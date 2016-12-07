#include "mainform.h"
#include "ui_mainform.h"
#include "comdefs.h"
#include <QDebug>
#include "IRCommand.h"
#include <QtXml>
#include <QTextCodec>
#include <QGradient>

char gPackLength[128]=
{
    0  , //  00:
    2  , //  01: ϵͳλϢ
    5  , //  02: ϵͳ״̬
    9  , //  03: ϵͳԼ
    5  , //  04: Ӧ
    8  , //  05: ECG
    5  , //  06: ӺźϢ
    5  , //  07:
    0  , //  08:
    0  , //  09:
    0  , //  0a:
    7  , //  0b: STƫ
    9  , //  0c: STβֵ
    0  , //  0d:
    0  , //  0e:
    0,  //  0f:
    4,  //  10:
    5,  //  11:
    6,  //  12: Ϣ
    4,  //  13: CVAϢ
    0,  //  14:
    8,  //  15:
    5,  //  16: SPO2
    7,  //  17: SPO2
    7,  //  18: IBP
    4,  //  19: IBP״̬
    10,  //  1a: IBPѹ
    6,  //  1b: IBPУУ׼Ϣ
    7,  //  1c: IBPУУ׼ʱ
    0,  //  1d:
    0,  //  1e:
    0,  //  1f:
    7,  //  20: NBPʵʱ
    4,  //  21: NBP
    9,  //  22: NBP1
    5,  //  23: NBP2
    8,  //  24: NBP״̬
    0,  //  25:
    0,  //  26:
    0,  //  27:
    0,  //  28:
    0,  //  29:
    0,  //  2a:
    0,  //  2b:
    0,  //  2c:
    0,  //  2d:
    0,  //  2e:
    0,  //  2f:
    0,  //  30:
    0,  //  31:
    0,  //  32:
    0,  //  33:
    0,  //  34:
    0,  //  35:
    0,  //  36:
    0,  //  37:
    0,  //  38:
    0,  //  39:
    0,  //  3a:
    0,  //  3b:
    0,  //  3c:
    0,  //  3d:
    0,  //  3e:
    0,  //  3f:
    2,  //  40: ȡԼ
    4,  //  41: ѡ
    4,  //  42: Ϣ
    0,  //  43:
    0,  //  44:
    4,  //  45: ģʽѡ:3,5
    4,  //  46: ʽѡ
    4,  //  47: ˲ʽѡ
    4,  //  48: ĵ
    4,  //  49: 1mVУ׼ź
    4,  //  4a: Ƶ
    4,  //  4b: 𲫷
    7,  //  4c: STISOST
    4,  //  4d: ĵͨ
    2,  //  4e: ĵѧϰ
    0,  //  4f:
    4,  //  50:
    0,  //  51:
    4,  //  52: Ϣʱѡ
    4,  //  53: ̽ͷ
    4,  //  54: SPO2
    2,  //  55: NBPʼһֶ/Զ
    2,  //  56: NBP
    4,  //  57: NBP
    2,  //  58: NBPʼУ׼
    2,  //  59: NBPλ
    2,  //  5a: NBP©
    2,  //  5b: NBPѯ״̬
    5,  //  5c: NBPóγѹ
    2,  //  5d: NBPʼSTAT
    2,  //  5e: NBPѯ
    0,  //  5f:
    4,  //  60: IBPѹ
    4,  //  61: IBPУ
    7,  //  62: IBP1У׼
    7,  //  63: IBP2У׼
    4,  //  64: ˲ģʽ
    5,  //  65: IBPѯ
    0,  //  66:
    0,  //  67:
    0,  //  68:
    0,  //  69:
    0,  //  6a:
    0,  //  6b:
    0,  //  6c:
    0,  //  6d:
    0,  //  6e:
    0,  //  6f:
    0,  //  70:
    0,  //  71:
    0,  //  72:
    0,  //  73:
    0,  //  74:
    0,  //  75:
    0,  //  76:
    0,  //  77:
    0,  //  78:
    0,  //  79:
    0,  //  7a:
    0,  //  7b:
    0,  //  7c:
    0,  //  7d:
    0,  //  7e:
    0,  //  7f:
};

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
//    QLinearGradient linegradient(0,0,1366,768);
//    linegradient.setColorAt(0.2,QColor::fromRgb(255,255,255));
//    linegradient.setColorAt(0.4,QColor::fromRgb(0,0,0));
//    paint.setBrush(QBrush(linegradient));
//    paint.drawEllipse(0,0,1366,768);
//    this->setStyleSheet("background-image: url(:/rsc/images/logo.png);");
    monitorform = new MonitorForm(this);
    waveform = new WaveForm(this);
    visualchart = new VisualChart(this);
    colorchart = new ColorChart(this);
    setting = new settings(this);
    passwordform =new PassWordDialog(this);
    resetform=new ResetDialog(this);
    connect(this,SIGNAL(ChineseLangue(bool)),waveform,SLOT(LoadConfigure(bool)));
    connect(this,SIGNAL(ChineseLangue(bool)),visualchart,SLOT(LoadLangue(bool)));
    connect(this,SIGNAL(ChineseLangue(bool)),colorchart,SLOT(Loadcolorlangue(bool)));
    connect(this,SIGNAL(ChineseLangue(bool)),setting,SLOT(Loadsettinglangue(bool)));
    connect(this,SIGNAL(ChineseLangue(bool)),passwordform,SLOT(Loadpswlangue(bool)));
    connect(this,SIGNAL(ChineseLangue(bool)),resetform,SLOT(Loadresetlangue(bool)));
    QDir dir;
    pathdir=dir.currentPath();
    Loadxml();
    ui->mainLayout->addWidget(monitorform,1);
    ui->mainLayout->addWidget(waveform,1);
    ui->mainLayout->addWidget(visualchart,1);
    ui->mainLayout->addWidget(colorchart,1);
    ui->mainLayout->addWidget(setting,1);
    IsNIBP=false;
    IsAtSetting=false;
    IsRebooting=false;
    sendecgcnt=0;
    paraint=0;
    IsOneSec=true;
    ecgloopcount=0;
    IsSendecg=0;
    idx_Mini=2;
    currenttimer=new QTimer(this);
    connect(currenttimer,SIGNAL(timeout()),this,SLOT(timeevent()));
    currenttimer->start(1000);
    on_btnMonitor_clicked();
    connect(monitorform,SIGNAL(BPTest()),this,SLOT(BPStart()));
//    connect(monitorform,SIGNAL(GlucoseTest()),this,SLOT(GlucoseStart()));
    connect(monitorform,SIGNAL(BPTestEND()),this,SLOT(BPEND()));
    connect(waveform,SIGNAL(ECGSIGNAL(char,int,int)),this,SLOT(ECGSet(char,int,int)));
    connect(monitorform,SIGNAL(PatientType(unsigned char)),this,SLOT(PatienttypeSet(unsigned char)));
    connect(setting,SIGNAL(Reloadxml()),monitorform,SLOT(Loadxml()));
    connect(setting,SIGNAL(Reloadxml()),this,SLOT(StartListen()));
    connect(this,SIGNAL(Clearpswtxt()),passwordform,SLOT(Cleartxt()));
    connect(this,SIGNAL(printcommand()),monitorform,SLOT(printSlot()));
    connect(monitorform,SIGNAL(print(double *)),this,SLOT(printData(double *)));
    connect(setting,SIGNAL(Reloadxml()),this,SLOT(Loadxml()));
    connect(this,SIGNAL(setbuzzingoff()),monitorform,SLOT(setisbuzzing()));
//    connect(this,SIGNAL(datareset()),monitorform,SLOT(on_btnDataReSet_clicked()));
//    connect(this,SIGNAL(receivedata(QString)),this,SLOT(TcpReceived(QString)));
    connect(this,SIGNAL(wavereflesh(bool)),waveform,SLOT(SetReflesh(bool)));
    connect(setting,SIGNAL(ReloadCalibratexml()),monitorform,SLOT(ReadCalibratexml()));
    connect(monitorform,SIGNAL(senddata(QString)),this,SLOT(MiniusbDataSend(QString)));
    connect(this,SIGNAL(AccuData(double)),monitorform,SLOT(AccuRecieved(double)));
    connect(waveform,SIGNAL(SendECGInfo(QString)),this,SLOT(ECGInfoSet(QString)));
    InitCom();
