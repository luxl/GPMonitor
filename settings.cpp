#include "settings.h"
#include "ui_settings.h"
//#include "mainform.h"
#include <QDateTime>
#include <QTimer>
#include <QtXml>
#include <QProcess>
#include <QRegExp>
#include <QValidator>
#include <string.h>

settings::settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.7);
    QRegExp regint("[1-9][0-9]{0,2}");
    ui->TxthrMax->setValidator(new QRegExpValidator(regint,this));
    ui->TxthrMin->setValidator(new QRegExpValidator(regint,this));
    ui->Txtspo2Max->setValidator(new QRegExpValidator(regint,this));
    ui->Txtspo2Min->setValidator(new QRegExpValidator(regint,this));
    ui->TxtsysMax->setValidator(new QRegExpValidator(regint,this));
    ui->TxtsysMin->setValidator(new QRegExpValidator(regint,this));
    ui->TxtaverMax->setValidator(new QRegExpValidator(regint,this));
    ui->TxtaverMin->setValidator(new QRegExpValidator(regint,this));
    ui->TxtdiasMax->setValidator(new QRegExpValidator(regint,this));
    ui->TxtdiasMin->setValidator(new QRegExpValidator(regint,this));

    QRegExp regdouble("[0-9]{1,2}[.][0-9]");
    ui->TxtgluMax->setValidator(new QRegExpValidator(regdouble,this));
    ui->TxtgluMin->setValidator(new QRegExpValidator(regdouble,this));
    ui->TxttempMax->setValidator(new QRegExpValidator(regdouble,this));
    ui->TxttempMin->setValidator(new QRegExpValidator(regdouble,this));
    QRegExp regyear("[2][0-9][0-9][0-9]");
    ui->Txtyear->setInputMask("0000;0");

    ui->Txtyear->setValidator(new QRegExpValidator(regyear,this));
    ui->Txtmonth->setValidator(new QIntValidator(1,12,this));
    ui->Txtday->setValidator(new QIntValidator(1,31,this));
    ui->Txthour->setValidator(new QIntValidator(0,23,this));
    ui->Txtminute->setValidator(new QIntValidator(0,59,this));
    ui->Txtsecond->setValidator(new QIntValidator(0,59,this));

    QRegExp regExpip("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){4}");
    ui->TxtlocalIP->setValidator(new QRegExpValidator(regExpip,this));
//    ui->TxtlocalIP->setInputMask("000.000.000.000;0");
    ui->Txtsubnetmask->setValidator(new QRegExpValidator(regExpip,this));
//    ui->Txtsubnetmask->setInputMask("000.000.000.000;0");
    ui->Txtgateway->setValidator(new QRegExpValidator(regExpip,this));
//    ui->Txtgateway->setInputMask("000.000.000.000;0");

    QButtonGroup *btngroup=new QButtonGroup();
    btngroup->addButton(ui->btn0,0);
    btngroup->addButton(ui->btn1,1);
    btngroup->addButton(ui->btn2,2);
    btngroup->addButton(ui->btn3,3);
    btngroup->addButton(ui->btn4,4);
    btngroup->addButton(ui->btn5,5);
    btngroup->addButton(ui->btn6,6);
    btngroup->addButton(ui->btn7,7);
    btngroup->addButton(ui->btn8,8);
    btngroup->addButton(ui->btn9,9);
    btngroup->addButton(ui->btnPoint,10);
    btngroup->addButton(ui->btnDelete,11);
    btngroup->addButton(ui->btnOK,12);
    connect(btngroup,SIGNAL(buttonClicked(int)),this,SLOT(btnNumslot(int)));

