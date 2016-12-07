#include "monitorform.h"
#include "ui_monitorform.h"
#include <QTimer>
#include "comdefs.h"
#include "qwt_painter.h"
#include "qwt_plot_canvas.h"
#include "qwt_plot_marker.h"
#include "qwt_plot_curve.h"
#include <QtXml>
#include "IRCommand.h"
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <QGradient>


#define MOTOR_MAGIC 'L'
#define BUZZER_ON 		_IOW(MOTOR_MAGIC, 0,int)
#define BUZZER_OFF 		_IOW(MOTOR_MAGIC, 1,int)
#define IOCTL_BZR_BEEP		_IOW('Q', 0x31, int)

//#include <linux/netlink.h>
//#include <arm-linux-gnueabi/sys/socket.h>
////#include <stdio.h>
//#include <stdlib.h>
//#include <dirent.h>
//#include <arm-linux-gnueabi/sys/types.h>
//#define UEVENT_BUFFER_SIZE 2048

MonitorForm::MonitorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonitorForm)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.7);


//    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);
//    ui->btnBPStart->setStyleSheet("broder-width: 0px");
    QDir dir;
    pathdir=dir.currentPath();
    IsChildren=true;
    IsFirst=true;
    Isvisible=false;
    isNBPFinished = false;  // 默认未结束
    alarmspo2=alarmpr=alarmglu=alarmtemp=alarmsys=alarmdia=alarmaver=false;
    Data_AVER=0;
    Data_DIAS=0;
    Data_GLU=0;
    Data_HR=0;
    Data_SPO2=0;
    Data_SYS=0;
    Data_TEMP=0;
    cal_Data_AVER=0;
    cal_Data_DIAS=0;
    cal_Data_SYS=0;
    cal_Data_SPO2=0;
    cal_Data_HR=0;
    IsNIBP=false;
    index_spo2=0;
    UItimer = new QTimer(this);
    connect(UItimer,SIGNAL(timeout()),this,SLOT(UpdateUI()));
    UItimer->start(500);
//    Sendtimer = new QTimer(this);
//    connect(Sendtimer,SIGNAL(timeout()),this,SLOT(SendDataSlot()));
//    Sendtimer->start(1500);
    spo2timer = new QTimer(this);
    connect(spo2timer,SIGNAL(timeout()),this,SLOT(UpdateUISPO2()));
    spo2timer->start(50);
//    Alarmtimer = new QTimer(this);
//    connect(Alarmtimer,SIGNAL(timeout()),this,SLOT(Alarm()));
    /// 修改
//    ui->qwtPlot_SPO2->clear();
    ui->qwtPlot_SPO2->detachItems();

    ui->qwtPlot_SPO2->setAxisScale(QwtPlot::yLeft,0,255);
    ui->qwtPlot_SPO2->setAxisScale(QwtPlot::xBottom, 0, PLOT_SIZE1);

    ui->qwtPlot_SPO2->enableAxis(QwtPlot::yLeft,false);
    ui->qwtPlot_SPO2->enableAxis(QwtPlot::xBottom,false);
    ui->qwtPlot_SPO2->enableAxis(QwtPlot::xTop,false);
    ui->qwtPlot_SPO2->enableAxis(QwtPlot::yRight,false);

    curve5=new QwtPlotCurve();
    curve6=new QwtPlotCurve();

    curve5->attach(ui->qwtPlot_SPO2);
    curve5->setPen(QPen(Qt::green));

    curve6->attach(ui->qwtPlot_SPO2);
    curve6->setPen(QPen(Qt::green));

//    USBInsert();
    watcher=new QDeviceWatcher();
    watcher->appendEventReceiver(this);
    connect(watcher,SIGNAL(deviceAdded(QString)),this,SLOT(slotDeviceAdded(QString)));
    connect(watcher,SIGNAL(deviceRemoved(QString)),this,SLOT(slotDeviceRemoved(QString)));
    toggleWatch();

//    msgdata="";
    Loadxml();
//    tcpserver=new QTcpServer(this);
//    clientconnection=new QTcpSocket(this);
//    StartListen();
    PatientAdult();
    ReadCalibratexml();
    count_i=0;
    fd = open("/dev/qiyang_buzzer", O_RDWR);
//    buzzon();
}

MonitorForm::~MonitorForm()
{
    delete ui;
//    delete setting;
}

void MonitorForm::UpdateData(int ID, double data1, double data2, double data3)
{
    switch(ID)
    {
    case ID_HR:
        //                            Data_PR=(unsigned short)data[1]*256+data[2];
        break;
    case ID_SPO2_PR:
        Data_SPO2= data1;
        Data_HR= data2;

        break;
    case ID_TEMP_ETG:
        Data_TEMP = data1;
        break;
    case ID_NBP_CUFPRE: //实时压力值显示
        Data_AVER = data1;
        break;
    case ID_NBP_END:
        isNBPFinished = true; // 测量结束，不再需要实时压力显示
        break;
    case ID_NBP_RESULT1:
        Data_SYS=data1;
        Data_DIAS=data2;
        Data_AVER=data3;
        IsNIBP=false;
        emit BPTestEND();
        ui->btnBPStart->setText(QString::fromUtf8(("血压测量")));
        break;
        //                        case ID_NBP_RESULT2:
        //                            Data_NIBP2=data1;
        //                            break;
    case ID_GLUCOSE:
//        if(data1!=0.0)
            Data_GLU = data1;
//        QString val;
//        if(Data_GLU==-100)
//            ui->lab_GLU->setText("--");
//        else
//            ui->lab_GLU->setText(val.sprintf("%2.1f",Data_GLU));
        break;
    }
    DataCalibrate();
}
void MonitorForm::AccuRecieved(double glu)
{
    Data_GLU=glu;
}

