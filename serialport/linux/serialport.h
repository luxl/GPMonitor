#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QThread>
#include "serialport/linux/ManageSerialPort.h"

const uchar maxCommand = 20;

class ThreadProc;

//串口通信基类
class SerialBase: public QObject
{
    Q_OBJECT
public:
    SerialBase();
    ~SerialBase();
    //设置串口属性及开启串口
    bool openSerialPort(QString device, BaudRateType baud, ParityType parity, DataBitsType databit, StopBitsType stopbit);
    //数据方法
    void writeFrame(const char *frame, qint64 count);
    void closeSerialPort();
private slots:
    void readData(const QByteArray &data);

signals:
    void dataUpdated(const QByteArray &data);

protected:
    ManageSerialPort *serialPort;
    uchar dataBuf[50];
    ThreadProc *thProc;
};

//
class ThreadProc : public QThread
{
    Q_OBJECT

public:
    ThreadProc(SerialBase &SerialPort);
    ~ThreadProc();
    void addData(QByteArray &dataToAdd);
    void stopProc();

signals:
    void dataUpdated(const QByteArray &data);

protected:
    void run();

private:
    QMutex mutex;
    SerialBase &extSerialPort;
    QQueue<QByteArray> packets;
    bool stopped;
};

#endif // SERIALPORT_H
