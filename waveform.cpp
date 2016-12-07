#pragma once
#include "waveform.h"
#include "ui_waveform.h"
#include "comdefs.h"
#include "qwt_painter.h"
#include "qwt_plot_canvas.h"
#include "qwt_plot_marker.h"
#include "qwt_plot_curve.h"
#include "qwt_scale_widget.h"
#include "qwt_legend.h"
#include "qwt_scale_draw.h"
#include "qwt_math.h"
#include "qwt_plot.h"
#include <QTimer>
#include "qwt_plot_grid.h"
#include "comdefs.h"
#include <QDebug>

WaveForm::WaveForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaveForm)
{
    ui->setupUi(this);
    Isfirst=true;
    /// 修改
    ui->qwtPlot_ECG->detachItems();
    ui->qwtPlot_ECG2->detachItems();

    ui->qwtPlot_ECG->setAxisScale(QwtPlot::yLeft,-1000,1000,500);
    ui->qwtPlot_ECG->setAxisScale(QwtPlot::xBottom, 0, PLOT_SIZE,25);
    ui->qwtPlot_ECG2->setAxisScale(QwtPlot::yLeft,-1000,1000,500);
    ui->qwtPlot_ECG2->setAxisScale(QwtPlot::xBottom, 0, PLOT_SIZE,25);

    ui->qwtPlot_ECG->enableAxis(QwtPlot::yLeft,false);
    ui->qwtPlot_ECG->enableAxis(QwtPlot::xBottom,false);
    ui->qwtPlot_ECG2->enableAxis(QwtPlot::yLeft,false);
    ui->qwtPlot_ECG2->enableAxis(QwtPlot::xBottom,false);

    QwtPlotGrid *grid1 = new QwtPlotGrid;
    grid1->enableXMin(true);
    grid1->enableYMin(true);
    QPen minpen;//-qws
    minpen.setColor(QColor::fromRgb(95,0,0));
    QPen majpen;
    majpen.setColor(QColor::fromRgb(127,0,0));
    grid1->setMajorPen(majpen);
    grid1->setMinorPen(minpen);
    grid1->attach(ui->qwtPlot_ECG);
    QwtPlotGrid *grid2 = new QwtPlotGrid;
    grid2->enableXMin(true);
    grid2->enableYMin(true);
    grid2->setMajorPen(majpen);
    grid2->setMinorPen(minpen);
    grid2->attach(ui->qwtPlot_ECG2);
    lead1index=1;
    lead2index=0;
    iscalled=false;
    ecg1currentgain=2;
    ecg2currentgain=2;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(UpdateUI()));
    timer->start(50);
    ECGcaltimer =new QTimer();
    connect(ECGcaltimer,SIGNAL(timeout()),this,SLOT(ECGcalibrate()));
//    ECGleadswitch =new QTimer();
//    connect(ECGleadswitch,SIGNAL(timeout()),this,SLOT(ECGlead()));
//    timerstop =new QTimer();
//    connect(timerstop,SIGNAL(timeout()),this,SLOT(istimerstop()));
    ecgfrontdata=2048;
    maxdiffvalue1=0;
    maxdiffvalue2=0;
    calibrategain1=1;
    calibrategain2=1;
    index=0;
    leadswitch=0;
    ecgmodel=false;
    IsFreezed=false;

    curve1 = new QwtPlotCurve();
    curve2 = new QwtPlotCurve();

    curve1->attach(ui->qwtPlot_ECG);
    curve1->setPen(QPen(Qt::green));

    curve2->attach(ui->qwtPlot_ECG);
    curve2->setPen(QPen(Qt::green));

    curve3 = new QwtPlotCurve();
    curve4 = new QwtPlotCurve();

    curve3->attach(ui->qwtPlot_ECG2);
    curve3->setPen(QPen(Qt::green));

    curve4->attach(ui->qwtPlot_ECG2);
    curve4->setPen(QPen(Qt::green));
    on_btnDiagnoseModel_clicked();
    ui->btnECG1lead->setFlat(true);
//    ui->btnECG1lead->setStyleSheet()
//    FreezeInfo="0";
//    ECGInfo="*"+ui->lab_ECG1lead->text().trimmed()+","+ui->lab_ECG2lead->text().trimmed()+","+QString::number(ecg1currentgain)+","+QString::number(ecg2currentgain)+","+QString::number(calibrategain1)+","+QString::number(calibrategain2)+","+FreezeInfo+","+"#";
//    emit SendECGInfo(ECGInfo);
}