void MonitorForm::UpdateUI()
{
    QString val;

//    if((signed char)Data_HR==-100||(int)Data_HR<=0)
//        ui->lab_PR->setText("--");
//    else
//        ui->lab_PR->setText(val.sprintf("%3.0f",Data_HR));

    if((signed char)Data_HR!=-100&&(int)Data_HR>0)
        ui->lab_PR->setText(val.sprintf("%3.0f",cal_Data_HR));

    if((signed char)Data_SPO2!=-100&&(int)Data_SPO2!=156&&(int)Data_SPO2>0)
    {
        if(cal_Data_SPO2>100)
            cal_Data_SYS=100;
        ui->lab_SPO2->setText(val.sprintf("%2.0f",cal_Data_SPO2));
    }

    if((signed char)Data_TEMP==-100||(int)Data_TEMP<=0)
        ui->lab_TEMP->setText("--");
    else
        ui->lab_TEMP->setText(val.sprintf("%2.1f",Data_TEMP));

    if((signed char)Data_GLU==-100||(int)Data_GLU<=0)
        ui->lab_GLU->setText("--");
    else
        ui->lab_GLU->setText(val.sprintf("%2.1f",Data_GLU));
    if((signed char)Data_DIAS==-100||(int)Data_DIAS<=0)
        ui->lab_DIAS->setText("--");
    else
        ui->lab_DIAS->setText(val.sprintf("%3.0f",cal_Data_DIAS));
    if((signed char)Data_SYS==-100||(int)Data_SYS<=0)
        ui->lab_SYS->setText("--");
    else
        ui->lab_SYS->setText(val.sprintf("%3.0f",cal_Data_SYS));
    if((signed char)Data_AVER==-100||(int)Data_AVER<=0)
        ui->lab_AVER->setText("--");
    else
        ui->lab_AVER->setText(val.sprintf("%3.0f",cal_Data_AVER));
    Alarm();
}
void MonitorForm::Alarm()
{
//    QString val;
    if(Isvisible==true)
        Isvisible=false;
    else
        Isvisible=true;
//    if((signed char)Data_HR!=-100&&(int)Data_HR>0)
//    {
//        if(Data_HR>prmax||Data_HR<prmin)
//        {
//            alarmpr=true;
//            ui->lab_PR->setVisible(Isvisible);
//        }
//        else
//        {
//            ui->lab_PR->setVisible(true);
//            alarmpr=false;
//        }
//    }
//    else
//    {
//        ui->lab_PR->setVisible(true);
//        alarmpr=false;
//    }
    double tmpval=0;
    if(ui->lab_PR->text()!="--")
        tmpval=ui->lab_PR->text().toDouble();
    else
        tmpval=0;
    if((signed char)tmpval!=-100&&(int)tmpval>0)
    {
        if(tmpval>prmax||tmpval<prmin)
        {
            alarmpr=true;
            ui->lab_PR->setVisible(Isvisible);
        }
        else
        {
            ui->lab_PR->setVisible(true);
            alarmpr=false;
        }
    }
    else
    {
        ui->lab_PR->setVisible(true);
        alarmpr=false;
    }
    if(ui->lab_SPO2->text()!="--")
        tmpval=ui->lab_SPO2->text().toDouble();
    else
        tmpval=0;
    if((signed char)tmpval!=-100&&(int)tmpval>0)
    {
        if(Data_SPO2>=156)
        {
            ui->lab_SPO2->setVisible(true);
            alarmspo2=false;
        }
        else if(tmpval>spo2max||tmpval<spo2min)
        {
            alarmspo2=true;
            ui->lab_SPO2->setVisible(Isvisible);
        }
        else
        {
            ui->lab_SPO2->setVisible(true);
            alarmspo2=false;
        }
    }
    else
    {
        ui->lab_SPO2->setVisible(true);
        alarmspo2=false;
    }
    if((signed char)Data_TEMP!=-100&&(int)Data_TEMP>0)
    {
        if(Data_TEMP>tempmax||Data_TEMP<tempmin)
        {
            alarmtemp=true;
            ui->lab_TEMP->setVisible(Isvisible);
        }
        else
        {
            ui->lab_TEMP->setVisible(true);
            alarmtemp=false;
        }
    }
    else
    {
        alarmtemp=false;
        ui->lab_TEMP->setVisible(true);
    }
    if((signed char)Data_GLU!=-100&&(int)Data_GLU>0)
    {
        if(Data_GLU>glumax||Data_GLU<glumin)
        {
            alarmglu=true;
            ui->lab_GLU->setVisible(Isvisible);
        }
        else
        {
            alarmglu=false;
            ui->lab_GLU->setVisible(true);
        }
    }
    else
    {
        alarmglu=false;
        ui->lab_GLU->setVisible(true);
    }
    if((signed char)Data_DIAS!=-100&&(int)Data_DIAS>0)
    {
        if(cal_Data_DIAS>diasmax||cal_Data_DIAS<diasmin)
        {
            alarmdia=true;
            ui->lab_DIAS->setVisible(Isvisible);
        }
        else
        {
            alarmdia=false;
            ui->lab_DIAS->setVisible(true);
        }
    }
    else
    {
        alarmdia=false;
        ui->lab_DIAS->setVisible(true);
    }
    if((signed char)Data_SYS!=-100&&(int)Data_SYS>0)
    {
        if(cal_Data_SYS>sysmax||cal_Data_SYS<sysmin)
        {
            alarmsys=true;
            ui->lab_SYS->setVisible(Isvisible);
        }
        else
        {
            alarmsys=false;
            ui->lab_SYS->setVisible(true);
        }
    }
    else
    {
        alarmsys=false;
        ui->lab_SYS->setVisible(true);
    }
    if((signed char)Data_AVER!=-100&&(int)Data_AVER>0 && isNBPFinished) // 测量结束后才会显示警报
    {
        if(cal_Data_AVER>avermax||cal_Data_AVER<avermin)
        {
            alarmaver=true;
            ui->lab_AVER->setVisible(Isvisible);
        }
        else
        {
            alarmaver=false;
            ui->lab_AVER->setVisible(true);
        }
    }
    else
    {
        alarmaver=false;
        ui->lab_AVER->setVisible(true);
    }
    bool Isalarm=alarmpr|alarmspo2|alarmglu|alarmtemp|alarmdia|alarmaver|alarmsys;
    if(Isbuzzing&&Isalarm)
    {
        if(Isvisible)
            buzzonoff(BUZZER_ON);
        else
            buzzonoff(BUZZER_OFF);
    }
    else
    {
        buzzonoff(BUZZER_OFF);
    }
    if(Isvisible)
    {
        QString msgdara="&"+QString::number(cal_Data_AVER)+","+QString::number(cal_Data_DIAS)+","+QString::number(Data_GLU,'f',1)+","+QString::number(cal_Data_HR)+","+QString::number(cal_Data_SPO2)+","+QString::number(cal_Data_SYS)+","+QString::number(Data_TEMP,'f',1)+"%";
        emit senddata(msgdara);
    }
}
void MonitorForm::updateSPO2WaveData(int ID,double data1,double data2)
{
    static int spo2cnt = 0;
    SPO2Data *data_spo2 = new SPO2Data();
    switch(ID)
    {
    case ID_SPO2_WAVE:

        if(++spo2cnt >=2)
        {
            data_spo2->SPO2=data1;
            data_spo2->SPO2state=data2;
            spo2msg.push_back(data_spo2);

            spo2cnt = 0;
        }
        break;
    }
}
void MonitorForm::PaintSPO2Wave(int data)
{
    d_xspo2[index_spo2]=index_spo2;
    d_yspo2[index_spo2]=data;

    if(IsFirst)
    {
        curve5->setSamples(d_xspo2,d_yspo2,index_spo2+1);;
    }
    else
    {
        if(index_spo2 % 3 ==0)
        {
            //        curve5->setSamples(d_xspo2,d_yspo2,index_spo2+1);
            if(index_spo2<PLOT_SIZE1-5)
            {
                curve5->setSamples(d_xspo2,d_yspo2,index_spo2+1);
                curve6->setSamples(d_xspo2+index_spo2+5,d_yspo2+index_spo2+5,PLOT_SIZE1-index_spo2-5);
            }
            else
            {
                curve5->setSamples(d_xspo2,d_yspo2,index_spo2+1);
            }
        }
    }
    ui->qwtPlot_SPO2->replot();
    if(++index_spo2 ==PLOT_SIZE1)
    {
        IsFirst=false;
        index_spo2=0;
    }
}
void MonitorForm::UpdateUISPO2()
{
    int spo2cout=spo2msg.count();
    if(spo2cout>0)
    {
        for(int i=0;i<spo2cout;i++)
        {
            SPO2Data *spo2data=spo2msg.front();
            PaintSPO2Wave(spo2data->SPO2);
            //                }
            spo2msg.pop_front();
            delete spo2data;
        }
    }
}