//    ui->Txtspo2Min->installEventFilter(this);
//    ui->TxtdiasMax->installEventFilter(this);
//    ui->TxtdiasMin->installEventFilter(this);
//    ui->TxtaverMax->installEventFilter(this);
//    ui->TxtaverMin->installEventFilter(this);
//    ui->TxtsysMax->installEventFilter(this);
//    ui->TxtsysMin->installEventFilter(this);
//    ui->Txtyear->installEventFilter(this);
//    ui->Txtday->installEventFilter(this);
//    ui->Txthour->installEventFilter(this);
//    ui->Txtminute->installEventFilter(this);
//    ui->TxttempMax->installEventFilter(this);
//    ui->TxttempMin->installEventFilter(this);
//    ui->TxtgluMax->installEventFilter(this);
//    ui->TxtgluMin->installEventFilter(this);
//    ui->Txtport->installEventFilter(this);
//    ui->TxtlocalIP->installEventFilter(this);
//    ui->TxthostIP->installEventFilter(this);
//    ui->Txtsubnetmask->installEventFilter(this);
//    ui->Txtgateway->installEventFilter(this);
//    ui->Txtmonth->installEventFilter(this);
//    ui->Txtsecond->installEventFilter(this);
    QDir dir;
    pathdir=dir.currentPath();
    Readxml();
    calibrate=new CalibrateDialog(this);
    connect(this,SIGNAL(langueload(bool)),calibrate,SLOT(loadlanguexml(bool)));

    connect(calibrate, SIGNAL(openValve()), this, SLOT(sendOpenSig()));
}

settings::~settings()
{
    delete ui;
    delete calibrate;

//    delete mainform;
}

void settings::btnNumslot(int num)
{
        if(ui->TxtlocalIP->hasFocus())
        {
            if(num<10)
                ui->TxtlocalIP->insert(QString::number(num));
            else if(num==10)
                ui->TxtlocalIP->insert(".");
            else if(num==11)
                ui->TxtlocalIP->backspace();
        }
        else if(ui->Txtgateway->hasFocus())
        {
            if(num<10)
                ui->Txtgateway->insert(QString::number(num));
            else if(num==10)
                ui->Txtgateway->insert(".");
            else if(num==11)
                ui->Txtgateway->backspace();
        }
        else if(ui->Txtsubnetmask->hasFocus())
        {
            if(num<10)
                ui->Txtsubnetmask->insert(QString::number(num));
            else if(num==10)
                ui->Txtsubnetmask->insert(".");
            else if(num==11)
                ui->Txtsubnetmask->backspace();
        }
        else if(ui->TxtaverMax->hasFocus())
        {
            if(num<10)
                ui->TxtaverMax->insert(QString::number(num));
            else if(num==11)
                ui->TxtaverMax->backspace();
        }
        else if(ui->TxtaverMin->hasFocus())
        {
            if(num<10)
                ui->TxtaverMin->insert(QString::number(num));
            else if(num==11)
                ui->TxtaverMin->backspace();
        }
        else if(ui->TxtdiasMax->hasFocus())
        {
            if(num<10)
                ui->TxtdiasMax->insert(QString::number(num));
            else if(num==11)
                ui->TxtdiasMax->backspace();
        }
        else if(ui->TxtdiasMin->hasFocus())
        {
            if(num<10)
                ui->TxtdiasMin->insert(QString::number(num));
            else if(num==11)
                ui->TxtdiasMin->backspace();
        }
        else if(ui->TxthrMax->hasFocus())
        {
            if(num<10)
                ui->TxthrMax->insert(QString::number(num));
            else if(num==11)
                ui->TxthrMax->backspace();
        }
        else if(ui->TxthrMin->hasFocus())
        {
            if(num<10)
                ui->TxthrMin->insert(QString::number(num));
            else if(num==11)
                ui->TxthrMin->backspace();
        }
        else if(ui->Txtspo2Max->hasFocus())
        {
            if(num<10)
                ui->Txtspo2Max->insert(QString::number(num));
            else if(num==11)
                ui->Txtspo2Max->backspace();
        }
        else if(ui->Txtspo2Min->hasFocus())
        {
            if(num<10)
                ui->Txtspo2Min->insert(QString::number(num));
            else if(num==11)
                ui->Txtspo2Min->backspace();
        }
        else if(ui->TxtsysMax->hasFocus())
        {
            if(num<10)
                ui->TxtsysMax->insert(QString::number(num));
            else if(num==11)
                ui->TxtsysMax->backspace();
        }
        else if(ui->TxtsysMin->hasFocus())
        {
            if(num<10)
                ui->TxtsysMin->insert(QString::number(num));
            else if(num==11)
                ui->TxtsysMin->backspace();
        }
        else if(ui->TxtsysMin->hasFocus())
        {
            if(num<10)
                ui->TxtsysMin->insert(QString::number(num));
            else if(num==11)
                ui->TxtsysMin->backspace();
        }
        else if(ui->TxttempMax->hasFocus())
        {
            if(num<10)
                ui->TxttempMax->insert(QString::number(num));
            else if(num==10)
                ui->TxttempMax->insert(".");
            else if(num==11)
                ui->TxttempMax->backspace();
        }
        else if(ui->TxttempMin->hasFocus())
        {
            if(num<10)
                ui->TxttempMin->insert(QString::number(num));
            else if(num==10)
                ui->TxttempMin->insert(".");
            else if(num==11)
                ui->TxttempMin->backspace();
        }
        else if(ui->TxtgluMax->hasFocus())
        {
            if(num<10)
                ui->TxtgluMax->insert(QString::number(num));
            else if(num==10)
                ui->TxtgluMax->insert(".");
            else if(num==11)
                ui->TxtgluMax->backspace();
        }
        else if(ui->TxtgluMin->hasFocus())
        {
            if(num<10)
                ui->TxtgluMin->insert(QString::number(num));
            else if(num==10)
                ui->TxtgluMin->insert(".");
            else if(num==11)
                ui->TxtgluMin->backspace();
        }
        else if(ui->TxtListenport->hasFocus())
        {
            if(num<10)
                ui->TxtListenport->insert(QString::number(num));
            else if(num==11)
                ui->TxtListenport->backspace();
        }
        else if(ui->Txtyear->hasFocus())
        {
            if(num<10)
                ui->Txtyear->insert(QString::number(num));
            else if(num==11)
                ui->Txtyear->backspace();
        }
        else if(ui->Txtday->hasFocus())
        {
            if(num<10)
                ui->Txtday->insert(QString::number(num));
            else if(num==11)
                ui->Txtday->backspace();
        }
        else if(ui->Txtmonth->hasFocus())
        {
            if(num<10)
                ui->Txtmonth->insert(QString::number(num));
            else if(num==11)
                ui->Txtmonth->backspace();
        }
        else if(ui->Txthour->hasFocus())
        {
            if(num<10)
                ui->Txthour->insert(QString::number(num));
            else if(num==11)
                ui->Txthour->backspace();
        }
        else if(ui->Txtminute->hasFocus())
        {
            if(num<10)
                ui->Txtminute->insert(QString::number(num));
            else if(num==11)
                ui->Txtminute->backspace();
        }
        else if(ui->Txtsecond->hasFocus())
        {
            if(num<10)
                ui->Txtsecond->insert(QString::number(num));
            else if(num==11)
                ui->Txtsecond->backspace();
        }

}