WaveForm::~WaveForm()
{
    delete ui;
}

void WaveForm::updateECGWaveData(int ID, double data1, double data2, double data3)
{
    static int ecgcnt = 0;
    ECGData *data=new ECGData();
    switch(ID)
    {
    case ID_ECGWAVE:
        if(++ecgcnt >=8)
        {
            data->ECG1 = data1;
            data->ECG2 = data2;
            data->FBeat = (bool)data3;
            ecgmsg.push_back(data);
//            qDebug()<<data1<<"\n";
            if(iscalled)
            {
                if(data1-ecgfrontdata>maxdiffvalue1)
                {
                    maxdiffvalue1=data1-ecgfrontdata;
                }
                if(data2-ecgfrontdata>maxdiffvalue2)
                {
                    maxdiffvalue2=data1-ecgfrontdata;
                }
            }
            ecgfrontdata=data1;
            ecgcnt =0;
        }
        break;
//    case ID_SPO2_WAVE:
//        if(++spo2cnt >=2)
//        {
//            data->SPO2=data1;
//            data->SPO2state=data2;
//            ecgmsg.push_back(data);

//            spo2cnt = 0;
//        }
//        break;
    }
}

void WaveForm::PaintECGWave(QwtPlot* plot,int data1,int data2)//,int data3)
{

    d_x[index]=index;
    d_y[index]=data1*calibrategain1;
    d_x1[index]=index;
    d_y1[index]=data2*calibrategain2;

    if(index % 6 == 0)
    {
        if((signed short)Data_HR==-100||Data_HR<0||Data_HR>300)
        {
            ui->lab_HR->setText("--");
        }
        else
        {
            QString val="0";
            ui->lab_HR->setText(val.sprintf("%3.0f",Data_HR));
        }
        if(Isfirst)
        {
            curve1->setSamples(d_x,d_y,index+1);
            curve3->setSamples(d_x1,d_y1,index+1);
        }
        else
        {
            if(index<PLOT_SIZE-5)
            {
                curve1->setSamples(d_x,d_y,index+1);
                curve2->setSamples(d_x+index+5,d_y+index+5,PLOT_SIZE-index-5);
                curve3->setSamples(d_x1,d_y1,index+1);
                curve4->setSamples(d_x1+index+5,d_y1+index+5,PLOT_SIZE-index-5);
                //            curve5->setSamples(d_xspo2,d_yspo2,index);
                //            curve6->setSamples(d_xspo2+index+2,d_yspo2+index+2,PLOT_SIZE1-index-2);
            }
            else
            {
                curve1->setSamples(d_x,d_y,index+1);
                curve3->setSamples(d_x1,d_y1,index+1);
                //            curve5->setSamples(d_xspo2,d_yspo2,index);
            }
        }
        ui->qwtPlot_ECG->replot();
        ui->qwtPlot_ECG2->replot();
    }
    if(++index == PLOT_SIZE)
    {
        index=0;
        Isfirst=false;
        if(ecgmodel)
        {
            IsFreezed=true;
            ui->btnLeadswitch->setEnabled(true);
        }
    }
}

void WaveForm::PaintECGModelWave(QwtPlot* plot,int data1,int data2)//,int data3)
{
    d_x[index]=index;
    d_y[index]=data1*calibrategain1;
    d_x1[index]=index;
    d_y1[index]=data2*calibrategain2;

    if(index % 6 == 0)
    {
        if((signed short)Data_HR==-100||Data_HR<0||Data_HR>300)
        {
            ui->lab_HR->setText("--");
        }
        else
        {
            QString val="0";
            ui->lab_HR->setText(val.sprintf("%3.0f",Data_HR));
        }
        if(index<PLOT_SIZE-5)
        {
            curve1->setSamples(d_x,d_y,index+1);
            curve2->setSamples(d_x+index+5,d_y+index+5,PLOT_SIZE-index-5);
            curve3->setSamples(d_x1,d_y1,index+1);
            curve4->setSamples(d_x1+index+5,d_y1+index+5,PLOT_SIZE-index-5);
            //                curve5->setSamples(d_xspo2,d_yspo2,index);
            //                curve6->setSamples(d_xspo2+index+2,d_yspo2+index+2,PLOT_SIZE1-index-2);
        }
        else
        {
            curve1->setSamples(d_x,d_y,index+1);
            curve3->setSamples(d_x1,d_y1,index+1);
            //                curve5->setSamples(d_xspo2,d_yspo2,index);
        }
        if(!IsFreezed)
        {
        ui->qwtPlot_ECG->replot();
        ui->qwtPlot_ECG2->replot();
        }
        //            ui->qwtPlot_SPO2->replot();
    }
    if(++index == PLOT_SIZE)
    {
        //            timer->stop();
        IsFreezed=true;
        index=0;
        ui->btnLeadswitch->setEnabled(true);
        //            calibrategain=(double)500/maxdiffvalue;
    }
}