void MonitorForm::on_btnBPStart_clicked()
{

    cal_Data_AVER=0;
    cal_Data_DIAS=0;
    cal_Data_SYS=0;
    emit BPTest();
    if(IsNIBP==false)
    {
        IsNIBP=true;
        isNBPFinished = false; // 开始血压测量
        if(IsChinese)
            ui->btnBPStart->setText(QString::fromUtf8("停止测量"));
        else
            ui->btnBPStart->setText("NIBP Stop");
    }
    else
    {
        IsNIBP=false;
        if(IsChinese)
            ui->btnBPStart->setText(QString::fromUtf8(("血压测量")));
        else
            ui->btnBPStart->setText("NIBP Start");
    }

}


//void MonitorForm::on_btnGlucose_clicked()
//{
//    emit GlucoseTest();
//}

void MonitorForm::Loadxml()
{
    QFile file(pathdir+"/configure.xml");
    if(!file.exists())
        return;
    file.open(QIODevice::ReadOnly|QFile::Text);

    QDomDocument doc;
    QString element;
    QString value;
    int id;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    QDomElement docElem=doc.documentElement();
    QDomNode node=docElem.firstChild();
    while(!node.isNull())
    {
        if(node.isElement())
        {
            element=node.nodeName();
            value=node.toElement().text();
            id=node.toElement().attribute("id").toInt();
            switch(id)
            {
            case 0:
                localip=value;
                break;
            case 1:
//                hostip=value;
                break;
            case 4:
                listenport=value.toInt();
                break;
            case 10:
                prmax=value.toInt();
                break;
            case 11:
                prmin=value.toInt();
                break;
            case 12:
                spo2max=value.toInt();
                break;
            case 13:
                spo2min=value.toInt();
                break;
            case 14:
                diasmax=value.toInt();
                break;
            case 15:
                diasmin=value.toInt();
                break;
            case 16:
                avermax=value.toInt();
                break;
            case 17:
                avermin=value.toInt();
                break;
            case 18:
                sysmax=value.toInt();
                break;
            case 19:
                sysmin=value.toInt();
                break;
            case 20:
                tempmax=value.toDouble();
                break;
            case 21:
                tempmin=value.toDouble();
                break;
            case 22:
                glumax=value.toDouble();
                break;
            case 23:
                glumin=value.toDouble();
                break;
            case 24:
//                connectport=value.toInt();
                break;
            case 25:
                Isbuzzing=value.toInt();
                break;
            case 26:
                if(value=="Chinese")
                    IsChinese=true;
                else
                    IsChinese=false;
                break;
            }
        }
        node=node.nextSibling();
    }
    ui->lab_Maxpr->setText(QString::number(prmax));
    ui->lab_Minpr->setText(QString::number(prmin));
    ui->lab_Maxspo2->setText(QString::number(spo2max));
    ui->lab_Minspo2->setText(QString::number(spo2min));
    ui->lab_MaxGLU->setText(QString::number(glumax,'f',1));
    ui->lab_MinGLU->setText(QString::number(glumin,'f',1));
    ui->lab_Maxsys->setText(QString::number(sysmax));
    ui->lab_Minsys->setText(QString::number(sysmin));
    ui->lab_Maxaver->setText(QString::number(avermax));
    ui->lab_Minaver->setText(QString::number(avermin));
    ui->lab_Maxdias->setText(QString::number(diasmax));
    ui->lab_Mindias->setText(QString::number(diasmin));
    ui->lab_Maxtemp->setText(QString::number(tempmax,'f',1));
    ui->lab_Mintemp->setText(QString::number(tempmin,'f',1));
    file.close();
    if(IsChinese)
    {
//        ui->lab_patienttypetag->setText(QString::fromUtf8("病人类型:"));
//        ui->lab_patienttypetag->setGeometry(40,20,151,41);
        ui->btnPatientType->setText(QString::fromUtf8("成人/儿童"));
        ui->btnBPStart->setText(QString::fromUtf8("血压测量"));
//        ui->btnGlucose->setText(QString::fromUtf8("血糖测量"));
//        ui->btnprint->setText(QString::fromUtf8("打印"));
//        ui->btnDataReSet->setText(QString::fromUtf8("重置"));
        ui->lab_bstop->setText(QString::fromUtf8("上限:"));
        ui->lab_bslow->setText(QString::fromUtf8("下限:"));
        ui->lab_bttop->setText(QString::fromUtf8("上限:"));
        ui->lab_btlow->setText(QString::fromUtf8("下限"));
        ui->lab_sbptop->setText(QString::fromUtf8("上限:"));
        ui->lab_sbplow->setText(QString::fromUtf8("下限"));
        ui->lab_maptop->setText(QString::fromUtf8("上限:"));
        ui->lab_maplow->setText(QString::fromUtf8("下限"));
        ui->lab_dbptop->setText(QString::fromUtf8("上限:"));
        ui->lab_dbplow->setText(QString::fromUtf8("下限"));
        ui->lab_spo2top->setText(QString::fromUtf8("上限:"));
        ui->lab_spo2low->setText(QString::fromUtf8("下限"));
        ui->lab_prtop->setText(QString::fromUtf8("上限:"));
        ui->lab_prlow->setText(QString::fromUtf8("下限"));
        ui->lab_BS->setText(QString::fromUtf8("血糖"));
        ui->lab_BT->setText(QString::fromUtf8("体温"));
        ui->lab_SBP->setText(QString::fromUtf8("收缩压"));
        ui->lab_MAP->setText(QString::fromUtf8("平均压"));
        ui->lab_DBP->setText(QString::fromUtf8("舒张压"));
        ui->lab_Spo2Tag->setText(QString::fromUtf8("血氧饱和度"));
        ui->lab_PRTag->setText(QString::fromUtf8("脉率"));
//        if(ui->lab_patienttype->text()=="Adult"||ui->lab_patienttype->text()==QString::fromUtf8("成人"))
//            ui->lab_patienttype->setText(QString::fromUtf8("成人"));
//        else
//            ui->lab_patienttype->setText(QString::fromUtf8("儿童"));
//        ui->lab_patienttype->setGeometry(140,20,61,41);
    }
    else
    {
//        ui->lab_patienttypetag->setText("PatientType:");
//        ui->lab_patienttypetag->setGeometry(30,20,151,41);
        ui->btnPatientType->setText("Adult/Child");
        ui->btnBPStart->setText("NIBP Start");
//        ui->btnGlucose->setText("GLU Test");
//        ui->btnprint->setText("Print");
//        ui->btnDataReSet->setText("Reset");
        ui->lab_bstop->setText("Max:");
        ui->lab_bslow->setText("Min:");
        ui->lab_bttop->setText("Max:");
        ui->lab_btlow->setText("Min:");
        ui->lab_sbptop->setText("Max:");
        ui->lab_sbplow->setText("Min:");
        ui->lab_maptop->setText("Max:");
        ui->lab_maplow->setText("Min:");
        ui->lab_dbptop->setText("Max:");
        ui->lab_dbplow->setText("Min:");
        ui->lab_spo2top->setText("Max:");
        ui->lab_spo2low->setText("Min:");
        ui->lab_prtop->setText("Max:");
        ui->lab_prlow->setText("Min:");
        ui->lab_BS->setText("GLU");
        ui->lab_BT->setText("BBT");
        ui->lab_SBP->setText("SBP");
        ui->lab_MAP->setText("MAP");
        ui->lab_DBP->setText("DBP");
        ui->lab_Spo2Tag->setText("SPO2");
        ui->lab_PRTag->setText("PR");
//        if(ui->lab_patienttype->text()==QString::fromUtf8("成人")||ui->lab_patienttype->text()=="Adult")
//            ui->lab_patienttype->setText("Adult");
//        else
//            ui->lab_patienttype->setText("Child");
//        ui->lab_patienttype->setGeometry(160,20,61,41);
    }
}