//    InitUsbCom();
    InitTempCom();
    InitIRACCUCom();
    InitPrintCom();
    InitMiniusbCom();
//    InitIRCom();
    MiniComLoopcount=0;
    InitMinicount=0;
    IsMiniReceived=false;
    IsMiniOutLink=true;
    AccuSendCount=0;
    btnHandlers[0] = &MainForm::on_btnMonitor_clicked;
    btnHandlers[1] = &MainForm::on_btnWave_clicked;
    btnHandlers[2] = &MainForm::on_btnVisualChart_clicked;
    btnHandlers[3] = &MainForm::on_btnColorChart_clicked;
    btnHandlers[4] = &MainForm::on_btnSettings_clicked;
    btnidx = 0;
    connect(this, SIGNAL(DispatchIRData(unsigned char)),colorchart, SLOT(IRProc(unsigned char)));
    connect(this,SIGNAL(DispatchIRData(unsigned char)), visualchart, SLOT(IRProc(unsigned char)));
    connect(this,SIGNAL(DispatchIRData(unsigned char)),monitorform,SLOT(IRProc(unsigned char)));
//    ui->frame->setStyleSheet("background-image: url(:/rsc/images/logo.png);");
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    tcpserver=new QTcpServer(this);
    clientconnection=new QTcpSocket(this);
    StartListen();
    ECGSet(CMD_LEADTYPE,1,1);
    ECGSet(CMD_LEADTYPE,2,0);
    ui->btnprint->setStyleSheet("background-color: rgb(0,0,0);");
    ui->btnreset->setStyleSheet("background-color: rgb(0,0,0);");
//    QTextCodec::SET(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    isCal = false;
    connect(setting, SIGNAL(closeValve()), this, SLOT(enterManualMode()));
    connect(setting, SIGNAL(openValve()), this, SLOT(exitManualMode()));
}

MainForm::~MainForm()
{
    delete ui;

    delete monitorform;
    delete waveform;
    delete visualchart;
    delete colorchart;
    delete passwordform;
    delete resetform;

#if(WIN32)
    delete myCom;
    delete usbCom;
    delete irCom;
#else
//    myCom->closeSerialPort();
//    usbCom->closeSerialPort();
    myCom->close();
//    usbCom->close();
    irCom->close();
    TempCom->close();
    MiniusbCom->close();
    printCom->close();
#endif
}

void MainForm::InitCom()
{
#if(WIN32)
    //崮ڶָͲѯģʽʹ¼EventDriven
    myCom =new Win_QextSerialPort("COM1",QextSerialBase::EventDriven);
    myCom ->open(QIODevice::ReadWrite);
    //Զдʽ򿪴
    myCom->setBaudRate(BAUD115200);
    //ãΪ115200
    myCom->setDataBits(DATA_8);
    //λãΪ8λλ
    myCom->setParity(PAR_NONE);
    //żУãΪУ
    myCom->setStopBits(STOP_1);
    //ֹͣλãΪ1λֹͣλ
    myCom->setFloowControl(FLOW_OFF);
    //ãΪ
    myCom->setTimeout(500);
    //ʱãΪʱ500ms,Woindowsº
    connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
    //źźͲۺڻʱж
#else
//    myCom =new SerialBase();
//    myCom->openSerialPort("/dev/ttymxc3",BAUD115200,PAR_NONE, DATA_8,STOP_1);
//    connect(myCom, SIGNAL(dataUpdated(QByteArray)), this, SLOT(comDataReceived(QByteArray)));
    myCom = new ManageSerialPort("/dev/ttymxc1",BAUD115200, DATA_8, PAR_NONE,STOP_1,FLOW_OFF,0,50);
    bool isOpen = myCom->open();
    if(isOpen)
    {
        //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
        connect(myCom,SIGNAL(newDataReceived(const QByteArray &)),this,SLOT(comDataReceived(const QByteArray&)));

        myCom->enableReceiving();
        myCom->enableSending();
        myCom->receiveData();
    }
#endif

}

void MainForm::readMyCom() //ȡݲʾ
{
#if(WIN32)
    QByteArray temp = myCom->readAll();
    comDataReceived(temp);
#endif
}

/********************************************************************
 *  Ӵڽջн
 *
 *  data     ڻָ룻
 *  len      ҪĴڻݳȣ
 *ֵ
*          0:  OK
 *        -1:  ȴ
 *        -2:  Уʹ
 *******************************************************************/
void MainForm::comDataReceived(const QByteArray &temp)
{
    static unsigned char sCurrPacket[10];
    static int        sPacketIdFound = 0;/*ܵIDı־1ʾյ*/
    static int        sCurrPacketLen;/*ǰܵİ*/

    unsigned char *data = (unsigned char*)temp.data();
    int length = temp.length();

    unsigned char  current_data;
    int   result = 0;
    /* ȡ */
    while (length > 0)
    {
        current_data = * data;
        /* յֽ */
        if ( sPacketIdFound ){
            /* ǰֽڣЧֽڱڵ0x80 */

            if (current_data >= 0x80 ){
                //
                if(sCurrPacketLen<10)
                    sCurrPacket [sCurrPacketLen++] = current_data;

                /* յݣʼ */
                if (sCurrPacketLen ==  gPackLength [sCurrPacket [0]]) {
                    result=UnPackData(sCurrPacket,sCurrPacketLen);
                    if ( 0 == result ){
                        DispatchData(sCurrPacket, sCurrPacketLen);
                    }
                    sPacketIdFound = 0;
                }
            }else{
                /*ǰС0x80, ضǴECG1LeadSet */
                sPacketIdFound = 0;
                result = -1;
            }
        }else if(current_data<0x80){
            /* 鵱ǰֽǷȷİID */
            if (gPackLength [current_data] > 0 )
            {
                sCurrPacketLen = 1;
                sCurrPacket[0] = current_data;
                sPacketIdFound   = 1;
            }else {
                /* ǰݲȷİ */
                result = -1;
            }
        }
        /* ָһ */
        data ++;
        /* ݳȼ1 */
        length --;
    }
}

int  MainForm::UnPackData(unsigned char *  pack, int  len)
{
    unsigned char  head;
    int  i;
    unsigned char checksum;

    if ( len < 2 )
        return -1;

    /* ʼУ */
    checksum  = *(pack);

    if ( 2 < len ){
        head = *(pack+1);
        /* Уͼͷ */
        checksum += head;

        for (i = 1; i < len - 2; i ++) {
            /* У */
            checksum += *(pack+i+1);
            *(pack+i) = (*(pack+i+1)&0x7f) | ( (head&0x1)<<7 );
            head >>= 1;
        }
    }
    if ( (checksum & 0x7f) != ((*(pack+len-1)) &0x7f) )
        return -2;
    return 0;
}