void settings::on_btnOK_clicked()
{
    hrmax=ui->TxthrMax->text().toInt();
    hrmin=ui->TxthrMin->text().toInt();
    spo2max=ui->Txtspo2Max->text().toInt();
    spo2min=ui->Txtspo2Min->text().toInt();
    diasmax=ui->TxtdiasMax->text().toInt();
    diasmin=ui->TxtdiasMin->text().toInt();
    avermax=ui->TxtaverMax->text().toInt();
    avermin=ui->TxtaverMin->text().toInt();
    sysmax=ui->TxtsysMax->text().toInt();
    sysmin=ui->TxtsysMin->text().toInt();
    year=ui->Txtyear->text().toInt();
    month=ui->Txtmonth->text().toInt();
    day=ui->Txtday->text().toInt();
    hour=ui->Txthour->text().toInt();
    minute=ui->Txtminute->text().toInt();
    second=ui->Txtsecond->text().toInt();
    tempmax=ui->TxttempMax->text().toDouble();
    tempmin=ui->TxttempMin->text().toDouble();
    glumax=ui->TxtgluMax->text().toDouble();
    glumin=ui->TxtgluMin->text().toDouble();
    listenport=ui->TxtListenport->text().toInt();
    localip=ui->TxtlocalIP->text();
    subnetmask=ui->Txtsubnetmask->text();
    gateway=ui->Txtgateway->text();
    hostip="";
    connectport=0;
    Createxml();
    emit Reloadxml();
    SetNetwork();
    Readxml();

//    Readxml();
}
void settings::Createxml()
{
    QReadWriteLock locker;
    locker.lockForWrite();
    QFile db(pathdir+"/configure.xml");
    if(!db.exists())
    {
        db.open((QIODevice::ReadWrite|QIODevice::Text));
        db.close();
    }
    db.open(QIODevice::WriteOnly|QIODevice::Truncate);

    QDomDocument doc;
    QDomElement root=doc.createElement("settings");
    doc.appendChild(root);

    QDomElement ip_local=doc.createElement("localip");
    QDomText elementval;
    QDomAttr id;
    elementval=doc.createTextNode(localip);
    ip_local.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("0");
    ip_local.setAttributeNode(id);
    root.appendChild(ip_local);

    QDomElement ip_host=doc.createElement("hostip");
//    QDomText elementval;
    elementval=doc.createTextNode(hostip);
    ip_host.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("1");
    ip_host.setAttributeNode(id);
    root.appendChild(ip_host);

    QDomElement sub_mask=doc.createElement("subnetmask");
    elementval=doc.createTextNode(subnetmask);
    sub_mask.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("2");
    sub_mask.setAttributeNode(id);
    root.appendChild(sub_mask);

    QDomElement _gateway=doc.createElement("gateway");
    elementval=doc.createTextNode(gateway);
    _gateway.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("3");
    _gateway.setAttributeNode(id);
    root.appendChild(_gateway);

    QDomElement _listenport=doc.createElement("listenport");
    elementval=doc.createTextNode(QString::number(listenport));
    _listenport.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("4");
    _listenport.setAttributeNode(id);
    root.appendChild(_listenport);

    QDomElement _year=doc.createElement("year");
    elementval=doc.createTextNode(QString::number(year));
    _year.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("5");
    _year.setAttributeNode(id);
    root.appendChild(_year);

    QDomElement _month=doc.createElement("month");
    elementval=doc.createTextNode(QString::number(month));
    _month.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("6");
    _month.setAttributeNode(id);
    root.appendChild(_month);

    QDomElement _day=doc.createElement("day");
    elementval=doc.createTextNode(QString::number(day));
    _day.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("7");
    _day.setAttributeNode(id);
    root.appendChild(_day);

    QDomElement _hour=doc.createElement("hour");
    elementval=doc.createTextNode(QString::number(hour));
    _hour.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("8");
    _hour.setAttributeNode(id);
    root.appendChild(_hour);

    QDomElement _minute=doc.createElement("minute");
    elementval=doc.createTextNode(QString::number(minute));
    _minute.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("9");
    _minute.setAttributeNode(id);
    root.appendChild(_minute);

    QDomElement hr_max=doc.createElement("hrmax");
    elementval=doc.createTextNode(QString::number(hrmax));
    hr_max.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("10");
    hr_max.setAttributeNode(id);
    root.appendChild(hr_max);

    QDomElement hr_min=doc.createElement("hrmin");
    elementval=doc.createTextNode(QString::number(hrmin));
    hr_min.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("11");
    hr_min.setAttributeNode(id);
    root.appendChild(hr_min);

    QDomElement spo2_max=doc.createElement("spo2max");
    elementval=doc.createTextNode(QString::number(spo2max));
    spo2_max.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("12");
    spo2_max.setAttributeNode(id);
    root.appendChild(spo2_max);

    QDomElement spo2_min=doc.createElement("spo2min");
    elementval=doc.createTextNode(QString::number(spo2min));
    spo2_min.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("13");
    spo2_min.setAttributeNode(id);
    root.appendChild(spo2_min);

    QDomElement dias_max=doc.createElement("diasmax");
    elementval=doc.createTextNode(QString::number(diasmax));
    dias_max.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("14");
    dias_max.setAttributeNode(id);
    root.appendChild(dias_max);

    QDomElement dias_min=doc.createElement("diasmin");
    elementval=doc.createTextNode(QString::number(diasmin));
    dias_min.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("15");
    dias_min.setAttributeNode(id);
    root.appendChild(dias_min);

    QDomElement aver_max=doc.createElement("avermax");
    elementval=doc.createTextNode(QString::number(avermax));
    aver_max.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("16");
    aver_max.setAttributeNode(id);
    root.appendChild(aver_max);

    QDomElement aver_min=doc.createElement("avermin");
    elementval=doc.createTextNode(QString::number(avermin));
    aver_min.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("17");
    aver_min.setAttributeNode(id);
    root.appendChild(aver_min);

    QDomElement sys_max=doc.createElement("sysmax");
    elementval=doc.createTextNode(QString::number(sysmax));
    sys_max.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("18");
    sys_max.setAttributeNode(id);
    root.appendChild(sys_max);

    QDomElement sys_min=doc.createElement("sysmin");
    elementval=doc.createTextNode(QString::number(sysmin));
    sys_min.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("19");
    sys_min.setAttributeNode(id);
    root.appendChild(sys_min);

    QDomElement temp_max=doc.createElement("tempmax");
    elementval=doc.createTextNode(QString::number(tempmax));
    temp_max.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("20");
    temp_max.setAttributeNode(id);
    root.appendChild(temp_max);

    QDomElement temp_min=doc.createElement("tempmin");
    elementval=doc.createTextNode(QString::number(tempmin));
    temp_min.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("21");
    temp_min.setAttributeNode(id);
    root.appendChild(temp_min);

    QDomElement glu_max=doc.createElement("glumax");
    elementval=doc.createTextNode(QString::number(glumax));
    glu_max.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("22");
    glu_max.setAttributeNode(id);
    root.appendChild(glu_max);

    QDomElement glu_min=doc.createElement("glumin");
    elementval=doc.createTextNode(QString::number(glumin));
    glu_min.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("23");
    glu_min.setAttributeNode(id);
    root.appendChild(glu_min);

    QDomElement _connectport=doc.createElement("connectport");
    elementval=doc.createTextNode(QString::number(connectport));
    _connectport.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("24");
    _connectport.setAttributeNode(id);
    root.appendChild(_connectport);

    QDomElement _buzzing=doc.createElement("Isbuzzing");
    elementval=doc.createTextNode(QString::number(Isbuzzing));
    _buzzing.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("25");
    _buzzing.setAttributeNode(id);
    root.appendChild(_buzzing);

    QDomElement _langue=doc.createElement("Langue");
    elementval=doc.createTextNode(SysLangue);
    _langue.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("26");
    _langue.setAttributeNode(id);
    root.appendChild(_langue);

    QTextStream out(&db);
    out.setCodec("UTF-8");
    doc.save(out,4);
    db.close();
    locker.unlock();
}