//void MonitorForm::on_btnAdult_clicked()
//{
//    ui->btnChildren->setEnabled(true);
//    ui->btnAdult->setEnabled(false);
//    ui->lab_patienttype->setText(QString::fromUtf8(("成人")));
//    emit PatientType((unsigned char)0);
//}

//void MonitorForm::on_btnChildren_clicked()
//{
//    ui->btnAdult->setEnabled(true);
//    ui->btnChildren->setEnabled(false);
//    ui->lab_patienttype->setText(QString::fromUtf8(("儿童")));
//    emit PatientType((unsigned char)1);
//}

//int MonitorForm::init_hotplug_sock()
//{
//  const int buffersize = 1024;
//  int ret;

//  struct sockaddr_nl snl;
//  bzero(&snl, sizeof(struct sockaddr_nl));
//  snl.nl_family = AF_NETLINK;
//  snl.nl_pid = getpid();
//  snl.nl_groups = 1;

//  int s = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
//  if (s == -1)
//  {
//        perror("socket");
//        return -1;Failed to set controlling terminal: Invalid argumen
//  }
//  setsockopt(s, SOL_SOCKET, SO_RCVBUF, &buffersize, sizeof(buffersize));

//  ret = bind(s, (struct sockaddr *)&snl, sizeof(struct sockaddr_nl));
//  if (ret < 0)
//  {
//        perror("bind");
//        close(s);
//        return -1;
//  }

