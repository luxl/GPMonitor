#include "serialport.h"
SerialBase::SerialBase()
{
    thProc = new ThreadProc(*this);
    connect(thProc,SIGNAL(dataUpdated(QByteArray)),this,SIGNAL(dataUpdated(QByteArray)));
}

SerialBase::~SerialBase()
{
    if (thProc != NULL)
    {
        delete thProc;
        thProc = NULL;
    }

    if (serialPort->isOpen())
        serialPort->close();
}

bool SerialBase::openSerialPort(QString device, BaudRateType baud, ParityType parity, DataBitsType databit, StopBitsType stopbit)
{
    //以可读写方式打开串口
    serialPort = new ManageSerialPort(device,baud,databit,parity,stopbit,FLOW_OFF,0,50);
    bool isOpen = serialPort->open();

    if(isOpen)
    {
        //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
        connect(serialPort,SIGNAL(newDataReceived(QByteArray)), this, SLOT(readData(QByteArray)));

        serialPort->enableReceiving();
        serialPort->enableSending();
        serialPort->receiveData();
    }

    return isOpen;
}

void SerialBase::closeSerialPort()
{
    serialPort->close();
}

//接收数据方法
void SerialBase::readData(const QByteArray &data)
{
    if(data.length() > 0)
    {
        QByteArray packet(data);
       thProc->addData(packet);
//        emit dataUpdated(data);
    }
}

//写数据
void SerialBase::writeFrame(const char *data, qint64 count)
{
    QByteArray *dataarray = new QByteArray(data, count);

    serialPort->sendData(*dataarray);
}

/********************************************************************************************************
* Classe ThreadProc
*****************************************************************************************************/

ThreadProc::ThreadProc(SerialBase &SerialPort) : extSerialPort(SerialPort)
{
    packets.clear();
    stopped=false;
}

ThreadProc::~ThreadProc()
{
    if (isRunning())
    {
        stopProc();
        wait();
    }
}

void ThreadProc::addData(QByteArray &dataToAdd)
{
    QMutexLocker locker(&mutex);
    packets.enqueue(dataToAdd);

    if (!isRunning())
        start();
}

void ThreadProc::stopProc()
{
    stopped=true;
}

void ThreadProc::run()
{
    QByteArray data;

    forever
    {
        if (packets.isEmpty() || stopped)
        {
            stopped = false;
            break;
        }
        mutex.lock();
        data = packets.dequeue();
        mutex.unlock();

        emit dataUpdated(data);

        usleep(1000);
    }
}
