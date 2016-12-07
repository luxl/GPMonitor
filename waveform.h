#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <QWidget>
#include <QQueue>
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
const int PLOT_SIZE=600;

//const int PLOT_SIZE2=125;
namespace Ui {
class WaveForm;
}

class WaveForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit WaveForm(QWidget *parent = 0);
    ~WaveForm();
    
    void updateECGWaveData(int ID, double data1, double data2, double data3);
    void updateHrData(int ID,double data1);

private:
    Ui::WaveForm *ui;
    struct ECGData
    {
        int ECG1;
        int ECG2;
        bool FBeat;
//        int SPO2;
//        char SPO2state ;
    };

    QQueue<ECGData *> ecgmsg;

   void PaintECGWave(QwtPlot *plot,int ecgdata1,int ecgdata2);//,int spo2data);
   void PaintECGModelWave(QwtPlot *plot,int ecgdata1,int ecgdata2);
//   int PLOT_SIZE;
//   int PLOT_SIZE2;
   double d_x[PLOT_SIZE];
   double d_y[PLOT_SIZE];
   double d_x1[PLOT_SIZE];
   double d_y1[PLOT_SIZE];
   double calibrategain1;
   double calibrategain2;
   double Data_HR;
   int ecgfrontdata;
   int maxdiffvalue1;
   int maxdiffvalue2;

   int index;
   int leadswitch;

   int lead1index;
   int lead2index;

   int ecg1currentgain;
   int ecg2currentgain;
   int sendnum;

   bool ecgmodel;
   bool IsFreezed;
   bool iscalled;
   bool IsChinese;
   bool Isfirst;
   QString ECGInfo;
   QString FreezeInfo;
//   bool Isaddlabel;
   QwtPlotCurve *curve1;
   QwtPlotCurve *curve2;
   QwtPlotCurve *curve3;
   QwtPlotCurve *curve4;

//   double d_z[PLOT_SIZE];
       QTimer *timer;
       QTimer *ECGcaltimer;
       QTimer *ECGleadswitch;
       QTimer *timerstop;
signals:
//       void ECG1Lead(int);
//       void ECG2Lead(int);
//       void ECG1Gain(int);
//       void ECG2Gain(int);
       void ECGSIGNAL(char,int,int);
       void SendECGInfo(QString);
//       void timerstop();
private slots:
      void UpdateUI();
      void ECGcalibrate();
      void ECGlead();
      void istimerstop();
      void on_btnECGModel_clicked();
      void on_btnDiagnoseModel_clicked();
      void on_btnECGcall_clicked();
      void on_btnECGFreeze_clicked();
      void on_btnLeadswitch_clicked();
      void on_btnECG1lead_clicked();
      void on_btnECG2lead_clicked();
      void on_btnECG1gain_clicked();
      void on_btnECG2gain_clicked();
      void LoadConfigure(bool langue);
      void SetReflesh(bool Isfreeze);
};

#endif // WAVEFORM_H