//  return s;
//}
void MonitorForm::slotDeviceAdded(QString deviceinfo)
{
//    ui->btnGlucose->setEnabled(true);
    emit ResetsPacketIdFound();
    emit USBreload();
}
void MonitorForm::slotDeviceRemoved(QString deviceinfo)
{
//    ui->btnGlucose->setEnabled(false);
    ui->lab_GLU->setText("--");
}
void MonitorForm::toggleWatch()
{
    if(!watcher->isRunning())
    {
        watcher->start();
    }
}
void MonitorForm::UsbopenState(bool isopen)
{
//    if(isopen==false)
//        ui->btnGlucose->setEnabled(false);
//    else
//        ui->btnGlucose->setEnabled(true);
}
//void MonitorForm::TcpCreatSlot()
//{
//    if(clientconnection->state()&QAbstractSocket::ConnectedState)
//        clientconnection->close();
//    clientconnection=tcpserver->nextPendingConnection();
//    connect(clientconnection,SIGNAL(readyRead()),this,SLOT(ReadSendMessage()));
//    connect(clientconnection,SIGNAL(disconnected()),this,SLOT(TcpClientClose()));
//    connect(clientconnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(DisplayTcpError(QAbstractSocket::SocketError)));
//}
//void MonitorForm::TcpClientClose()
//{
//    clientconnection->close();
//}
//void MonitorForm::DisplayTcpError(QAbstractSocket::SocketError)
//{
//    qDebug()<<clientconnection->errorString();
//}

//void MonitorForm::ActivesendData()
//{
//    QByteArray block;
//    QString msgdata=QString::number(Data_AVER)+","+QString::number(Data_DIAS)+","+QString::number(Data_GLU)+","+QString::number(Data_HR)+","+QString::number(Data_SPO2)+","+QString::number(Data_SYS)+","+QString::number(Data_TEMP);
//    block.append(msgdata);
//    if(tcpsocket->state()&QAbstractSocket::ConnectedState)
//    {
//        tcpsocket->write(block);
//        tcpsocket->flush();
//        tcpsocket->abort();
////        block.resize(0);
//        qDebug()<<count_i++;
//    }
//}

//void MonitorForm::ReadSendMessage()
//{
//    char *redata;
//    redata=clientconnection->readAll().data();
//    QString info=redata;
//    redata=NULL;
//    if(info!="")
//        emit receivedata(info);
//    qDebug()<<info+":"+QString::number(++count_i);

//    msgdata=QString::number(cal_Data_AVER)+","+QString::number(cal_Data_DIAS)+","+QString::number(Data_GLU,'f',1)+","+QString::number(cal_Data_HR)+","+QString::number(cal_Data_SPO2)+","+QString::number(cal_Data_SYS)+","+QString::number(Data_TEMP,'f',1);
//    block.append(msgdata);
//    clientconnection->write(block);
//    clientconnection->flush();
////    qDebug()<<block+":"+QString::number(count_i);
//    block.clear();
//}
//void MonitorForm::StartListen()
//{
//    if(tcpserver->isListening())
//    {
//        tcpserver->close();
//        clientconnection->close();
//        tcpserver=new QTcpServer(this);
//    }
//    if(!tcpserver->listen(QHostAddress(localip),listenport))
//    {
//        qDebug()<<tcpserver->errorString();
//    }
//    connect(tcpserver,SIGNAL(newConnection()),this,SLOT(TcpCreatSlot()));
//}
void MonitorForm::IRProc(unsigned char code)
{
    if(this->isVisible())
    {
//        if(code==IR_BLOODPRE)
//        {
        switch(code)
        {
        case IR_BLOODPRE:
            on_btnBPStart_clicked();
            break;
        case IR_CLEAR:
            DataReSet();
            break;
//        case IR_PRINT:
//            on_btnprint_clicked();
//            break;
//        case IR_PATIENTTYPE:
//            on_btnPatientType_clicked();
//            break;
        case IR_ADULT:
            PatientAdult();
            break;
        case IR_CHILD:
            PatientChild();
            break;
        }
    }
}

