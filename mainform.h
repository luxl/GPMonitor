#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QThread>
#include "monitorform.h"
#include "waveform.h"
#include "visualchart.h"
#include "colorchart.h"
#include "settings.h"
#include "passworddialog.h"
#include "resetdialog.h"
#include <QMutex>
//#include <QPainter>

#if (WIN32)
    #include "serialport/win32/win_qextserialport.h"
#else
    #include "serialport/linux/ManageSerialPort.h"
#endif

namespace Ui {
class MainForm;
}
class Threadaccu;

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

private:
    bool isCal;  //是否在校准界面中

    Ui::MainForm *ui;
    MonitorForm *monitorform;
    WaveForm *waveform;
    VisualChart *visualchart;
    ColorChart *colorchart;
    settings *setting;
    PassWordDialog *passwordform;
    ResetDialog *resetform;
    bool IsNIBP;
    QTimer *currenttimer;
    typedef void(MainForm::*btnEventHandlers)();
    btnEventHandlers btnHandlers[5];
    int btnidx;
//    Threadaccu *ThaccuSend;
    int count_temp;
    bool IsAtSetting;
    bool IsRebooting;
    bool IsChinese;
    QString pathdir;
    QString PID;
    QString PNAME;
    QByteArray sdata;
    QByteArray secgdata;
    QByteArray shrdata;
    QByteArray secginfo;
    int MiniComLoopcount;
    bool IsMiniReceived;
    bool IsMiniOutLink;
    int InitMinicount;
    int idx;
    int ispacket;
    int AccuSendCount;
    int sendecgcnt;
    int ecgloopcount;
    int IsSendecg;
    int paraint;
    bool IsOneSec;
    int idx_Mini;
    QMutex mutex_mini;
    QString localip;
    int listenport;
    QTcpServer *tcpserver;
    QTcpSocket *clientconnection;
    QByteArray block;
    QString msgdata;
//    QPainter paint;
//    int sPacketIdFound;/*ܵIDı־1ʾյ*/
#if(WIN32)
        Win_QextSerialPort *myCom;
        Win_QextSerialPort *usbCom;
        Win_QextSerialPort *irCom;
//        Win_QextSerialPort *accuCom;
        Win_QextSerialPort *printCom;
#else
        ManageSerialPort *myCom;
        ManageSerialPort *usbCom;
        ManageSerialPort *irCom;
//        ManageSerialPort *accuCom;
        ManageSerialPort *printCom;
        ManageSerialPort *TempCom;
        ManageSerialPort *MiniusbCom;
#endif
    int  UnPackData(unsigned char *  pack, int  len);
//    int  UnPackIRData(unsigned char *  pack, int  len);
    int  UnPackTmepData(unsigned char *  pack, int  len);
    void SendCommand (unsigned char*  pack);
    char *UnPack(unsigned char *data, int length);
    void DispatchData(unsigned char *  data, int  length);
    void SendUsbCommand();

    void SendAccuCommand();
    bool askSendAccu;



signals:
    void NIBPEND(bool);
    void DispatchIRData(unsigned char code);
    void UsbIsopen(bool);
//    void StartTcpSend();
    void creatsetfile();
    void Loadsetfile();
    void Clearpswtxt();
    void ChineseLangue(bool);
    void setbuzzingoff();
//    void datareset();
    void wavereflesh(bool);
    void AccuData(double);
    void receivedata(QString);
    void printcommand();
private slots:
    void InitCom();
    void InitTempCom();
    void TempDataReceived(const QByteArray &temp);
    void readMyCom();
    void comDataReceived(const QByteArray &temp);
    void InitUsbCom();
    void InitMiniusbCom();
    void readUsbCom();
    void usbDataReceived(const QByteArray &temp);
    void InitIRACCUCom();
    void readIRCom();
    void irDataReceived(const QByteArray &temp);
    void MiniusbDataReceived(const QByteArray &temp);
    void MiniusbDataSend(QString msg);
//    void InitAccuCom();
    void InitPrintCom();
//    void readAccuCom();
    void accuDataReceived(const QByteArray &temp);
    void timeevent();
    void BPStart();
    void BPEND();
    void on_btnVisualChart_clicked();
    void on_btnColorChart_clicked();
    void on_btnWave_clicked();
    void on_btnMonitor_clicked();
    void GlucoseStart();
    void on_btnSettings_clicked();
    void IRACCUDataReceive(const QByteArray &temp);
//    void ECG1LeadSet(int index);
//    void ECG2LeadSet(int index);
//    void ECG1GainSet(int index);
//    void ECG2GainSet(int index);
    void PatienttypeSet(unsigned char patienttype);
    void ECGSet(char command,int lead,int index);
    void ECGInfoSet(QString info);
//    void SetsPacketIdFound();
//    void on_btnTcpSendData_clicked();
//    void on_btnreset_clicked();
    void printData(double *pdata);
    void on_btnreset_clicked();
    void Loadxml();
    void TcpReceived(QString data);
    void ResetPinfo();
    void StartListen();
    void ReadSendMessage();
    void TcpCreatSlot();
    void TcpClientClose();
    void DisplayTcpError(QAbstractSocket::SocketError);
    void on_btnprint_clicked();

    // 进入手动测量模式
    void enterManualMode();
    // 退出手动测量
    void exitManualMode();
};

//class Threadaccu : public QThread
//{
//    Q_OBJECT

//public:
////    ThreadSend(QextSerialPort &addressSerialPort);
////    Threadaccu(ManageSerialPort &SendCom);
//    Threadaccu();
//        void GetSendCom(ManageSerialPort *ComComClass);
////    void addDataToSend(QByteArray &dataToAdd, int interval);
//    void stopSend();
//    ManageSerialPort *SendCom;
//protected:
//    void run();
//private:
//    bool stopped;
//private slots:

//    void SendAccuCommand(ManageSerialPort *ComClass);
//};

#endif //MAINFORM_H