void settings::Readxml()
{
    QFile file(pathdir+"/configure.xml");
    if(!file.exists())
        return;
    file.open(QIODevice::ReadOnly|QFile::Text);

    QDomDocument doc;
    QString element;
    QString value;
    QString temp;
    QString glu;
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
                hostip=value;
                break;
            case 2:
                subnetmask=value;
                break;
            case 3:
                gateway=value;
                break;
            case 4:
                listenport=value.toInt();
                break;
            case 5:
                year=value.toInt();
                break;
            case 6:
                month=value.toInt();
                break;
            case 7:
                day=value.toInt();
                break;
            case 8:
                hour=value.toInt();
                break;
            case 9:
                minute=value.toInt();
                break;
            case 10:
                hrmax=value.toInt();
                break;
            case 11:
                hrmin=value.toInt();
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
                temp= QString::number(value.toDouble(),'f',1);
                tempmax=temp.toDouble();
                break;
            case 21:
                temp=QString::number(value.toDouble(),'f',1);
                tempmin=temp.toDouble();
                break;
            case 22:
                glu= QString::number(value.toDouble(),'f',1);
                glumax=glu.toDouble();
                break;
            case 23:
                glu=QString::number(value.toDouble(),'f',1);
                glumin=glu.toDouble();
                break;
            case 24:
//                connectport=value.toInt();
                break;
            case 25:
                Isbuzzing=value.toInt();
                break;
            case 26:
                SysLangue=value;
                if(SysLangue=="Chinese")
                    IsChinese=true;
                else
                    IsChinese=false;
                break;
            }
        }
        node=node.nextSibling();
    }
    ui->TxthrMax->setText(QString::number(hrmax));
    ui->TxthrMin->setText(QString::number(hrmin));
    ui->Txtspo2Max->setText(QString::number(spo2max));
    ui->Txtspo2Min->setText(QString::number(spo2min));
    ui->TxtdiasMax->setText(QString::number(diasmax));
    ui->TxtdiasMin->setText(QString::number(diasmin));
    ui->TxtaverMax->setText(QString::number(avermax));
    ui->TxtaverMin->setText(QString::number(avermin));
    ui->TxtsysMax->setText(QString::number(sysmax));
    ui->TxtsysMin->setText(QString::number(sysmin));
