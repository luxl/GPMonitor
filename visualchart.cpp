#include "visualchart.h"
#include "ui_visualchart.h"
#include "IRCommand.h"
#include <QTime>

VisualChart::VisualChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualChart)
{
    ui->setupUi(this);

    path.moveTo(0,0);
    path.lineTo(4,0);
    path.moveTo(0,0);
    path.lineTo(0,4);
    path.moveTo(0,2);
    path.lineTo(4,2);
    path.moveTo(0,4);
    path.lineTo(4,4);

    double xratio = 1000/163.0 , yratio = 600/99.0;
    farvisual[0][0]=4.0, farvisual[0][1]=0.10, farvisual[0][2] = 72.72/2*xratio, farvisual[0][3]=72.72/2*yratio;
    farvisual[1][0]=4.1, farvisual[1][1]=0.12, farvisual[1][2] = 57.76/2*xratio, farvisual[1][3]=57.76/2*yratio;
    farvisual[2][0]=4.2, farvisual[2][1]=0.15, farvisual[2][2] = 45.88/2*xratio, farvisual[2][3]=45.88/2*yratio;
    farvisual[3][0]=4.3, farvisual[3][1]=0.20, farvisual[3][2] = 36.45/2*xratio, farvisual[3][3]=36.45/2*yratio;
    farvisual[4][0]=4.4, farvisual[4][1]=0.25, farvisual[4][2] = 28.95/2*xratio, farvisual[4][3]=28.95/2*yratio;
    farvisual[5][0]=4.5, farvisual[5][1]=0.30, farvisual[5][2] = 23.00/2*xratio, farvisual[5][3]=23.00/2*yratio;
    farvisual[6][0]=4.6, farvisual[6][1]=0.40, farvisual[6][2] = 18.27/2*xratio, farvisual[6][3]=18.27/2*yratio;
    farvisual[7][0]=4.7, farvisual[7][1]=0.50, farvisual[7][2] = 14.51/2*xratio, farvisual[7][3]=14.51/2*yratio;
    farvisual[8][0]=4.8, farvisual[8][1]=0.60, farvisual[8][2] = 11.53/2*xratio, farvisual[8][3]=11.53/2*yratio;
    farvisual[9][0]=4.9, farvisual[9][1]=0.80, farvisual[9][2] = 9.16/2*xratio, farvisual[9][3]=9.16/2*yratio;
    farvisual[10][0]=5.0, farvisual[10][1]=1.00, farvisual[10][2] = 7.27/2*xratio, farvisual[10][3]=7.27/2*yratio;
    farvisual[11][0]=5.1, farvisual[11][1]=1.20, farvisual[11][2] = 5.78/2*xratio, farvisual[11][3]=5.78/2*yratio;
    farvisual[12][0]=5.2, farvisual[12][1]=1.50, farvisual[12][2] = 4.59/2*xratio, farvisual[12][3]=4.59/2*yratio;
    farvisual[13][0]=5.3, farvisual[13][1]=2.00, farvisual[13][2] = 3.64/2*xratio, farvisual[13][3]=3.64/2*yratio;

    ui->chart->installEventFilter(this);

    qsrand((unsigned)QTime::currentTime().msec());
    on_btnRestart_clicked();
}

VisualChart::~VisualChart()
{
    delete ui;
}

bool VisualChart::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->chart) {
        if (event->type() == QEvent::Paint) {
            QPainter *painter = new QPainter(ui->chart);
            QPen pen(Qt::SolidLine);
            pen.setJoinStyle(Qt::MiterJoin);
            pen.setColor(Qt::black);
            pen.setWidth(1);
            painter->setPen(pen); //ӻ

            QBrush brush(Qt::black);
            brush.setStyle(Qt::SolidPattern);
            painter->setBrush(brush); //ӻˢ
            painter->setWindow(-500,-300,1000,600);
            painter->rotate(angle);
            painter->translate(-2 * xscale,-2 * yscale);
            painter->scale(xscale,yscale);
            painter->drawPath(path);

            QPainter *painterleft = new QPainter(ui->chart);
            painterleft->setPen(pen); //ӻ

            painterleft->setBrush(brush); //ӻˢ
            double xpitch=0;
            if(grade!=5.2&&grade!=5.1)
                xpitch=(grade-4)*10;
            else if(grade==5.1)
                xpitch=10.5;
            else
                xpitch=11;
            painterleft->setWindow(-200-25*xpitch,-300,1000,600);
            double leftdir=qrand()%4*90.0;
            while(leftdir==angle)
            {
                leftdir=qrand()%4*90.0;
            }
            painterleft->rotate(leftdir);
            painterleft->translate(-2 * xscale,-2 * yscale);
            painterleft->scale(xscale,yscale);

//            painter->drawPath(path);
            painterleft->drawPath(path);

            QPainter *painterright = new QPainter(ui->chart);
            painterright->setPen(pen); //ӻ

            painterright->setBrush(brush); //ӻˢ
            painterright->setWindow(-800+25*xpitch,-300,1000,600);
            double rightdir=qrand()%4*90.0;
            while(rightdir==angle)
            {
                rightdir=qrand()%4*90.0;
            }
            painterright->rotate(rightdir);
            painterright->translate(-2 * xscale,-2 * yscale);
            painterright->scale(xscale,yscale);

            painterright->drawPath(path);
            //delete painter;
            return true;
        }
    }
    return QWidget::eventFilter(target, event);
}
//void VisualChart::PainterSet(int x,int y)
//{
//    QPainter *painterleft = new QPainter(ui->chart);
//    QPen pen(Qt::SolidLine);
//    pen.setJoinStyle(Qt::MiterJoin);
//    pen.setColor(Qt::black);
//    pen.setWidth(1);
//    painterleft->setPen(pen); //ӻ