int  MainForm::UnPackTmepData(unsigned char *  pack, int  len)
{
    unsigned char checksum;
    int temp1;
    int temp2;
    int temp3;
    int temp4;
    int checkhigh;
    int checklow;
    int temphigh;
    int templow;
    QByteArray tmp;

    if ( len < 2 )
        return -1;

    /* ʼУ */
    checksum  = *(pack);

    if ( 2 < len ){
        checksum=(QString::number(*(pack),16).toInt());
        temp1=(QString::number(*(pack+1),16).toInt())-30;
        temp2=QString::number(*(pack+2),16).toInt()-30;
        temp3=QString::number(*(pack+3),16).toInt()-30;
        temp4=QString::number(*(pack+4),16).toInt()-30;
        templow=temp2+temp4;
        temphigh=(short)checksum+temp1*10+temp3*10;
        if(templow>=10)
        {
//            temphigh+=1;
            if(templow<16)
            {
                switch(templow)
                {
                case 10:
                    templow=65;
                    break;
                case 11:
                    templow=66;
                    break;
                case 12:
                    templow=67;
                    break;
                case 13:
                    templow=68;
                    break;
                case 14:
                    templow=69;
                    break;
                case 15:
                    templow=70;
                    break;
                }
            }
            else
            {
                templow-=16;
            }
        }
        if(templow<10)
            templow+=48;
        temphigh=temphigh/10;
        if(temphigh>=10)
        {
            if(temphigh<16)
            {
                switch(temphigh)
                {
                case 10:
                    temphigh=65;
                    break;
                case 11:
                    temphigh=66;
                    break;
                case 12:
                    temphigh=67;
                    break;
                case 13:
                    temphigh=68;
                    break;
                case 14:
                    temphigh=69;
                    break;
                case 15:
                    temphigh=70;
                    break;
                }
            }
            else
                temphigh-=16;
        }
        if(temphigh<10)
            temphigh+=48;
        checkhigh= *(pack+5);
        checklow=*(pack+6);

    }
    if(checkhigh!=temphigh||checklow!=templow)
        return -2;
    return 0;
}
void MainForm::DispatchData(unsigned char *  data, int  length)
{
    switch(data[0])
    {
        case ID_HR:
            waveform->updateHrData(data[0],(short)(data[1]*256+data[2]));
            break;
        case ID_SPO2_PR:
            monitorform->UpdateData(data[0],(char)data[4],(short)(data[2]*256+data[3]));
            break;
        case ID_TEMP_ETG:
        {
            int temp1=(QString::number(data[1],16).toInt())-30;
            int temp2=QString::number(data[2],16).toInt()-30;
            int temp3=QString::number(data[3],16).toInt()-30;
            int temp4=QString::number(data[4],16).toInt()-30;
            if(temp4>=5)
                temp3+=1;
            monitorform->UpdateData(data[0],(double)(temp1*10+temp2+temp3*0.1));
        }
            break;

        // 增加实时压力值显示
        case ID_NBP_CUFPRE:
            monitorform->UpdateData(data[0], (short)(data[1]*256 + data[2]), data[3], data[4]);
            if (isCal){
                setting->updateData((short)(data[1]*256 + data[2]));
            }
            break;

        case ID_NBP_END:
            monitorform->UpdateData(data[0], (short)data[1]);
            break;
        case ID_NBP_RESULT1:
            monitorform->UpdateData(data[0],
                                (short)(data[1]*256+data[2]),
                                (short)(data[3]*256+data[4]),
                                (short)(data[5]*256+data[6]));
            break;
        //                    NIBPEND    case ID_NBP_RESULT2:
        //                            monitorform->UpdateData(data[0],(char)data);
        //                            break;
        case ID_ECGWAVE:
            waveform->updateECGWaveData(data[0],data[1]*256+data[2],data[3]*256+data[4],data[5]&0x01);
            if(++sendecgcnt>=8)
            {
                secgdata=QByteArray((const char*)data,length);
                QReadWriteLock locker;
                locker.lockForWrite();
                if(clientconnection->state()&QAbstractSocket::ConnectedState)
                {
                    clientconnection->write(secgdata);
                    clientconnection->flush();
    //                qDebug()<<ecgloopcount++;
                }
                else
                {
                    if(!IsMiniOutLink)
                    {
                        MiniusbCom->sendData(secgdata,1000);
                        qDebug()<<ecgloopcount++;
                    }
                }
                locker.unlock();
                secgdata.clear();
                sendecgcnt=0;
            }
            break;
    case ID_SPO2_WAVE:
        monitorform->updateSPO2WaveData(data[0],data[1],data[2]);
        break;
//    case ID_GLUCOSE:
//        monitorform->UpdateData(0x30,(double)data[1]);
//        break;
    }
}

/********************************************************************
: ͵λ
:		pack----Ҫ͵ָ룬Ϊδ֯õID+DATA
ֵ:	ޡ
********************************************************************/
void  MainForm::SendCommand (unsigned char*  pack)
{
    unsigned char  head;
    int  i;
    unsigned char  checksum;

    int len = gPackLength [*pack];
    /* С2ֱӷ*/
    if(len<2)
        return;

    /* ʼ У */
    checksum = *(pack);

    if (len >=2 ){
        head = 0;
        for (i = len-2; i > 1; i --) {
            head <<= 1;
            /* λ1 */
            *(pack+i) = *(pack+i-1) | 0x80;
            /* У */
            checksum += *(pack+i);
            /* ͷ */
            head |= (*(pack+i-1)&0x80) >> 7;
        }
        /* ͷλ1 */
        *(pack+1) = head | 0x80;
        /* Уͼͷ */
        checksum += *(pack+1);

        /* У */
        *(pack+len-1) = checksum | 0x80;

        /* TODO: ûλڷ */
        /* uart.write(pack, len); */
//        QString val=new QString(pack,len);
#if(WIN32)
        myCom->write((const char*)pack,len);
#else
        QByteArray data((const char*)pack, len);
        myCom->sendData(data);
//        myCom->writeFrame((const char*)pack,len);
#endif
    }
}

void MainForm::InitUsbCom()
{
#if(WIN32)
    //崮ڶָͲѯģʽʹ¼EventDriven
    usbCom =new Win_QextSerialPort("COM10",QextSerialBase::EventDriven);
    usbCom ->open(QIODevice::ReadWrite);
    //Զдʽ򿪴
    usbCom->setBaudRate(BAUD9600);
    //ãΪ9600
    usbCom->setDataBits(DATA_8);
    //λãΪ8λλ
    usbCom->setParity(PAR_NONE);
    //żУãΪУ
    usbCom->setStopBits(STOP_1);
    //ֹͣλãΪ1λֹͣλ
    usbCom->setFlowControl(FLOW_OFF);
    //ãΪ
    usbCom->setTimeout(500);
    //ʱãΪʱ500ms,Windowsº
    connect(usbCom,SIGNAL(readyRead()),this,SLOT(readUsbCom()));
    //źźͲۺڻʱжڲ
#else
//    usbCom =new SerialBase();
//    usbCom->openSerialPort("/dev/ttyUSB0",BAUD9600,PAR_NONE,DATA_8,STOP_1);
//    connect(usbCom, SIGNAL(dataUpdated(QByteArray)), this, SLOT(usbDataReceived(QByteArray)));
    usbCom = new ManageSerialPort("/dev/ttyUSB0",BAUD9600, DATA_8, PAR_NONE,STOP_1,FLOW_OFF,0,50);
    bool isOpen = usbCom->open();
    if(isOpen)
    {
        //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
        connect(usbCom,SIGNAL(newDataReceived(const QByteArray &)),this,SLOT(usbDataReceived(const QByteArray &)));

        usbCom->enableReceiving();
        usbCom->enableSending();
        usbCom->receiveData();
    }
#endif
}

void MainForm::readUsbCom() //ȡݲʾ
{
#if(WIN32)
    const QByteArray temp = usbCom->readAll();
    usbDataReceived(temp);
#endif
}

void MainForm::usbDataReceived(const QByteArray &temp)
{
    static unsigned char sCurrPacket[10];
    static int        sPacketIdFound = 0;/*ܵIDı־1ʾյ*/
    static int        sCurrPacketLen;/*ǰܵİ*/
    static unsigned char chksum = 0;

    const unsigned char* data = (const unsigned char*)temp.constData();
    int length = temp.size();

    unsigned char  current_data;
    double val = 0.0;

    /* ȡ */
    while (length > 0)
    {
        current_data = * data;

        if ( sPacketIdFound == 0 && current_data == 0xeb)
            sPacketIdFound++;
        else if( sPacketIdFound == 1 && current_data == 0x90)
            sPacketIdFound++;
        else if ( sPacketIdFound == 2 && current_data == 0xfe)
        {
            chksum = 0;
            sPacketIdFound++;
        }
        else if ( sPacketIdFound == 3 && current_data == 0xd2)
        {
            chksum += current_data;
            sPacketIdFound++;
        }
        else if ( sPacketIdFound == 4 && current_data == 0x09)
        {
            chksum += current_data;
            sPacketIdFound++;
        }
        else if ( sPacketIdFound == 5 && current_data == 0x00) //item0
        {
            chksum += current_data;
            sPacketIdFound++;
            sCurrPacketLen = 0;
        }
        else if ( sPacketIdFound == 6)
        {
            //
            sCurrPacket [sCurrPacketLen++] = current_data;

            //
            if(sCurrPacketLen <= 8)
                chksum += current_data;
            else
            {
                if(chksum == current_data)
                {
                    val += (sCurrPacket[2]>>4) * 100.0;
                    val += (sCurrPacket[2] & 0x0f) * 10.0;
                    val += (sCurrPacket[3]>>4) * 1.0;
                    val += (sCurrPacket[3] & 0x0f) / 10.0;

                    monitorform->UpdateData(ID_GLUCOSE, val);
                }
                sPacketIdFound = 0;
            }
        }
        else
        {
            sPacketIdFound = 0;
        }

        /* ָһ */
        data ++;
        /* ݳȼ1 */
        length --;
    }
}
/********************************************************************
: ͵λ
:	ޡ
ֵ:	ޡ
********************************************************************/
void  MainForm::SendUsbCommand ()
{
    const char pack[] = {0x68, 0x52, 0x01, 0x01, 0x54, 0x16};
#if(WIN32)
    usbCom->write((const char*)pack,6);
#else
    QByteArray data(pack,6);
    usbCom->sendData(data);
//    usbCom->writeFrame((const char*)pack,6);
#endif
}