//    ui->Txtyear->setText(QString::number(year));
//    ui->Txtmonth->setText(QString::number(month));
//    ui->Txtday->setText(QString::number(day));
//    ui->Txthour->setText(QString::number(hour));
//    ui->Txtminute->setText(QString::number(minute));
    ui->TxttempMax->setText(QString::number(tempmax,'f',1));
    ui->TxttempMin->setText(QString::number(tempmin,'f',1));
    ui->TxtgluMax->setText(QString::number(glumax,'f',1));
    ui->TxtgluMin->setText(QString::number(glumin,'f',1));
    ui->TxtListenport->setText(QString::number(listenport));
    ui->TxtlocalIP->setText(localip);
    ui->Txtsubnetmask->setText(subnetmask);
    ui->Txtgateway->setText(gateway);
    file.close();

}
void settings::Loadsettinglangue(bool langue)
{
    if(langue)
    {
        ui->btnDelete->setText(QString::fromUtf8("删除"));
        ui->btnOK->setText(QString::fromUtf8("确认"));
        ui->btnsettime->setText(QString::fromUtf8("时间设置"));
        ui->btndatacalibrate->setText(QString::fromUtf8("校准"));
        ui->lab_pralarm->setText(QString::fromUtf8("脉率报警"));
        ui->lab_glualarm->setText(QString::fromUtf8("血糖报警"));
        ui->lab_spo2alarm->setText(QString::fromUtf8("血氧报警"));
        ui->lab_tempalarm->setText(QString::fromUtf8("体温报警"));
        ui->lab_sysalarm->setText(QString::fromUtf8("收缩压报警"));
        ui->lab_diaalarm->setText(QString::fromUtf8("舒张压报警"));
        ui->lab_averalarm->setText(QString::fromUtf8("平均压报警"));
        ui->lab_buzzing->setText(QString::fromUtf8("蜂鸣设置"));
        ui->lab_langue->setText(QString::fromUtf8("语言设置"));
//        ui->lab_buzzing->setText(QString::fromUtf8("时间设置"));
        ui->lab_hrtop->setText(QString::fromUtf8("上限"));
        ui->lab_hrlow->setText(QString::fromUtf8("下限"));
        ui->lab_glutop->setText(QString::fromUtf8("上限"));
        ui->lab_glulow->setText(QString::fromUtf8("下限"));
        ui->lab_spo2top->setText(QString::fromUtf8("上限"));
        ui->lab_spo2low->setText(QString::fromUtf8("下限"));
        ui->lab_temptop->setText(QString::fromUtf8("上限"));
        ui->lab_templow->setText(QString::fromUtf8("下限"));
        ui->lab_systop->setText(QString::fromUtf8("上限"));
        ui->lab_syslow->setText(QString::fromUtf8("下限"));
        ui->lab_diatop->setText(QString::fromUtf8("上限"));
        ui->lab_dialow->setText(QString::fromUtf8("下限"));
        ui->lab_avertop->setText(QString::fromUtf8("上限"));
        ui->lab_averlow->setText(QString::fromUtf8("下限"));
        ui->lab_time->setText(QString::fromUtf8("时间"));
        ui->lab_date->setText(QString::fromUtf8("日期"));
        ui->lab_gateway->setText(QString::fromUtf8("网关"));
        ui->lab_localip->setText(QString::fromUtf8("本机IP"));
        ui->lab_systemset->setText(QString::fromUtf8("系\n统\n配\n置"));
        ui->lab_port->setText(QString::fromUtf8("端口"));
        ui->lab_subnetmask->setText(QString::fromUtf8("掩码"));
//        ui->lab_localip->setGeometry(80,70,121,41);
//        ui->lab_gateway->setGeometry(570,70,81,41);
//        ui->lab_subnetmask->setGeometry(570,140,81,41);
        ui->btnlangueText->setText(QString::fromUtf8("中  文"));
        if(!Isbuzzing)
            ui->btnbuzzing->setText(QString::fromUtf8("静  音"));
        else
            ui->btnbuzzing->setText(QString::fromUtf8("蜂  鸣"));
    }
    else
    {
        ui->btnDelete->setText("DEL");
        ui->btnOK->setText("OK");
        ui->btnsettime->setText("Time Set");
        ui->btndatacalibrate->setText("Cal");
        ui->lab_pralarm->setText("HR Alarm");
        ui->lab_glualarm->setText("GLU Alarm");
        ui->lab_spo2alarm->setText("SPO2 Alarm");
        ui->lab_tempalarm->setText("BT Alarm");
        ui->lab_sysalarm->setText("SBP Alarm");
        ui->lab_diaalarm->setText("DBP Alarm");
        ui->lab_averalarm->setText("MAP Alarm");
//        ui->gpbuzzing->setTitle("Buzzing Set");
        ui->lab_langue->setText("Langue Set");
        ui->lab_buzzing->setText("Buzzing Set");
        ui->lab_hrtop->setText("Max");
        ui->lab_hrlow->setText("Min");
        ui->lab_glutop->setText("Max");
        ui->lab_glulow->setText("Min");
        ui->lab_spo2top->setText("Max");
        ui->lab_spo2low->setText("Min");
        ui->lab_temptop->setText("Max");
        ui->lab_templow->setText("Min");
        ui->lab_systop->setText("Max");
        ui->lab_syslow->setText("Min");
        ui->lab_diatop->setText("Max");
        ui->lab_dialow->setText("Min");
        ui->lab_avertop->setText("Max");
        ui->lab_averlow->setText("Min");
        ui->lab_time->setText("Time");
        ui->lab_date->setText("Date");
        ui->lab_gateway->setText("Gateway");
        ui->lab_localip->setText("LocalIP");
        ui->lab_systemset->setText("Sys\nSet");
        ui->lab_port->setText("Port");
        ui->lab_subnetmask->setText("Mask");
//        ui->lab_localip->setGeometry(60,70,121,41);
//        ui->lab_gateway->setGeometry(520,70,141,41);
//        ui->lab_subnetmask->setGeometry(470,140,211,41);
        ui->btnlangueText->setText("English");
        if(!Isbuzzing)
            ui->btnbuzzing->setText(QString::fromUtf8("Slience"));
        else
            ui->btnbuzzing->setText(QString::fromUtf8("Buzzing"));
    }
}

