#include "colorchart.h"
#include "ui_colorchart.h"
#include "IRCommand.h"

ColorChart::ColorChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorChart)
{
    ui->setupUi(this);

//    on_btnRestart_clicked();
    on_btnFirstPage_clicked();
}

ColorChart::~ColorChart()
{
    delete ui;
}

void ColorChart::on_btnPrevious_clicked()
{
    if(index>0)
        index--;
    QString str;
    str.sprintf("%03d",index);

    ui->frame->setStyleSheet("background-image: url(:/rsc/images/color" + str + ".jpg);");
}

void ColorChart::on_btnNext_clicked()
{
    if(index<39)
        index++;
    QString str;
    str.sprintf("%03d",index);

    ui->frame->setStyleSheet("background-image: url(:/rsc/images/color" + str + ".jpg);");
}

//void ColorChart::on_btnPass_clicked()
//{
//    result[index] = 1;
//    on_btnNext_clicked();
//}

//void ColorChart::on_btnFail_clicked()
//{
//    result[index] = 2;
//    on_btnNext_clicked();
//}

//void ColorChart::on_btnResult_clicked()
//{
//    int passcnt = 0, failcnt = 0;
//    for(int i=0; i< 100; i++)
//    {
//        if(result[i] == 1) passcnt++;
//        if(result[i] == 2) failcnt++;
//    }

//    if(failcnt == 0)
//    {
//        if(passcnt > 0)
//        {
//            if(IsChinese)
//                ui->lblResult->setText(QString::fromUtf8("色觉正常"));
//            else
//                ui->lblResult->setText("Color vision is nomal");
//        }
//        else
//        {
//            if(IsChinese)
//                ui->lblResult->setText(QString::fromUtf8("测试结果未知"));
//            else
//                ui->lblResult->setText("Test result is unknown");
//        }
//    }
//    else
//    {
//    }

//    ui->lblResult->setVisible(true);
//}

//void ColorChart::on_btnRestart_clicked()
//{
//    for(int i=0; i<100; i++)
//        result[i] = 0;
//    index = 0;
//    ui->frame->setStyleSheet("background-image: url(:/rsc/images/color000.jpg);");
//    ui->lblResult->setStyleSheet("background-color: rgb(0,0,127); color:rgb(255,255,255);");
//    ui->lblResult->setVisible(false);
//}

void ColorChart::IRProc(unsigned char code)
{
    if(this->isVisible())
    {
        switch(code)
        {
        case IR_LEFT:
            on_btnPrevious_clicked();
            break;
        case IR_RIGHT:
            on_btnNext_clicked();
            break;
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
            break;
//        case IR_BLOODPRE:
//            on_btnBPStart_clicked();
//        break;
        }
    }
}

void ColorChart::Loadcolorlangue(bool langue)
{
    IsChinese=langue;
    if(IsChinese)
    {
        ui->btnPrevious->setText(QString::fromUtf8("上一页"));
        ui->btnNext->setText(QString::fromUtf8("下一页"));
        ui->btnFirstPage->setText(QString::fromUtf8("第一页"));
        ui->btnLastPage->setText(QString::fromUtf8("最后一页"));
//        ui->btnPass->setText(QString::fromUtf8("正确"));
//        ui->btnFail->setText(QString::fromUtf8("错误"));
//        ui->btnRestart->setText(QString::fromUtf8("清除"));
//        ui->btnResult->setText(QString::fromUtf8("结果"));
    }
    else
    {
        ui->btnPrevious->setText("Previous");
        ui->btnNext->setText("Next");
        ui->btnFirstPage->setText(QString::fromUtf8("First Page"));
        ui->btnLastPage->setText(QString::fromUtf8("Last Page"));
//        ui->btnPass->setText("Right");
//        ui->btnFail->setText("Fault");
//        ui->btnRestart->setText("Clear");
//        ui->btnResult->setText("Result");
    }
}

void ColorChart::on_btnFirstPage_clicked()
{
    index = 0;
    ui->frame->setStyleSheet("background-image: url(:/rsc/images/color000.jpg);");
//    ui->lblResult->setStyleSheet("background-color: rgb(0,0,127); color:rgb(255,255,255);");
//    ui->lblResult->setVisible(false);
}

void ColorChart::on_btnLastPage_clicked()
{
    index = 39;
    ui->frame->setStyleSheet("background-image: url(:/rsc/images/color039.jpg);");
}