void WaveForm::updateHrData(int ID, double data1)
{
    switch(ID)
    {
    case ID_HR:
        Data_HR=data1;
        break;
    }
}
void WaveForm::UpdateUI()
{
    int ecgcout=ecgmsg.count();
    if(ecgcout>0)
    {
        for(int i=0;i<ecgcout;i++)
        {
            ECGData *ecgdata=ecgmsg.front();
            if(!IsFreezed)
                PaintECGWave(ui->qwtPlot_ECG,ecgdata->ECG1-2048,ecgdata->ECG2-2048);
            ecgmsg.pop_front();
            delete ecgdata;
        }
    }
    if(++sendnum==20)
    {
        if(IsFreezed)
            FreezeInfo="1";
        else
            FreezeInfo="0";

        ECGInfo="*"+ui->lab_ECG1lead->text().trimmed()+","+ui->lab_ECG2lead->text().trimmed()+","+QString::number(ecg1currentgain)+","+QString::number(ecg2currentgain)+","+QString::number(calibrategain1)+","+QString::number(calibrategain2)+","+FreezeInfo+","+ui->lab_HR->text().trimmed()+"#";
        emit SendECGInfo(ECGInfo);
        sendnum=0;
    }
}

void WaveForm::on_btnECGModel_clicked()
{
    ui->btnECG1gain->setEnabled(false);
    ui->btnECG1lead->setEnabled(false);
    ui->btnECG2gain->setEnabled(false);
    ui->btnECG2lead->setEnabled(false);
    ui->btnECGModel->setEnabled(false);
    ui->btnDiagnoseModel->setEnabled(true);
//    ui->gbECGmodel->setEnabled(true);
    ui->btnLeadswitch->setEnabled(true);
    ui->btnECGFreeze->setEnabled(true);
    ecgmodel=true;
    IsFreezed=false;
    ecg1currentgain=2;
    ecg2currentgain=2;
//    timer->stop();

//    if(IsFreezed)
//        FreezeInfo="1";
//    else
//        FreezeInfo="0";
//    ECGInfo="*"+ui->lab_ECG1lead->text().trimmed()+","+ui->lab_ECG2lead->text().trimmed()+","+QString::number(ecg1currentgain)+","+QString::number(ecg2currentgain)+","+QString::number(calibrategain1)+","+QString::number(calibrategain2)+","+FreezeInfo+","+"#";
//    emit SendECGInfo(ECGInfo);
}

void WaveForm::on_btnDiagnoseModel_clicked()
{
    ui->btnECG1gain->setEnabled(true);
    ui->btnECG1lead->setEnabled(true);
    ui->btnECG2gain->setEnabled(true);
    ui->btnECG2lead->setEnabled(true);
    ui->btnDiagnoseModel->setEnabled(false);
    ui->btnECGModel->setEnabled(true);
    ui->btnLeadswitch->setEnabled(false);
    ui->btnECGFreeze->setEnabled(false);
    ecgmodel=false;
    if(!timer->isActive())
        timer->start(50);
    IsFreezed=false;
}

void WaveForm::on_btnECGcall_clicked()
{
    iscalled=true;
    if(ecg1currentgain!=1||ecg2currentgain!=1)
    {
        ecg1currentgain=1;
        ecg2currentgain=1;
        on_btnECG1gain_clicked();
        on_btnECG2gain_clicked();
    }
    emit ECGSIGNAL(CMD_ECG_CAL,1,0);
    IsFreezed=false;
    ECGcaltimer->start(2000);
}
void WaveForm::ECGcalibrate()
{
    emit ECGSIGNAL(CMD_ECG_CAL,0,0);
    ECGcaltimer->stop();
//    qDebug()<<maxdiffvalue1;
//    qDebug()<<maxdiffvalue2;
    iscalled=false;
    calibrategain1=(double)500/maxdiffvalue1;
    calibrategain2=(double)500/maxdiffvalue2;
}

void WaveForm::on_btnECGFreeze_clicked()
{
    if(IsFreezed==true)
        IsFreezed=false;
    else
        IsFreezed=true;
}