void settings::SetNetwork()
{
    QReadWriteLock locker;
    locker.lockForWrite();
    QString cmd_set;
    cmd_set="auto eth0\niface eth0 inet static\naddress "+localip+"\ngateway "+gateway+"\nnetmask "+subnetmask;
    QFile networkset("/etc/network/interfaces");
    if(!networkset.open(QIODevice::WriteOnly|QIODevice::Truncate))
        return;
    QTextStream txtoutput(&networkset);
    txtoutput<<cmd_set<<endl;
    networkset.close();
    QString cmd_ifconfig="sudo ifconfig eth0 "+localip+" netmask "+subnetmask;
    QString cmd_routedel="sudo route del default";
    QString cmd_routeadd="sudo route add default gw "+gateway;
    system(cmd_ifconfig.toLatin1().data());
    system(cmd_routedel.toLatin1().data());
    system(cmd_routeadd.toLatin1().data());
    locker.unlock();
//    emit ReListentcp();

    //    system(cmd_intf.toLatin1().data());
    //    system(cmd_edit.toLatin1().data());
    //    system(cmd_set.toLatin1().data());
    //    system(cmd_exit.toLatin1().data());
    //    QString cmd_sehll="sudo vi /home/linaro/work/GPmonitor/shellip";
    //    QString cmd_ip="sudo ifconfig eth0 "+localip+" netmask "+subnetmask;
    //    QString cmd_ip2="sudo ifconfig eth0 192.168.1.100 netmask 255.255.255.0";
    //    system(cmd_ip.toLatin1().data());
    //    system(cmd_ip2.toLatin1().data());

}
void settings::SetsysTime()
{
    second=ui->Txtsecond->text().toInt();
    year=ui->Txtyear->text().toInt();
    month=ui->Txtmonth->text().toInt();
    day=ui->Txtday->text().toInt();
    hour=ui->Txthour->text().toInt();
    minute=ui->Txtminute->text().toInt();
    QString detialtime="\""+QString::number(year)+"-"+QString::number(month)+"-"+QString::number(day)+" "+QString::number(hour)+":"+QString::number(minute)+":"+QString::number(second)+"\"";
    QString cmd_date="sudo date -s "+detialtime;
    system(cmd_date.toLatin1().data());
    QString cmd_clock="#clock -w";
    system(cmd_clock.toLatin1().data());
}