//void MainForm::InitIRCom()
//{
//#if(WIN32)
//    //崮ڶָͲѯģʽʹ¼EventDriven
//    irCom =new Win_QextSerialPort("COM2",QextSerialBase::EventDriven);
//    irCom ->open(QIODevice::ReadWrite);
//    //Զдʽ򿪴
//    irCom->setBaudRate(BAUD9600);
//    //ãΪ115200
//    irCom->setDataBits(DATA_8);
//    //λãΪ8λλ
//    irCom->setParity(PAR_NONE);
//    //żУãΪУ
//    irCom->setStopBits(STOP_1);
//    //ֹͣλãΪ1λֹͣλ
//    irCom->setFloowControl(FLOW_OFF);
//    //ãΪ
//    irCom->setTimeout(500);
//    //ʱãΪʱ500ms,Woindowsº
//    connect(irCom,SIGNAL(readyRead()),this,SLOT(readIRCom()));
//    //źźͲۺڻʱж
//#else
//    irCom = new ManageSerialPort("/dev/ttymxc4",BAUD9600, DATA_8, PAR_NONE,STOP_1,FLOW_OFF,0,50);
//    bool isOpen = irCom->open();
//    if(isOpen)
//    {
//        //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
//        connect(irCom,SIGNAL(newDataReceived(const QByteArray &)),this,SLOT(irDataReceived(const QByteArray&)));

//        irCom->enableReceiving();
//        irCom->enableSending();
//        irCom->receiveData();
//    }
//#endif

//}
void MainForm::InitMiniusbCom()
{
#if(WIN32)
    //崮ڶָͲѯģʽʹ¼EventDriven
    MiniusbCom =new Win_QextSerialPort("COM2",QextSerialBase::EventDriven);
    MiniusbCom ->open(QIODevice::ReadWrite);
    //Զдʽ򿪴
    MiniusbCom->setBaudRate(BAUD9600);
    //ãΪ115200
    MiniusbCom->setDataBits(DATA_8);
    //λãΪ8λλ
    MiniusbCom->setParity(PAR_NONE);
    //żУãΪУ
    MiniusbCom->setStopBits(STOP_1);
    //ֹͣλãΪ1λֹͣλ
    MiniusbCom->setFloowControl(FLOW_OFF);
    //ãΪ
    MiniusbCom->setTimeout(500);
    //ʱãΪʱ500ms,Woindowsº
    connect(MiniusbCom,SIGNAL(readyRead()),this,SLOT(readIRCom()));
    //źźͲۺڻʱж
#else
    MiniusbCom = new ManageSerialPort("/dev/ttyGS0",BAUD9600, DATA_8, PAR_NONE,STOP_1,FLOW_OFF,0,50);
    bool isOpen = MiniusbCom->open();
    if(isOpen)
    {
        //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
        connect(MiniusbCom,SIGNAL(newDataReceived(const QByteArray &)),this,SLOT(MiniusbDataReceived(const QByteArray&)));
//        connect(MiniusbCom,SIGNAL(destroyed()),MiniusbCom,SLOT(deleteLater()));
        MiniusbCom->enableReceiving();
        MiniusbCom->enableSending();
        MiniusbCom->receiveData();
    }
#endif

}

void MainForm::MiniusbDataReceived(const QByteArray &temp)
{
    qDebug()<<"MiniReceive";
    MiniComLoopcount=0;
    InitMinicount=0;
    IsMiniOutLink=false;
    idx_Mini=0;
    IsMiniReceived=true;
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));

//    static int sPacketIdFound = 0;
//    static int sCurrPacketLen=0;
//    char *data = (char*)temp.data();
//    QString recdata=temp.data();
//    int length = temp.length();
//    char sCurrPacket[50];
//    char  current_data;
    QString rinfo=temp.data();
    if(rinfo!="")
        TcpReceived(rinfo);
//    qDebug()<<rinfo;

//    while (length > 0)
//    {
//        current_data = * data;
//        if (sPacketIdFound){
//            if(current_data==0x21)
//            {
////                for(int i=0;i<sCurrPacketLen;i++)
//                    rinfo=QString(QLatin1String(sCurrPacket));
//                TcpReceive(rinfo);
//                qDebug()<<rinfo;
//                sCurrPacketLen=0;
//                sPacketIdFound=0;
//            }
//            else
//            {
//                sCurrPacket [sCurrPacketLen] = current_data;
//                sCurrPacketLen++;
//            }
//        }
//        else if(current_data==0x26){
//            sPacketIdFound = 1;
//        }
//        data ++;
//        length --;
//    }
    if(MiniusbCom->isOpen())
        MiniusbCom->close();
    MiniusbCom->open();
    MiniusbCom->sendData(sdata,2000);
//    qDebug()<<paraint++;
}
void MainForm::MiniusbDataSend(QString msg)
{
//    bool isopen=MiniusbCom->open();
//    if(isopen&&MiniusbCom->isSendingEnabled())
//    {
//        QByteArray sdata=msg.toAscii();
//        MiniusbCom->sendData(sdata,2000);
//        qDebug()<<sdata;
//    }
    msgdata=msg;
    sdata=msg.toLatin1();
}

void MainForm::InitTempCom()
{
#if(WIN32)
    //崮ڶָͲѯģʽʹ¼EventDriven
    irCom =new Win_QextSerialPort("COM2",QextSerialBase::EventDriven);
    irCom ->open(QIODevice::ReadWrite);
    //Զдʽ򿪴
    irCom->setBaudRate(BAUD9600);
    //ãΪ115200
    irCom->setDataBits(DATA_8);
    //λãΪ8λλ
    irCom->setParity(PAR_NONE);
    //żУãΪУ
    irCom->setStopBits(STOP_1);
    //ֹͣλãΪ1λֹͣλ
    irCom->setFloowControl(FLOW_OFF);
    //ãΪ
    irCom->setTimeout(500);
    //ʱãΪʱ500ms,Woindowsº
    connect(irCom,SIGNAL(readyRead()),this,SLOT(readIRCom()));
    //źźͲۺڻʱж
#else
    TempCom = new ManageSerialPort("/dev/ttymxc4",BAUD19200, DATA_8, PAR_NONE,STOP_1,FLOW_OFF,0,50);
    bool isOpen = TempCom->open();
    if(isOpen)
    {
        //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
        connect(TempCom,SIGNAL(newDataReceived(const QByteArray &)),this,SLOT(TempDataReceived(const QByteArray&)));

        TempCom->enableReceiving();
//        TempCom->enableSending();
        TempCom->receiveData();
    }
#endif

}
void MainForm::TempDataReceived(const QByteArray &temp)
{
    static unsigned char sCurrPacket[10];
    static int        sPacketIdFound = 0;/*ܵIDı־1ʾյ*/
    static int        sCurrPacketLen;/*ǰܵİ*/

    unsigned char *data = (unsigned char*)temp.data();
    int length = temp.length();

    unsigned char  current_data;
    int   result = 0;
    /* ȡ */
    while (length > 0)
    {
        current_data = * data;
        /* յֽ */
        if ( sPacketIdFound ){
            /* ǰֽڣЧֽڱڵ0x80 */

//            if (current_data >0x32 ){
                //
                sCurrPacket [sCurrPacketLen++] = current_data;

                /* յݣʼ */
                if (sCurrPacketLen ==  8) {
                    result=UnPackTmepData(sCurrPacket,sCurrPacketLen);
                    if ( 0 == result ){
                        DispatchData(sCurrPacket, sCurrPacketLen);
                    }
                    sPacketIdFound = 0;
                }

        }else if(current_data==0x50){
            /* 鵱ǰֽǷȷİID */
            sCurrPacketLen = 1;
            sCurrPacket[0] = current_data;
            sPacketIdFound   = 1;
        }else {
            /* ǰݲȷİ */
            result = -1;
        }
        /* ָһ */
        data ++;
        /* ݳȼ1 */
        length --;
    }
}

