#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
//#include "mainform.h"
#include "calibratedialog.h"

namespace Ui {
class settings;
}

class settings : public QWidget
{
    Q_OBJECT
    
public:
    explicit settings(QWidget *parent = 0);
    ~settings();

    void Createxml();

    void SetNetwork();
    void SetsysTime();

    // 获取校准数据的借口
    void updateData(int data);
signals:
    // 校准开始，切换到手动模式
    void closeValve();
    void openValve();

    void Reloadxml();
    void langueload(bool);
    void ReloadCalibratexml();
private slots:
    void sendOpenSig();

    void btnNumslot(int);
    void on_btnOK_clicked();
    void Readxml();
    void on_btnsettime_clicked();

//    bool eventFilter(QObject *obj, QEvent *eve);

    void Loadsettinglangue(bool langue);

    void on_btndatacalibrate_clicked();

    void on_btnlangueUp_clicked();

    void on_btnlangueDown_clicked();

    void on_btnBuzzingUp_clicked();

    void on_btnBuzzingDown_clicked();

private:
    Ui::settings *ui;
    CalibrateDialog *calibrate;
//    MainForm *mainform;
    int hrmax;
    int hrmin;
    int spo2max;
    int spo2min;
    int diasmax;
    int diasmin;
    int avermax;
    int avermin;
    int sysmax;
    int sysmin;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    double tempmax;
    double tempmin;
    double glumax;
    double glumin;
    int listenport;
    int connectport;
    QString localip;
    QString hostip;
    QString subnetmask;
    QString gateway;
    QString pathdir;
    QString SysLangue;
    int Isbuzzing;
    bool IsChinese;
//    protected:
//    void eventFilter(QObject *obj, QEvent *eve);
};

#endif // SETTINGS_H