void settings::on_btnsettime_clicked()
{
    SetsysTime();
}

/*
//bool settings::eventFilter(QObject *obj, QEvent *eve)
//{

//        if(obj==ui->TxthostIP)
//        {
//            if(eve->type()==QEvent::FocusIn)
//            {
//            ui->TxthostIP->selectAll();
//            }
//        }
//        else if(obj==ui->TxtlocalIP)
//        {

//        }
//        else if(obj==ui->Txtgateway)
//        {

//        }
//        else if(obj==ui->Txtsubnetmask)
//        {

//        }
//        else if(obj==ui->TxtaverMax)
//        {

//        }
//        else if(obj==ui->TxtaverMin)
//        {

//        }
//        else if(obj==ui->TxtdiasMax)
//        {

//        }
//        else if(obj==ui->TxtdiasMin)
//        {

//        }
//        else if(obj==ui->TxthrMax)
//        {

//        }
//        else if(obj==ui->TxthrMin)
//        {

//        }
//        else if(obj==ui->Txtspo2Max)
//        {

//        }
//        else if(obj==ui->Txtspo2Min)
//        {

//        }
//        else if(obj==ui->TxtsysMax)
//        {

//        }
//        else if(obj==ui->TxtsysMin)
//        {

//        }
//        else if(obj==ui->TxtsysMin)
//        {

//        }
//        else if(obj==ui->TxttempMax)
//        {
//            ui->TxttempMax->selectAll();
//        }
//        else if(obj==ui->TxttempMin)
//        {

//        }
//        else if(obj==ui->TxtgluMax)
//        {

//        }
//        else if(obj==ui->TxtgluMin)
//        {

//        }
//        else if(obj==ui->Txtport)
//        {

//        }
//        else if(obj==ui->Txtyear)
//        {

//        }
//        else if(obj==ui->Txtday)
//        {

//        }
//        else if(obj==ui->Txtmonth)
//        {

//        }
//        else if(ui->Txthour->hasFocus())
//        {

//        }
//        else if(ui->Txtminute->hasFocus())
//        {

//        }

//    return true;
}
*/