void MonitorForm::on_btnPatientType_clicked()
{
    if(!IsChildren)
    {
        IsChildren=true;
//        if(IsChinese)
//            ui->lab_patienttype->setText(QString::fromUtf8(("儿童")));
//        else
//            ui->lab_patienttype->setText("Child");
        emit PatientType((unsigned char)1);

    }
    else
    {
        IsChildren=false;
//        if(IsChinese)
//            ui->lab_patienttype->setText(QString::fromUtf8(("成人")));
//        else
//            ui->lab_patienttype->setText("Adult");
        emit PatientType((unsigned char)0);
    }
}
void MonitorForm::PatientAdult()
{
    IsChildren=false;
//    if(IsChinese)
//        ui->lab_patienttype->setText(QString::fromUtf8(("成人")));
//    else
//        ui->lab_patienttype->setText("Adult");
    emit PatientType((unsigned char)0);
}
void MonitorForm::PatientChild()
{
    IsChildren=true;
//    if(IsChinese)
//        ui->lab_patienttype->setText(QString::fromUtf8(("儿童")));
//    else
//        ui->lab_patienttype->setText("Child");
    emit PatientType((unsigned char)1);
}


void MonitorForm::DataReSet()
{
    Data_AVER=0;
    Data_DIAS=0;
    Data_GLU=0;
    Data_HR=0;
    Data_SPO2=0;
    Data_SYS=0;
    Data_TEMP=0;
    cal_Data_AVER=0;
    cal_Data_DIAS=0;
    cal_Data_HR=0;
    cal_Data_SPO2=0;
    cal_Data_SYS=0;
    ui->lab_AVER->setText("--");
    ui->lab_DIAS->setText("--");
    ui->lab_GLU->setText("--");
    ui->lab_PR->setText("--");
    ui->lab_SPO2->setText("--");
    ui->lab_SYS->setText("--");
    ui->lab_TEMP->setText("--");
    alarmspo2=alarmpr=alarmglu=alarmtemp=alarmsys=alarmdia=alarmaver=false;
    Loadxml();
    emit ClearPinfo();
}
void MonitorForm::buzzonoff(unsigned int cmd)
{
//    fd = open("/dev/qiyang_buzzer", O_RDWR);
    if(fd > 0&&cmd==BUZZER_ON)
        ioctl(fd, cmd,cmd);
    else
        ioctl(fd,BUZZER_OFF);
}