void WaveForm::on_btnLeadswitch_clicked()
{
//    if(!timer->isActive())
//        timer->start(50);=
//    leadswitch=0;
    ui->btnLeadswitch->setEnabled(false);
    IsFreezed=false;
    ECGlead();
//    leadswitch++;
//    ECGleadswitch->start(2500);
}
void WaveForm::ECGlead()
{
//    qDebug()<<leadswitch<<"\n";
    if(leadswitch<3)
    {
        emit ECGSIGNAL(CMD_LEADTYPE,1,leadswitch);
        emit ECGSIGNAL(CMD_LEADTYPE,2,leadswitch+3);

    }
//    qDebug()<<leadswitch<<"\n";
    if(leadswitch==3)
    {
        emit ECGSIGNAL(CMD_LEADTYPE,2,leadswitch+3);
        leadswitch=0;
//        ECGleadswitch->stop();
    }
    else
        leadswitch++;
    switch(leadswitch)
    {
    case 1:
        ui->lab_ECG1lead->setText("I");
        ui->lab_ECG2lead->setText("AVR");
        lead1index=0;
        lead2index=3;
        break;
    case 2:
        ui->lab_ECG1lead->setText("II");
        ui->lab_ECG2lead->setText("AVL");
        lead1index=1;
        lead2index=4;
        break;
    case 3:
        ui->lab_ECG1lead->setText("III");
        ui->lab_ECG2lead->setText("AVF");
        lead1index=2;
        lead2index=5;
        break;
    case 0:
        ui->lab_ECG1lead->setText("III");
        ui->lab_ECG2lead->setText("V");
        lead1index=2;
        lead2index=6;
        break;
    }
    ui->lab_ECG1lead->setVisible(true);
    ui->lab_ECG2lead->setVisible(true);
//    timerstop->start(2000);

}
void WaveForm::istimerstop()
{
    timer->start(50);
    timerstop->stop();
}

void WaveForm::on_btnECG1lead_clicked()
{
    int curindex=lead1index;
    if(curindex<2)
    {
        curindex++;
        if(curindex==lead2index)
        {
            if(lead2index==1)
                curindex=2;
            else if(lead2index==2)
                curindex=0;
        }
    }
    else
    {
        if(lead2index==0)
            curindex=1;
        else
            curindex=0;
    }
    lead1index=curindex;
    emit ECGSIGNAL(CMD_LEADTYPE,1,curindex);
    switch(curindex)
    {
    case 0:
        ui->lab_ECG1lead->setText("I");
        break;
    case 1:
        ui->lab_ECG1lead->setText("II");
        break;
    case 2:
        ui->lab_ECG1lead->setText("III");
        break;
    }
}

void WaveForm::on_btnECG2lead_clicked()
{
    int curindex=lead2index;
    if(curindex<6)
    {
        curindex++;
        if(curindex==lead1index)
            curindex++;
    }
    else
    {
        if(lead1index==0)
            curindex=1;
        else
            curindex=0;
    }
    lead2index=curindex;
    emit ECGSIGNAL(CMD_LEADTYPE,2,curindex);
    switch(curindex)
    {
    case 0:
        ui->lab_ECG2lead->setText("I");
        break;
    case 1:
        ui->lab_ECG2lead->setText("II");
        break;
    case 2:
        ui->lab_ECG2lead->setText("III");
        break;
    case 3:
        ui->lab_ECG2lead->setText("AVR");
        break;
    case 4:
        ui->lab_ECG2lead->setText("AVL");
        break;
    case 5:
        ui->lab_ECG2lead->setText("AVF");
        break;
    case 6:
        ui->lab_ECG2lead->setText("v");
        break;
    }
}

void WaveForm::on_btnECG1gain_clicked()
{
    int gainindex=ecg1currentgain;
    if(gainindex<3)
        gainindex++;
    else
        gainindex=0;
    emit ECGSIGNAL(CMD_ECG_GAIN,1,gainindex);
    ecg1currentgain=gainindex;
    switch(gainindex)
    {
    case 0:
        ui->lab_ECG1Gain->setText("X0.25");
        break;
    case 1:
        ui->lab_ECG1Gain->setText("X0.5");
        break;
    case 2:
        ui->lab_ECG1Gain->setText("X1");
        break;
    case 3:
        ui->lab_ECG1Gain->setText("X2");
        break;
    }
}