void settings::on_btndatacalibrate_clicked()
{
    // TODO 进入手动测量
    qDebug()<<"发送命令，关闭阀门";
    emit closeValve();
    calibrate->updateUI();

    emit langueload(IsChinese);
    if(calibrate->exec()==CalibrateDialog::Accepted)
        emit ReloadCalibratexml();
}

void settings::on_btnlangueUp_clicked()
{

    SysLangue="Chinese";
    ui->btnlangueText->setText(QString::fromUtf8("中  文"));
}

void settings::on_btnlangueDown_clicked()
{

    SysLangue="English";
    ui->btnlangueText->setText(SysLangue);
}

void settings::on_btnBuzzingUp_clicked()
{
    Isbuzzing=0;
    if(IsChinese)
        ui->btnbuzzing->setText(QString::fromUtf8("静  音"));
    else
        ui->btnbuzzing->setText("Slience");
}

void settings::on_btnBuzzingDown_clicked()
{
    Isbuzzing=1;
    if(IsChinese)
        ui->btnbuzzing->setText(QString::fromUtf8("蜂  鸣"));
    else
        ui->btnbuzzing->setText("Buzzing");
}

void settings::sendOpenSig() {
    emit openValve();
}

void settings::updateData(int data) {
    if(calibrate){
        calibrate->updateData(data);
    }
}