void MonitorForm::printSlot()
{
    double pdata[7];
    pdata[0]=Data_GLU;
    pdata[1]=Data_TEMP;
    pdata[2]=cal_Data_SYS;
    pdata[3]=cal_Data_DIAS;
    pdata[4]=cal_Data_AVER;
    pdata[5]=cal_Data_SPO2;
    pdata[6]=cal_Data_HR;
    emit print(pdata);
}
void MonitorForm::setisbuzzing()
{
    Isbuzzing=false;
}
void MonitorForm::ReadCalibratexml()
{
    QFile file(pathdir+"/calibrate.xml");
    if(!file.exists())
        InitCalibrate();
    file.open(QIODevice::ReadOnly|QFile::Text);

    QDomDocument doc;
    QString element;
    QString value;
    int id;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    QDomElement docElem=doc.documentElement();
    QDomNode node=docElem.firstChild();
    while(!node.isNull())
    {
        if(node.isElement())
        {
            element=node.nodeName();
            value=node.toElement().text();
            id=node.toElement().attribute("id").toInt();
            switch(id)
            {
            case 1:
                hrinput1=value.toInt();
                break;
            case 2:
                hrinput2=value.toInt();
                break;
            case 3:
                hrinput3=value.toInt();
                break;
            case 4:
                hrinput4=value.toInt();
                break;
            case 5:
                hrinput5=value.toInt();
                break;
            case 6:
                hrinput6=value.toInt();
                break;
            case 7:
                hrinput7=value.toInt();
                break;
            case 8:
                hrinput8=value.toInt();
                break;
            case 9:
                hrinput9=value.toInt();
                break;
            case 10:
                hrinput10=value.toInt();
                break;
            case 11:
                hroutput1=value.toInt();
                break;
            case 12:
                hroutput2=value.toInt();
                break;
            case 13:
                hroutput3=value.toInt();
                break;
            case 14:
                hroutput4=value.toInt();
                break;
            case 15:
                hroutput5=value.toInt();
                break;
            case 16:
                hroutput6=value.toInt();
                break;
            case 17:
                hroutput7=value.toInt();
                break;
            case 18:
                hroutput8=value.toInt();
                break;
            case 19:
                hroutput9=value.toInt();
                break;
            case 20:
                hroutput10=value.toInt();
                break;
            case 21:
                spo2input1=value.toInt();
                break;
            case 22:
                spo2input2=value.toInt();
                break;
            case 23:
                spo2input3=value.toInt();
                break;
            case 24:
                spo2input4=value.toInt();
                break;
            case 25:
                spo2input5=value.toInt();
                break;
            case 26:
                spo2input6=value.toInt();
                break;
            case 27:
                spo2input7=value.toInt();
                break;
            case 28:
                spo2input8=value.toInt();
                break;
            case 29:
                spo2input9=value.toInt();
                break;
            case 30:
                spo2input10=value.toInt();
                break;
            case 31:
                spo2output1=value.toInt();
                break;
            case 32:
                spo2output2=value.toInt();
                break;
            case 33:
                spo2output3=value.toInt();
                break;
            case 34:
                spo2output4=value.toInt();
                break;
            case 35:
                spo2output5=value.toInt();
                break;
            case 36:
                spo2output6=value.toInt();
                break;
            case 37:
                spo2output7=value.toInt();
                break;
            case 38:
                spo2output8=value.toInt();
                break;
            case 39:
                spo2output9=value.toInt();
                break;
            case 40:
                spo2output10=value.toInt();
                break;
            case 41:
                sysinput1=value.toInt();
                break;
            case 42:
                sysinput2=value.toInt();
                break;
            case 43:
                sysinput3=value.toInt();
                break;
            case 44:
                sysinput4=value.toInt();
                break;
            case 45:
                sysinput5=value.toInt();
                break;
            case 46:
                sysinput6=value.toInt();
                break;
            case 47:
                sysinput7=value.toInt();
                break;
            case 48:
                sysinput8=value.toInt();
                break;
            case 49:
                sysinput9=value.toInt();
                break;
            case 50:
                sysinput10=value.toInt();
                break;
            case 51:
                sysoutput1=value.toInt();
                break;
            case 52:
                sysoutput2=value.toInt();
                break;
            case 53:
                sysoutput3=value.toInt();
                break;
            case 54:
                sysoutput4=value.toInt();
                break;
            case 55:
                sysoutput5=value.toInt();
                break;
            case 56:
                sysoutput6=value.toInt();
                break;
            case 57:
                sysoutput7=value.toInt();
                break;
            case 58:
                sysoutput8=value.toInt();
                break;
            case 59:
                sysoutput9=value.toInt();
                break;
            case 60:
                sysoutput10=value.toInt();
                break;
            case 61:
                averinput1=value.toInt();
                break;
            case 62:
                averinput2=value.toInt();
                break;
            case 63:
                averinput3=value.toInt();
                break;
            case 64:
                averinput4=value.toInt();
                break;
            case 65:
                averinput5=value.toInt();
                break;
            case 66:
                averinput6=value.toInt();
                break;
            case 67:
                averinput7=value.toInt();
                break;
            case 68:
                averinput8=value.toInt();
                break;
            case 69:
                averinput9=value.toInt();
                break;
            case 70:
                averinput10=value.toInt();
                break;
            case 71:
                averoutput1=value.toInt();
                break;
            case 72:
                averoutput2=value.toInt();
                break;
            case 73:
                averoutput3=value.toInt();
                break;
            case 74:
                averoutput4=value.toInt();
                break;
            case 75:
                averoutput5=value.toInt();
                break;
            case 76:
                averoutput6=value.toInt();
                break;
            case 77:
                averoutput7=value.toInt();
                break;
            case 78:
                averoutput8=value.toInt();
                break;
            case 79:
                averoutput9=value.toInt();
                break;
            case 80:
                averoutput10=value.toInt();
                break;
            case 81:
                diainput1=value.toInt();
                break;
            case 82:
                diainput2=value.toInt();
                break;
            case 83:
                diainput3=value.toInt();
                break;
            case 84:
                diainput4=value.toInt();
                break;
            case 85:
                diainput5=value.toInt();
                break;
            case 86:
                diainput6=value.toInt();
                break;
            case 87:
                diainput7=value.toInt();
                break;
            case 88:
                diainput8=value.toInt();
                break;
            case 89:
                diainput9=value.toInt();
                break;
            case 90:
                diainput10=value.toInt();
                break;
            case 91:
                diaoutput1=value.toInt();
                break;
            case 92:
                diaoutput2=value.toInt();
                break;
            case 93:
                diaoutput3=value.toInt();
                break;
            case 94:
                diaoutput4=value.toInt();
                break;
            case 95:
                diaoutput5=value.toInt();
                break;
            case 96:
                diaoutput6=value.toInt();
                break;
            case 97:
                diaoutput7=value.toInt();
                break;
            case 98:
                diaoutput8=value.toInt();
                break;
            case 99:
                diaoutput9=value.toInt();
                break;
            case 100:
                diaoutput10=value.toInt();
                break;
            }
        }
        node=node.nextSibling();
    }
    file.close();
}