//    QBrush brush(Qt::black);
//    brush.setStyle(Qt::SolidPattern);
//    painterleft->setBrush(brush); //ӻˢ
//    painterleft->setWindow(x,y,1000,600);
//    painterleft->rotate(angle);
//    painterleft->translate(-2 * xscale,-2 * yscale);
//    painterleft->scale(xscale,yscale);

//    painterleft->drawPath(path);

////    DrawE(-1);
//}
void VisualChart::DrawE(int dir)
{
    double width = 0,height = 0;
    if(dir == -1) //random
        direction = qrand() % 4;
    else
        direction = dir;

    grade = farvisual[idx][0];
    value = farvisual[idx][1];
    width = farvisual[idx][2];
    height = farvisual[idx][3];

    xscale = width / 5.0;
    yscale = height / 5.0;
    angle = direction * 90.0;

    QString val;
    val.sprintf("%0.1f",grade);
    ui->lblLevel->setText(val);
    val.sprintf("%0.2f",value);
    ui->lblValue->setText(val);
    ui->chart->update();
}

void VisualChart::IRProc(unsigned char code)
{
    if(this->isVisible())
    {
        switch(code)
        {
        case IR_UP:
            DrawE(3);
            break;
        case IR_DOWN:
            DrawE(1);
            break;
        case IR_LEFT:
            DrawE(2);
            break;
        case IR_RIGHT:
            DrawE(0);
            break;
        case IR_ENTER:
            on_btnMore_clicked();
            break;
        case IR_PRINT:
            on_btnPrevious_clicked();
            break;
        case IR_VISUALLOW:
            on_btnNext_clicked();
//            break;
//        case IR_YES:
//            on_btnPass_clicked();
//            break;
//        case IR_NO:
//            on_btnFail_clicked();
//            break;
//        case IR_SHOW:
//            on_btnResult_clicked();
//            break;
//        case IR_CLEAR:
//            on_btnRestart_clicked();
//            break;
        }
    }
}

void VisualChart::on_btnPrevious_clicked()
{

    if(--idx < 0)
        idx = 0;
    DrawE(-1);
}

void VisualChart::on_btnNext_clicked()
{
//    PainterSet(-100,300);
//    PainterSet(100,300);
    if(++idx > 13)
        idx = 13;
    DrawE(-1);
}

void VisualChart::on_btnMore_clicked()
{
    DrawE(-1);
}

//void VisualChart::on_btnPass_clicked()
//{
//    result[idx][0] ++;
//    result[idx][1] ++;
//    DrawE(-1);
//}

//void VisualChart::on_btnFail_clicked()
//{
//    result[idx][0] ++;
//    DrawE(-1);
//}

//void VisualChart::on_btnResult_clicked()
//{
//    double rate;
//    for(int i=0; i<=13; i++)
//    {
//        if(result[i][0] == 0)
//            rate =0;
//        else
//            rate = result[i][1]*100.0/result[i][0];

//        if(rate < 75)
//        {
//            if(--idx < 0) idx =0;
//            ui->lblLevel->setStyleSheet("color: rgb(255,0,0);");
//            ui->lblValue->setStyleSheet("color: rgb(255,0,0);");
//            DrawE(-1);
//            break;
//        }
//    }

//}

void VisualChart::on_btnRestart_clicked()
{
    for(int i=0; i<14; i++)
    {
        result[i][0] = 0;
        result[i][1] = 0;
    }
    idx = 0;

    ui->lblLevel->setStyleSheet("color: rgb(0,0,255);");
    ui->lblValue->setStyleSheet("color: rgb(0,255,0);");
    DrawE(-1);
}

void VisualChart::LoadLangue(bool langue)
{
    IsChinese=langue;
    if(IsChinese)
    {
        ui->btnPrevious->setText(QString::fromUtf8("视力+"));
        ui->btnNext->setText(QString::fromUtf8("视力-"));
        ui->btnMore->setText(QString::fromUtf8("随机"));
//        ui->btnPass->setText(QString::fromUtf8("正确"));
//        ui->btnFail->setText(QString::fromUtf8("错误"));
        ui->btnRestart->setText(QString::fromUtf8("复位"));
//        ui->btnResult->setText(QString::fromUtf8("结果"));

    }
    else
    {
        ui->btnPrevious->setText("Eyesight+");
        ui->btnNext->setText("Eyesight-");
        ui->btnMore->setText("Random");
//        ui->btnPass->setText("Right");
//        ui->btnFail->setText("Fault");
        ui->btnRestart->setText("Reset");
//        ui->btnResult->setText("Result");
    }
}