void MainForm::InitIRACCUCom()
{
#if(WIN32)
    //崮ڶָͲѯģʽʹ¼EventDriven
    irCom =new Win_QextSerialPort("COM2",QextSerialBase::EventDriven);
    irCom ->open(QIODevice::ReadWrite);
    //Զдʽ򿪴
    irCom->setBaudRate(BAUD9600);
    //ãΪ115200
    irCom->setDataBits(DATA_8);
    //λãΪ8λλ
    irCom->setParity(PAR_NONE);
    //żУãΪУ
    irCom->setStopBits(STOP_1);
    //ֹͣλãΪ1λֹͣλ
    irCom->setFloowControl(FLOW_OFF);
    //ãΪ
    irCom->setTimeout(500);
    //ʱãΪʱ500ms,Woindowsº
    connect(irCom,SIGNAL(readyRead()),this,SLOT(readIRCom()));
    //źźͲۺڻʱж
#else
    irCom = new ManageSerialPort("/dev/ttymxc3",BAUD9600, DATA_8, PAR_NONE,STOP_1,FLOW_OFF,0,50);
    bool isOpen = irCom->open();
    if(isOpen)
    {
        //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
        connect(irCom,SIGNAL(newDataReceived(const QByteArray &)),this,SLOT(IRACCUDataReceive(const QByteArray&)));

        irCom->enableReceiving();
        irCom->enableSending();
        irCom->receiveData();
    }
#endif
}
void MainForm::IRACCUDataReceive(const QByteArray &temp)
{
//    unsigned char IRACCUsCurrPacket[10];
    static int        sPacketIdFound = 0;
    static int        sCurrPacketLen;

    unsigned char *data = (unsigned char*)temp.data();
    int length = temp.length();
    //    bool IsGLUPack=false;
    unsigned char  current_data;
    while (length > 0)
    {
        current_data = * data;
        if ( sPacketIdFound ){
            //            IRACCUsCurrPacket [sCurrPacketLen++] = current_data;
            sCurrPacketLen++;
            if (sCurrPacketLen ==  2) {
                sPacketIdFound = 0;
                sCurrPacketLen=0;
                irDataReceived(temp);
            }
        }
        else if(current_data==PACKID_IR){
            sCurrPacketLen = 1;
            //            IRACCUsCurrPacket[0] = current_data;
            sPacketIdFound   = 1;
        }
        else if(current_data==0xF0)
        {
            sPacketIdFound=0;
            sCurrPacketLen=0;
        }
        data ++;
        length --;
    }
    if(current_data!=0xFE&&!sPacketIdFound&&current_data!=0xF0)
        accuDataReceived(temp);
}

//void MainForm::readAccuCom()
//{

//}
void MainForm::accuDataReceived(const QByteArray &temp)
{
    unsigned char *data = (unsigned char*)temp.data();
    int length = temp.length();
    QByteArray buff;
    double glu;
    static unsigned char packet[100];

    for(int i=0; i< length;i++)
    {

        if( data[i]==0x15)
        {
//            qDebug()<<"0x15";
            idx = 0;
            ispacket = 0;
            buff.clear();
            buff.append(0x0b);
            buff.append(0x0d);
            irCom->sendData(buff, 20000);
        }
        else if(data[i] == 0x06)
        {
//            qDebug()<<"0x06";
            ispacket =1;
            idx = 0;
            packet[idx++] = data[i];
        }
        else if(ispacket ==1)
        {
            if(data[i] == 0x04)
            {
//                qDebug()<<"0x04";
                packet[idx++] = data[i];
                if(idx == 13)
                {
                    buff.clear();
                    buff.append(0x06);
                    buff.append(0x61);
                    buff.append(0x09);
                    buff.append(0x31);
                    buff.append(0x09);
                    buff.append(0x31);
                    buff.append(0x0d);
                    irCom->sendData(buff, 20000);
//                    IsReceiveAccu=true;
                }
                else if(idx == 34)
                {
                    glu =((packet[5]-'0') * 100.0 + (packet[6]-'0')*10.0 + (packet[7]-'0'))/18.0;
//                    qDebug()<<glu;
                    buff.clear();
                    buff.append(0x06);
                    buff.append(0x1d);
                    buff.append(0x0d);
                    irCom->sendData(buff, 20000);
                    emit AccuData(glu);
                    return;
    //                AccuSendCount=0;
    //                InitIRACCUCom();
                }
                idx = 0;
                ispacket = 0;
            }
            else
            {
                packet[idx++] = data[i];
//                qDebug()<<"Isreceiving";
                if(idx >= 34)
                {
//                    qDebug()<<"error";
                    idx = 0;
                    ispacket = 0;
                }
            }

        }
        else
        {
            idx = 0;
            ispacket = 0;
//            qDebug()<<"other";
          }
    }

}

