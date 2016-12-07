#ifndef MONITORFORM_H
#define MONITORFORM_H

#include <QWidget>
#include <QQueue>
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "settings.h"
#include "qdevicewatcher.h"
#include <QtNetwork>

#if (WIN32)
    #include "serialport/win32/win_qextserialport.h"
#else
    #include "serialport/linux/ManageSerialPort.h"
#endif
const int PLOT_SIZE1=500;
namespace Ui {
class MonitorForm;
}

//class QDeviceWatcher;
class MonitorForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit MonitorForm(QWidget *parent = 0);
    ~MonitorForm();
    void UpdateData(int ID, double data1=0, double data2=0, double data3=0);
    void updateSPO2WaveData(int ID, double data1, double data2);
    void SendUsbCommand();
//    int init_hotplug_sock();
signals:
    void BPTest();
    void BPTestEND();
    void GlucoseTest();
    void PatientType(unsigned char);
    void USBreload();
    void ResetsPacketIdFound();
    void print(double *);
//    void receivedata(QString);
    void senddata(QString);
    void ClearPinfo();
private:
    Ui::MonitorForm *ui;
//    settings *setting;
    QDeviceWatcher *watcher;
    double Data_HR;
    double Data_SPO2;
    double Data_TEMP;
    double Data_SYS;
    double Data_DIAS;
    double Data_AVER;
    double Data_GLU;
    double cal_Data_HR,cal_Data_SPO2,cal_Data_SYS,cal_Data_AVER,cal_Data_DIAS;
    int PackID;
    int index_spo2;
    double d_xspo2[PLOT_SIZE1];
    double d_yspo2[PLOT_SIZE1];
    QTimer *UItimer;
    QTimer *spo2timer;

//    QTimer *Sendtimer;
    int count_i;
//    QTimer *Alarmtimer;
    struct SPO2Data
    {
        int SPO2;
        char SPO2state ;
    };
    QQueue<SPO2Data *> spo2msg;
    QwtPlotCurve *curve5;
    QwtPlotCurve *curve6;
    void PaintSPO2Wave(int spo2data);

    bool IsNIBP;
    bool Isvisible;
    bool IsChildren;
    bool isNBPFinished;  // 无创血压测量是否结束
    bool alarmspo2,alarmpr,alarmglu,alarmtemp,alarmsys,alarmdia,alarmaver;

    // 校准界面使用的变量
    int hrinput1,hrinput2,hrinput3,hrinput4,hrinput5,hrinput6,hrinput7,hrinput8,hrinput9,hrinput10;
    int hroutput1,hroutput2,hroutput3,hroutput4,hroutput5,hroutput6,hroutput7,hroutput8,hroutput9,hroutput10;
    int spo2input1,spo2input2,spo2input3,spo2input4,spo2input5,spo2input6,spo2input7,spo2input8,spo2input9,spo2input10;
    int spo2output1,spo2output2,spo2output3,spo2output4,spo2output5,spo2output6,spo2output7,spo2output8,spo2output9,spo2output10;
    int diainput1,diainput2,diainput3,diainput4,diainput5,diainput6,diainput7,diainput8,diainput9,diainput10;
    int diaoutput1,diaoutput2,diaoutput3,diaoutput4,diaoutput5,diaoutput6,diaoutput7,diaoutput8,diaoutput9,diaoutput10;
    int averinput1,averinput2,averinput3,averinput4,averinput5,averinput6,averinput7,averinput8,averinput9,averinput10;
    int averoutput1,averoutput2,averoutput3,averoutput4,averoutput5,averoutput6,averoutput7,averoutput8,averoutput9,averoutput10;
    int sysinput1,sysinput2,sysinput3,sysinput4,sysinput5,sysinput6,sysinput7,sysinput8,sysinput9,sysinput10;
    int sysoutput1,sysoutput2,sysoutput3,sysoutput4,sysoutput5,sysoutput6,sysoutput7,sysoutput8,sysoutput9,sysoutput10;

    bool IsChinese;
    bool IsFirst;
    int prmax;
    int prmin;
    int spo2max;
    int spo2min;
    int diasmax;
    int diasmin;
    int avermax;
    int avermin;
    int sysmax;
    int sysmin;
    double tempmax;
    double tempmin;
    double glumax;
    double glumin;
    QString localip;
//    QString hostip;
    int listenport;
//    int connectport;
    int Isbuzzing;
    int fd;
//    QTcpServer *tcpserver;
//    QTcpSocket *clientconnection;
//    QTcpSocket *clientSend;
//    QTcpSocket *tcpsocket;
    QString pathdir;
//    QByteArray block;
//    QString msgdata;
//    int count_i;
private slots:
    void UpdateUI();
    void UpdateUISPO2();
    void Alarm();
    void Loadxml();
    void on_btnBPStart_clicked();
//    void on_btnGlucose_clicked();
    void slotDeviceAdded(QString deviceinfo);
    void slotDeviceRemoved(QString deviceinfo);
    void toggleWatch();
    void UsbopenState(bool isopen);
    void IRProc(unsigned char code);
    void on_btnPatientType_clicked();
    void DataReSet();
    void buzzonoff(unsigned int cmd);
    void printSlot();
    void PatientAdult();
    void PatientChild();
    void setisbuzzing();
    void DataCalibrate();
    void ReadCalibratexml();
//    void StartListen();
//    void TcpCreatSlot();
////    void ActivesendData();
//    void ReadSendMessage();
//    void TcpClientClose();
//    void DisplayTcpError(QAbstractSocket::SocketError);
////    void SendDataSlot();
    void AccuRecieved(double glu);
    void InitCalibrate();
};

#endif // MONITORFORM_H