void WaveForm::on_btnECG2gain_clicked()
{
    int gainindex=ecg2currentgain;
    if(gainindex<3)
        gainindex++;
    else
        gainindex=0;
    emit ECGSIGNAL(CMD_ECG_GAIN,2,gainindex);
    ecg2currentgain=gainindex;
    switch(gainindex)
    {
    case 0:
        ui->lab_ECG2Gain->setText("X0.25");
        break;
    case 1:
        ui->lab_ECG2Gain->setText("X0.5");
        break;
    case 2:
        ui->lab_ECG2Gain->setText("X1");
        break;
    case 3:
        ui->lab_ECG2Gain->setText("X2");
        break;
    }
}

void WaveForm::LoadConfigure(bool langue)
{
    IsChinese=langue;
    if(IsChinese)
    {
        ui->lab_hrtag->setText(QString::fromUtf8("心率:"));
        ui->btnECG1lead->setText(QString::fromUtf8("导联切换"));
        ui->btnECG1gain->setText(QString::fromUtf8("增益切换"));
        ui->btnECG2lead->setText(QString::fromUtf8("导联切换"));
        ui->btnECG2gain->setText(QString::fromUtf8("增益切换"));
        ui->btnECGcall->setText(QString::fromUtf8("定    标"));
        ui->btnECGFreeze->setText(QString::fromUtf8("冻    结"));
        ui->btnECGModel->setText(QString::fromUtf8("心电图模式"));
        ui->btnDiagnoseModel->setText(QString::fromUtf8("监护模式"));
        ui->btnLeadswitch->setText(QString::fromUtf8("导联切换"));
        ui->lab_ECGSET->setText(QString::fromUtf8("心\n电\n设\n置"));
        ui->lab_lead1set->setText(QString::fromUtf8("导联设置"));
        ui->lab_lead2set->setText(QString::fromUtf8("导联设置"));
        ui->lab_gain1set->setText(QString::fromUtf8("增益设置"));
        ui->lab_gain2set->setText(QString::fromUtf8("增益设置"));
//        ui->gpecgchannel1->setTitle(QString::fromUtf8("心电通道1"));
//        ui->gpecgchannel2->setTitle(QString::fromUtf8("心电通道2"));
//        ui->gpother->setTitle(QString::fromUtf8("其他"));
        ui->btnECGChanel1->setText(QString::fromUtf8("心电通道1"));
        ui->btnECGChanel2->setText(QString::fromUtf8("心电通道2"));
        ui->btnOther->setText(QString::fromUtf8("其    他"));
        ui->lab_ecg1leadtag->setText(QString::fromUtf8("导联"));
        ui->lab_ecg1gaintag->setText(QString::fromUtf8("增益"));
        ui->lab_ecg2leadtag->setText(QString::fromUtf8("导联"));
        ui->lab_ecg2gaintag->setText(QString::fromUtf8("增益"));
    }
    else
    {
        ui->lab_hrtag->setText("HR:");
        ui->btnECG1lead->setText("LeadChange");
        ui->btnECG1gain->setText("GainChange");
        ui->btnECG2lead->setText("LeadChange");
        ui->btnECG2gain->setText("GainChange");
        ui->btnECGcall->setText("Calibrate");
        ui->btnECGFreeze->setText("Freezing");
        ui->btnECGModel->setText("ECGModel");
        ui->btnDiagnoseModel->setText("MonitorModel");
        ui->btnLeadswitch->setText("LeadChange");
        ui->lab_ECGSET->setText("ECG\nSET");
        ui->lab_lead1set->setText("Lead Set");
        ui->lab_lead2set->setText("Lead Set");
        ui->lab_gain1set->setText("Gain Set");
        ui->lab_gain2set->setText("Gain Set");
//        ui->gpecgchannel1->setTitle("ECG Channel1");
//        ui->gpecgchannel2->setTitle("ECG Channel2");
//        ui->gpother->setTitle("Other");
        ui->btnECGChanel1->setText(QString::fromUtf8("ECG Channel1"));
        ui->btnECGChanel2->setText(QString::fromUtf8("ECG Channel2"));
        ui->btnOther->setText(QString::fromUtf8("Other"));
        ui->lab_ecg1leadtag->setText("Lead");
        ui->lab_ecg1gaintag->setText("Gain");
        ui->lab_ecg2leadtag->setText("Lead");
        ui->lab_ecg2gaintag->setText("Gain");
    }
}

void WaveForm::SetReflesh(bool Isfreeze)
{
    IsFreezed=Isfreeze;
}