void MainForm::timeevent()
{

    QDateTime dt;
    QTime time;
    QDate date;
    dt.setTime(time.currentTime());
    dt.setDate(date.currentDate());
    QString timenow=dt.toString("yyyy-MM-dd hh:mm:ss");
    IsOneSec=false;
    ui->labTime->setText(timenow);
    if(MiniComLoopcount++>=5&&IsMiniReceived)
    {
        MiniComLoopcount=0;
        if(InitMinicount++<=2)
        {
            if(MiniusbCom->isOpen())
                MiniusbCom->close();
            MiniusbCom->open();
            MiniusbCom->receiveData();
            qDebug()<<"ReInitMiniUsbCom";
        }
    }
    if(AccuSendCount++==2)
    {
        idx = 0;
        ispacket = 0;
        if(irCom->isOpen())
            irCom->close();
        irCom->open();
        GlucoseStart();
        AccuSendCount=0;
    }
    if(idx_Mini++>=2)
        IsMiniOutLink=true;
    else
        IsMiniOutLink=false;
}
void MainForm::InitPrintCom()
{
#if(WIN32)
    //崮ڶָͲѯģʽʹ¼EventDriven
    irCom =new Win_QextSerialPort("COM2",QextSerialBase::EventDriven);
    irCom ->open(QIODevice::ReadWrite);
    //Զдʽ򿪴
    irCom->setBaudRate(BAUD9600);
    //ãΪ115200
    irCom->setDataBits(DATA_8);
    //λãΪ8λλ
    irCom->setParity(PAR_NONE);
    //żУãΪУ
    irCom->setStopBits(STOP_1);
    //ֹͣλãΪ1λֹͣλ
    irCom->setFloowControl(FLOW_OFF);
    //ãΪ
    irCom->setTimeout(500);
    //ʱãΪʱ500ms,Woindowsº
    connect(irCom,SIGNAL(readyRead()),this,SLOT(readIRCom()));
    //źźͲۺڻʱж
#else
    printCom = new ManageSerialPort("/dev/ttymxc2",BAUD9600, DATA_8, PAR_NONE,STOP_1,FLOW_OFF,0,50);
    bool isOpen = printCom->open();
    if(isOpen)
    {
        //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
//        connect(printCom,SIGNAL(newDataReceived(const QByteArray &)),this,SLOT(TempDataReceived(const QByteArray&)));

        printCom->enableReceiving();
        printCom->enableSending();
        printCom->receiveData();
    }
#endif
}
void MainForm::printData(double *pdata)
{
    if(printCom->isOpen())
        printCom->close();
    printCom->open();
//    const char cmdchar[]={0x1b,0x36};
//    unsigned char tmpdata[]={*pdata,*(pdata+1),*(pdata+2),*(pdata+3),*(pdata+4),*(pdata+5),*(pdata+6)};  //GLU,TEMP,SYS,DIA,AVER,SPO2,PR
    const char cmdinit[]={0x1b,0x40,0x00};  //Init cmd
//    const char cmdleftlimite[]={0x1b,0x6c,0x10};
    const char cmdchinatable[]={0x1b,0x44,0x01,0x8,0xF,0x00};
    const char cmdenglishtable[]={0x1b,0x44,0x01,0x06,0xE,0x00};
    const char cmdfontspace[]={0x1b,0x20,0x01};  //font space between
    const char cmdnullval[]={"--"};
    const char gluunit[]={"mmol/dl"};
    const char tempunit1[]={0x1b, 0x37, (const char) 0x9a};
    const char tempunit[]={0x1b,0x36,0x43};
//    const char tempunit[]={"C"};
    const char sysunit[]={"mmHg"};
    const char diaunit[]={"mmHg"};
    const char averunit[]={"mmHg"};
    const char spo2unit[]={"%"};
    const char prunit[]={"BPM"};
    QDateTime dt;
    QTime time;
    QDate date;
    dt.setTime(time.currentTime());
    dt.setDate(date.currentDate());
    QString timenow=dt.toString("yyyy-MM-dd hh:mm:ss");
    printCom->sendData(*new QByteArray(&cmdinit[0],3)); //init the printer


    if(IsChinese)
    {
        const char cmdchineselitter[]={0x1b,0x38,0x04,0x1b,0x57,0x01};
        const char cmdchinesebig[]={0x1b,0x38,0x04,0x1b,0x57,0x02};
        const char cglu[]={(const char) 0xd1, (const char) 0xaa, 0x1b, 0x66, 0x0, 0x2, (const char) 0xcc,
                           (const char) 0x0c7, 0x3a};
        const char cspo2[]={(const char) 0xd1, (const char) 0xaa, 0x1b, 0x66, 0x0, 0x2, (const char) 0xd1,
                            (const char) 0xf5, 0x3a};
        const char ctemp[]={(const char) 0xcc, (const char) 0xe5, 0x1b, 0x66, 0x0, 0x2, (const char) 0xce,
                            (const char) 0xc2, 0x3a};
        const char cpr[]={(const char) 0xc2, (const char) 0xf6, 0x1b, 0x66, 0x0, 0x2, (const char) 0xc2,
                          (const char) 0xca, 0x3a};
        const char csys[]={(const char) 0xca, (const char) 0xd5, (const char) 0xcb, (const char) 0xf5,
                           (const char) 0xd1, (const char) 0xb9, 0x3a};
        const char cdia[]={(const char) 0xca, (const char) 0xe6, (const char) 0xd5, (const char) 0xc5,
                           (const char) 0xd1, (const char) 0xb9, 0x3a};
        const char caver[]={(const char) 0xc6, (const char) 0xbd, (const char) 0xbe, (const char) 0xf9,
                            (const char) 0xd1, (const char) 0xb9, 0x3a};

//        printCom->sendData(*new QByteArray(&cmdleftlimite[0],3)); //limite left size
        printCom->sendData(*new QByteArray(&cmdchineselitter[0],6));  //set chinese type
        printCom->sendData(*new QByteArray(*new QByteArray(&cmdchinatable[0],6)));

        //print pr
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&cpr[0],9));
        printCom->sendData(*new QByteArray(&cmdchinesebig[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata+6)).toInt()<=0)
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata+6)).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdchineselitter[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&prunit[0],3));
        printCom->sendData(*new QByteArray(1,(char)0x0a));

        //print spo2
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&cspo2[0],9));
        printCom->sendData(*new QByteArray(&cmdchinesebig[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata+5)).toInt()<=0||(QString::number(*(pdata+5)).toInt()>100))
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata+5)).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdchineselitter[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&spo2unit[0],1));
        printCom->sendData(*new QByteArray(1,(char)0x0a));

        // print aver
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&caver[0],7));
        printCom->sendData(*new QByteArray(&cmdchinesebig[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata+4)).toInt()<=0)
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata+4)).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdchineselitter[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&averunit[0],4));
        printCom->sendData(*new QByteArray(1,(char)0x0a));

        // print dia
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&cdia[0],7));
        printCom->sendData(*new QByteArray(&cmdchinesebig[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata+3)).toInt()<=0)
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata+3)).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdchineselitter[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&diaunit[0],4));
        printCom->sendData(*new QByteArray(1,(char)0x0a));

        //print sys
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&csys[0],7));
        printCom->sendData(*new QByteArray(&cmdchinesebig[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata+2)).toInt()<=0)
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata+2)).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdchineselitter[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&sysunit[0],4));
        printCom->sendData(*new QByteArray(1,(char)0x0a));

        //print temp
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&ctemp[0],9));
        printCom->sendData(*new QByteArray(&cmdchinesebig[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata+1),'f',1).toDouble()<=0.0)
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata+1),'f',1).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdchineselitter[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&tempunit1[0],3));
        printCom->sendData(*new QByteArray(&tempunit[0],3));
        printCom->sendData(*new QByteArray(1,(char)0x0a));

        printCom->sendData(*new QByteArray(&cmdchineselitter[0],6));
        //print glu
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&cglu[0],9));
        printCom->sendData(*new QByteArray(&cmdchinesebig[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata),'f',1).toDouble()<=0.0)
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata),'f',1).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdchineselitter[0],6));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&gluunit[0],7));
        printCom->sendData(*new QByteArray(1,(char)0x0a));
    }
    else
    {
        const char cmdenglishbig[]={0x1b,0x36,0x1b,0x57,0x02};
        const char cmdenglishlitter[]={0x1b,0x36,0x1b,0x57,0x01};
        const char eglu[]={"GLU:"};
        const char espo2[]={"SPO2:"};
        const char etemp[]={"BBT:"};
        const char epr[]={"PR:"};
        const char esys[]={"SBP:"};
        const char edia[]={"DBP:"};
        const char eaver[]={"MBP:"};
        printCom->sendData(*new QByteArray(&cmdfontspace[0],3));//set font space between
        printCom->sendData(*new QByteArray(*new QByteArray(&cmdenglishtable[0],6)));
        printCom->sendData(*new QByteArray(&cmdenglishlitter[0],5));  //set english type

        //print pr
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&epr[0],strlen(eglu)));
        printCom->sendData(*new QByteArray(&cmdenglishbig[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata+6)).toInt()<=0)
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata+6)).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdenglishlitter[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&prunit[0],3));
        printCom->sendData(*new QByteArray(1,(char)0x0a));

        //print spo2
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&espo2[0],strlen(espo2)));
        printCom->sendData(*new QByteArray(&cmdenglishbig[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata+5)).toInt()<=0||(QString::number(*(pdata+5)).toInt()>100))
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata+5)).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdenglishlitter[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&spo2unit[0],1));
        printCom->sendData(*new QByteArray(1,(char)0x0a));

        // print aver
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&eaver[0],strlen(eaver)));
        printCom->sendData(*new QByteArray(&cmdenglishbig[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata+4)).toInt()<=0)
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata+4)).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdenglishlitter[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&averunit[0],4));
        printCom->sendData(*new QByteArray(1,(char)0x0a));

        // print dia
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&edia[0],strlen(edia)));
        printCom->sendData(*new QByteArray(&cmdenglishbig[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata+3)).toInt()<=0)
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata+3)).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdenglishlitter[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&diaunit[0],4));
        printCom->sendData(*new QByteArray(1,(char)0x0a));

        //print sys
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&esys[0],strlen(esys)));
        printCom->sendData(*new QByteArray(&cmdenglishbig[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata+2)).toInt()<=0)
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata+2)).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdenglishlitter[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&sysunit[0],4));
        printCom->sendData(*new QByteArray(1,(char)0x0a));

        //print temp
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&etemp[0],strlen(etemp)));
        printCom->sendData(*new QByteArray(&cmdenglishbig[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata+1),'f',1).toDouble()<=0.0)
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata+1),'f',1).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdenglishlitter[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&tempunit1[0],3));
        printCom->sendData(*new QByteArray(&cmdenglishlitter[0],5));
        printCom->sendData(*new QByteArray(&tempunit[0],3));
        printCom->sendData(*new QByteArray(1,(char)0x0a));

        //print glu
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&eglu[0],strlen(eglu)));
        printCom->sendData(*new QByteArray(&cmdenglishbig[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        if(QString::number(*(pdata),'f',1).toDouble()<=0.0)
            printCom->sendData(*new QByteArray(&cmdnullval[0],2));
        else
            printCom->sendData(*new QByteArray(QString::number(*(pdata),'f',1).toLatin1()));
        printCom->sendData(*new QByteArray(&cmdenglishlitter[0],5));
        printCom->sendData(*new QByteArray(1,(char)0x09));
        printCom->sendData(*new QByteArray(&gluunit[0],7));
        printCom->sendData(*new QByteArray(1,(char)0x0a));

    }
    printCom->sendData(*new QByteArray(timenow.toLatin1())); //print time
    printCom->sendData(*new QByteArray(1,(char)0x0a));
    printCom->sendData(*new QByteArray(1,(char)0x0a));
    printCom->sendData(*new QByteArray(1,(char)0x0a));
    printCom->sendData(*new QByteArray(1,(char)0x0a));
    printCom->sendData(*new QByteArray(1,(char)0x0a));
    printCom->sendData(*new QByteArray(1,(char)0x0a));
    printCom->sendData(*new QByteArray(1,(char)0x0a));
    printCom->sendData(*new QByteArray(1,(char)0x0a));
    printCom->sendData(*new QByteArray(1,(char)0x0d));
}


void MainForm::readIRCom()
{
#if(WIN32)
    QByteArray temp = irCom->readAll();
    irDataReceived(temp);
#endif
}


void MainForm::irDataReceived(const QByteArray &temp)
{
    unsigned char *data = (unsigned char*)temp.data();
    int length = temp.length();

    unsigned char  current_data;

    while (length > 0)
    {
        current_data = *data;
//        QString val;
//        val.sprintf("%02x",current_data);
        qDebug()<<current_data<<"\n";
        switch(*(data))
        {
//        case IR_MODEL:
//            if(--btnidx < 0) btnidx = 0;
//            (this->*btnHandlers[btnidx])();
//            break;
//        case IR_MODER:
//            if(++btnidx > 4) btnidx = 4;
//            (this->*btnHandlers[btnidx])();
//            break;
//        case IR_SYSRESET:
//            on_btnreset_clicked();
//            break;
        case IR_PRINT:
            if(monitorform->isVisible())
                on_btnprint_clicked();
            else if(visualchart->isVisible())
                emit DispatchIRData(*data);
            break;
        case IR_MAINFORM:
            on_btnMonitor_clicked();
            break;
        case IR_ECG:
            on_btnWave_clicked();
            break;
        case IR_VISUALCHART:
            on_btnVisualChart_clicked();
            break;
        case IR_COLORCHART:
            on_btnColorChart_clicked();
            break;
        case IR_VOICE:
            emit setbuzzingoff();
            break;
        default:
            emit DispatchIRData(*data);
        }
        length--;
        data++;
    }
}


void MainForm::on_btnMonitor_clicked()
{
    emit wavereflesh(true);
    if(passwordform->isActiveWindow())
        passwordform->close();
    monitorform->setVisible(true);
    waveform->setVisible(false);
    visualchart->setVisible(false);
    colorchart->setVisible(false);
    setting->setVisible(false);
    btnidx = 0;
    IsAtSetting=false;
    ui->btnMonitor->setStyleSheet("background-color: rgb(60,89,172);");
    ui->btnWave->setStyleSheet("background-color: rgb(0,0,0);");
    ui->btnVisualChart->setStyleSheet("background-color: rgb(0,0,0);");
    ui->btnColorChart->setStyleSheet("background-color: rgb(0,0,0);");
    ui->btnSettings->setStyleSheet("background-color: rgb(0,0,0);");
}

void MainForm::on_btnWave_clicked()
{
    emit wavereflesh(false);
    if(passwordform->isActiveWindow())
        passwordform->close();
    monitorform->setVisible(false);
    waveform->setVisible(true);
    visualchart->setVisible(false);
    colorchart->setVisible(false);
    setting->setVisible(false);
    btnidx = 1;
    IsAtSetting=false;
    ui->btnMonitor->setStyleSheet("background-color: rgb(0,0,0);");
    ui->btnWave->setStyleSheet("background-color: rgb(60,89,172);");
    ui->btnVisualChart->setStyleSheet("background-color: rgb(0,0,0);");
    ui->btnColorChart->setStyleSheet("background-color: rgb(0,0,0);");
    ui->btnSettings->setStyleSheet("background-color: rgb(0,0,0);");
}

void MainForm::on_btnVisualChart_clicked()
{
    emit wavereflesh(true);
    if(passwordform->isActiveWindow())
        passwordform->close();
    monitorform->setVisible(false);
    waveform->setVisible(false);
    visualchart->setVisible(true);
    colorchart->setVisible(false);
    setting->setVisible(false);
    btnidx = 2;
    IsAtSetting=false;

    ui->btnMonitor->setStyleSheet("background-color: rgb(0,0,0);");
    ui->btnWave->setStyleSheet("background-color: rgb(0,0,0);");
    ui->btnVisualChart->setStyleSheet("background-color: rgb(60,89,172);");
    ui->btnColorChart->setStyleSheet("background-color: rgb(0,0,0);");
    ui->btnSettings->setStyleSheet("background-color: rgb(0,0,0);");
}

void MainForm::on_btnColorChart_clicked()
{
    emit wavereflesh(false);
    if(passwordform->isActiveWindow())
        passwordform->close();
    monitorform->setVisible(false);
    waveform->setVisible(false);
    visualchart->setVisible(false);
    colorchart->setVisible(true);
    setting->setVisible(false);
    btnidx = 3;
    IsAtSetting=false;
    ui->btnMonitor->setStyleSheet("background-color: rgb(0,0,0);");
    ui->btnWave->setStyleSheet("background-color: rgb(0,0,0);");
    ui->btnVisualChart->setStyleSheet("background-color: (0,0,0);");
    ui->btnColorChart->setStyleSheet("background-color: rgb(60,89,172);");
    ui->btnSettings->setStyleSheet("background-color: rgb(0,0,0);");
}

void MainForm::on_btnSettings_clicked()
{
    emit Clearpswtxt();
    if(IsAtSetting)
        return;
    if(waveform->isVisible())
        emit wavereflesh(true);
    if(passwordform->exec()==PassWordDialog::Accepted)
    {


        monitorform->setVisible(false);
        waveform->setVisible(false);
        visualchart->setVisible(false);
        colorchart->setVisible(false);
        setting->setVisible(true);
        btnidx = 4;
        IsAtSetting=true;
        ui->btnMonitor->setStyleSheet("background-color: rgb(0,0,0);");
        ui->btnWave->setStyleSheet("background-color: rgb(0,0,0);");
        ui->btnVisualChart->setStyleSheet("background-color: (0,0,0);");
        ui->btnColorChart->setStyleSheet("background-color: rgb(0,0,0);");
        ui->btnSettings->setStyleSheet("background-color: rgb(60,89,172);");
    }
    else
    {
        if(waveform->isVisible())
            on_btnWave_clicked();
        else if(monitorform->isVisible())
            on_btnMonitor_clicked();
        else if(visualchart->isVisible())
            on_btnVisualChart_clicked();
        else if(colorchart->isVisible())
            on_btnColorChart_clicked();
    }
//    ui->btnSettings->setStyleSheet("background-color: rgb(0,0,255);");
}

void MainForm::BPStart()
{
    if(!IsNIBP)
    {
        unsigned char packet[10];
        packet[0] = CMD_NBP_START;
        SendCommand(packet);
        IsNIBP=true;
//        emit NIBPBPTestENDEND();
 //       ui->btnBPStart->setText(QString::fromUtf8("停止测量"));
    }
    else
    {
        unsigned char packet[10];
        packet[0] = CMD_NBP_END;
        SendCommand(packet);
        IsNIBP=false;

      //  ui->btnBPStart->setText(QString::fromUtf8(("血压测量")));
    }
}
void MainForm::BPEND()
{
    IsNIBP=false;
}

void MainForm::GlucoseStart()
{
    QByteArray buff;

    buff.append(0x01);
    buff.append(0x01);
    buff.append(0x01);

    irCom->sendData(buff, 20000);
    buff.clear();
//    qDebug()<<"IsSending";
}


void MainForm::PatienttypeSet(unsigned char patienttype)
{
    unsigned char packet[10];
    packet[0]=CMD_PAT_TYPE;
    packet[1]=patienttype;
    SendCommand(packet);
    if(patienttype==(unsigned char)1)
    {
        if(IsChinese)
            ui->labPatientType->setText(QString::fromUtf8(("儿童")));
        else
            ui->labPatientType->setText("Child");
    }
    else
    {
        if(IsChinese)
            ui->labPatientType->setText(QString::fromUtf8(("成人")));
        else
            ui->labPatientType->setText("Adult");
    }

}
void MainForm::ECGSet(char command, int packet1, int index)
{
    unsigned char packet[10];
    packet[0]=command;
    unsigned char ECGcmd;
    if(command==CMD_LEADTYPE)
    {
        if(packet1==1)
            ECGcmd=(unsigned char)(index+1);
        else
            ECGcmd=(unsigned char)(index+17);
    }
    else if(command==CMD_ECG_GAIN)
    {
        if(packet1==1)
            ECGcmd=(unsigned char)(index);
        else
            ECGcmd=(unsigned char)(index+16);
    }
    else
    {
        ECGcmd=(unsigned char)packet1;
    }
    packet[1]=ECGcmd;
    SendCommand(packet);
}
void MainForm::ECGInfoSet(QString info)
{
    secginfo=info.toLatin1();//.append(info);
    if(clientconnection->state()&QAbstractSocket::ConnectedState)
    {

        clientconnection->write(secginfo);
        clientconnection->flush();
//        qDebug()<<secginfo.length();
    }
    else
    {
        if(!IsMiniOutLink)
            MiniusbCom->sendData(secginfo,1000);
    }
    secginfo.clear();
}

void MainForm::on_btnreset_clicked()
{
//    ui->btnreset->setStyleSheet("background-color: rgb(0,0,255);");

//    if(IsRebooting)
//    {
//        IsRebooting=false;
//        resetform->close();
//    }
//    else
//    {
//        IsRebooting=true;
        if(resetform->exec()==ResetDialog::Accepted)
        {
            QString cmdreset="reboot";
            system(cmdreset.toLatin1().data());
        }
//        else
//        ui->btnreset->setStyleSheet("background-color: rgb(0,0,255);");
//    }
}
void MainForm::Loadxml()
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
            case 4:
                listenport=value.toInt();
                break;
            case 26:
                if(value=="Chinese")
                {
                    IsChinese=true;
                    emit ChineseLangue(true);
                }
                else
                {
                    IsChinese=false;
                    emit ChineseLangue(false);
                }
                break;
            }
        }
        node=node.nextSibling();
    }
    if(IsChinese)
    {
        ui->btnprint->setText(QString::fromUtf8("打  印"));
        ui->btnMonitor->setText(QString::fromUtf8("主界面"));
        ui->btnWave->setText(QString::fromUtf8("心电图"));
        ui->btnVisualChart->setText(QString::fromUtf8("视力表"));
        ui->btnColorChart->setText(QString::fromUtf8("色觉图"));
        ui->btnSettings->setText(QString::fromUtf8("设  置"));
        ui->btnreset->setText(QString::fromUtf8("重  启"));
        ui->labPatientNumtag->setText(QString::fromUtf8("患者编号:"));
        ui->labPatientNametag->setText(QString::fromUtf8("患者姓名:"));
        ui->labPatientNum->setGeometry(290,0,261,69);
        ui->labPatientName->setGeometry(690,0,221,69);
//        ui->labcompany->setText(QString::fromUtf8("上海跃进医用光学器械厂"));
        if(ui->labPatientType->text()=="Adult"||ui->labPatientType->text()==QString::fromUtf8("成人"))
            ui->labPatientType->setText(QString::fromUtf8("成人"));
        else
            ui->labPatientType->setText(QString::fromUtf8("儿童"));
    }
    else
    {
        ui->btnMonitor->setText("MainForm");
        ui->btnWave->setText("ECG");
        ui->btnVisualChart->setText("VisualChart");
        ui->btnColorChart->setText("ColorChart");
        ui->btnSettings->setText("Setting");
        ui->btnprint->setText("Print");
        ui->btnreset->setText("Resart");
        ui->labPatientNumtag->setText("PatientID:");
        ui->labPatientNum->setGeometry(320,0,261,69);
        ui->labPatientName->setGeometry(670,0,221,69);
        ui->labPatientNametag->setText("Name:");
        if(ui->labPatientType->text()==QString::fromUtf8("成人")||ui->labPatientType->text()=="Adult")
            ui->labPatientType->setText("Adult");
        else
            ui->labPatientType->setText("Child");
    }
    file.close();
}
void MainForm::TcpReceived(QString data)
{
    QStringList pinfolist=data.split(',');
    PID=pinfolist.at(0);
    PNAME=pinfolist.at(1);
    if(PID!="0")
        ui->labPatientNum->setText(PID);
    else
        ui->labPatientNum->setText("--");
    if(PNAME!="0")
        ui->labPatientName->setText(PNAME);
    else
        ui->labPatientName->setText("--");
}
void MainForm::ResetPinfo()
{
    PID="0";
    PNAME="0";
}
void MainForm::StartListen()
{
    if(tcpserver->isListening())
    {
        tcpserver->close();
        clientconnection->close();
        tcpserver=new QTcpServer(this);
    }
//    qDebug()<<localip;
    if(!tcpserver->listen(QHostAddress(localip),listenport))
    {
        qDebug()<<tcpserver->errorString();
    }
    connect(tcpserver,SIGNAL(newConnection()),this,SLOT(TcpCreatSlot()));
}
void MainForm::ReadSendMessage()
{
    MiniComLoopcount=0;
    InitMinicount=0;
    char *redata;
    redata=clientconnection->readAll().data();
    QString info=redata;
    redata=NULL;
    if(info!="")
        TcpReceived(info);
//        emit receivedata(info);
//    qDebug()<<info+":"+QString::number(++count_i);

//    msgdata=//QString::number(cal_Data_AVER)+","+QString::number(cal_Data_DIAS)+","+QString::number(Data_GLU,'f',1)+","+QString::number(cal_Data_HR)+","+QString::number(cal_Data_SPO2)+","+QString::number(cal_Data_SYS)+","+QString::number(Data_TEMP,'f',1);
    block.append(msgdata);
    clientconnection->write(block);
    clientconnection->flush();
//    qDebug()<<block;
    block.clear();
}
void MainForm::TcpCreatSlot()
{
    if(clientconnection->state()&QAbstractSocket::ConnectedState)
        clientconnection->close();
    clientconnection=tcpserver->nextPendingConnection();
    connect(clientconnection,SIGNAL(readyRead()),this,SLOT(ReadSendMessage()));
    connect(clientconnection,SIGNAL(disconnected()),this,SLOT(TcpClientClose()));
    connect(clientconnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(DisplayTcpError(QAbstractSocket::SocketError)));
}
void MainForm::TcpClientClose()
{
    clientconnection->close();
}
void MainForm::DisplayTcpError(QAbstractSocket::SocketError)
{
    qDebug()<<clientconnection->errorString();
}

void MainForm::on_btnprint_clicked()
{
    emit printcommand();
}

// 发送命令，关闭阀门
void MainForm::enterManualMode() {
    // 发送手动测量命令
    unsigned char packet[10];
    packet[0] = CMD_NBP_CAL;
    SendCommand(packet);

    isCal = true;
    qDebug() << "阀门已关闭....";
}

// 发送命令，打开阀门
void MainForm::exitManualMode() {
    unsigned char packet[10];
    packet[0] = CMD_NBP_END;
    SendCommand(packet);

    isCal = false;
    qDebug() << "阀门已打开...";
}