void MonitorForm::DataCalibrate()
{
    int hrin[10]={hrinput1,hrinput2,hrinput3,hrinput4,hrinput5,hrinput6,hrinput7,hrinput8,hrinput9,hrinput10};
    int hrout[10]={hroutput1,hroutput2,hroutput3,hroutput4,hroutput5,hroutput6,hroutput7,hroutput8,hroutput9,hroutput10};
    int spo2in[10]={spo2input1,spo2input2,spo2input3,spo2input4,spo2input5,spo2input6,spo2input7,spo2input8,spo2input9,spo2input10};
    int spo2out[10]={spo2output1,spo2output2,spo2output3,spo2output4,spo2output5,spo2output6,spo2output7,spo2output8,spo2output9,spo2output10};
    int diain[10]={diainput1,diainput2,diainput3,diainput4,diainput5,diainput6,diainput7,diainput8,diainput9,diainput10};
    int diaout[10]={diaoutput1,diaoutput2,diaoutput3,diaoutput4,diaoutput5,diaoutput6,diaoutput7,diaoutput8,diaoutput9,diaoutput10};
    int averin[10]={averinput1,averinput2,averinput3,averinput4,averinput5,averinput6,averinput7,averinput8,averinput9,averinput10};
    int averout[10]={averoutput1,averoutput2,averoutput3,averoutput4,averoutput5,averoutput6,averoutput7,averoutput8,averoutput9,averoutput10};
    int sysin[10]={sysinput1,sysinput2,sysinput3,sysinput4,sysinput5,sysinput6,sysinput7,sysinput8,sysinput9,sysinput10};
    int sysout[10]={sysoutput1,sysoutput2,sysoutput3,sysoutput4,sysoutput5,sysoutput6,sysoutput7,sysoutput8,sysoutput9,sysoutput10};
    QString val;
    for(int i=0;i<9;i++)
    {
        if((signed char)Data_HR!=-100&&val.sprintf("%3.0f",Data_HR).toInt()>hrin[i]&&val.sprintf("%3.0f",Data_HR).toInt()<=hrin[i+1])
        {
            cal_Data_HR=(double)((((int)Data_HR-hrin[i])*(hrout[i+1]-hrout[i]))/(hrin[i+1]-hrin[i])+hrout[i]);
        }
        if(Data_SPO2!=156&&val.sprintf("%3.0f",Data_SPO2).toInt()>spo2in[i]&&val.sprintf("%3.0f",Data_SPO2).toInt()<=spo2in[i+1])
        {
            cal_Data_SPO2=(double)((((int)Data_SPO2-spo2in[i])*(spo2out[i+1]-spo2out[i]))/(spo2in[i+1]-spo2in[i])+spo2out[i]);
        }
        if(val.sprintf("%3.0f",Data_SYS).toInt()>sysin[i]&&val.sprintf("%3.0f",Data_SYS).toInt()<=sysin[i+1])
        {
            cal_Data_SYS=(double)((((int)Data_SYS-sysin[i])*(sysout[i+1]-sysout[i]))/(sysin[i+1]-sysin[i])+sysout[i]);
        }
        if(val.sprintf("%3.0f",Data_DIAS).toInt()>diain[i]&&val.sprintf("%3.0f",Data_DIAS).toInt()<=diain[i+1])
        {
            cal_Data_DIAS=(double)((((int)Data_DIAS-diain[i])*(diaout[i+1]-diaout[i]))/(diain[i+1]-diain[i])+diaout[i]);
        }
        if(val.sprintf("%3.0f",Data_AVER).toInt()>averin[i]&&val.sprintf("%3.0f",Data_AVER).toInt()<=averin[i+1])
        {
            cal_Data_AVER=(double)((((int)Data_AVER-averin[i])*(averout[i+1]-averout[i]))/(averin[i+1]-averin[i])+averout[i]);
        }
    }
//    qDebug()<<"HRInupt:"+val.sprintf("%3.0f",Data_HR)+'\n';
//    qDebug()<<"HRoutput:"+val.sprintf("%3.0f",cal_Data_HR)+'\n';
//    qDebug()<<"Spo2Inupt:"+val.sprintf("%3.0f",Data_SPO2)+'\n';
//    qDebug()<<"Spo2output:"+val.sprintf("%3.0f",cal_Data_SPO2)+'\n';
//    qDebug()<<"SysInupt:"+val.sprintf("%3.0f",Data_SYS)+'\n';
//    qDebug()<<"Sysoutput:"+val.sprintf("%3.0f",cal_Data_SYS)+'\n';
//    qDebug()<<"AverInupt:"+val.sprintf("%3.0f",Data_AVER)+'\n';
//    qDebug()<<"Averoutput:"+val.sprintf("%3.0f",cal_Data_AVER)+'\n';
//    qDebug()<<"DiaInupt:"+val.sprintf("%3.0f",Data_DIAS)+'\n';
//    qDebug()<<"Diaoutput:"+val.sprintf("%3.0f",cal_Data_DIAS)+'\n';
}
void MonitorForm::InitCalibrate()
{
    hrinput1=hroutput1=0;
    hrinput2=hroutput2=20;
    hrinput3=hroutput3=40;
    hrinput4=hroutput4=60;
    hrinput5=hroutput5=80;
    hrinput6=hroutput6=100;
    hrinput7=hroutput7=120;
    hrinput8=hroutput8=140;
    hrinput9=hroutput9=160;
    hrinput10=hroutput10=200;

    spo2input1=spo2output1=0;
    spo2input2=spo2output2=10;
    spo2input3=spo2output3=20;
    spo2input4=spo2output4=30;
    spo2input5=spo2output5=40;
    spo2input6=spo2output6=50;
    spo2input7=spo2output7=60;
    spo2input8=spo2output8=70;
    spo2input9=spo2output9=80;
    spo2input10=spo2output10=100;

    sysinput1=sysoutput1=0;
    sysinput2=sysoutput2=30;
    sysinput3=sysoutput3=60;
    sysinput4=sysoutput4=90;
    sysinput5=sysoutput5=120;
    sysinput6=sysoutput6=150;
    sysinput7=sysoutput7=180;
    sysinput8=sysoutput8=210;
    sysinput9=sysoutput9=240;
    sysinput10=sysoutput10=290;

    diainput1=diaoutput1=0;
    diainput2=diaoutput2=20;
    diainput3=diaoutput3=40;
    diainput4=diaoutput4=60;
    diainput5=diaoutput5=80;
    diainput6=diaoutput6=100;
    diainput7=diaoutput7=120;
    diainput8=diaoutput8=140;
    diainput9=diaoutput9=160;
    diainput10=diaoutput10=200;

    averinput1=averoutput1=0;
    averinput2=averoutput2=20;
    averinput3=averoutput3=40;
    averinput4=averoutput4=60;
    averinput5=averoutput5=80;
    averinput6=averoutput6=100;
    averinput7=averoutput7=120;
    averinput8=averoutput8=140;
    averinput9=averoutput9=160;
    averinput10=averoutput10=200;
}
