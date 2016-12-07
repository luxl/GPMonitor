#ifndef COLORCHART_H
#define COLORCHART_H

#include <QWidget>

namespace Ui {
class ColorChart;
}

class ColorChart : public QWidget
{
    Q_OBJECT
    
public:
    explicit ColorChart(QWidget *parent = 0);
    ~ColorChart();
public slots:
    void IRProc(unsigned char code);
private slots:
    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

//    void on_btnPass_clicked();

//    void on_btnFail_clicked();

//    void on_btnResult_clicked();

//    void on_btnRestart_clicked();
    void Loadcolorlangue(bool langue);

    void on_btnFirstPage_clicked();

    void on_btnLastPage_clicked();

private:
    Ui::ColorChart *ui;
    int index;
    int result[100];
    bool IsChinese;
};

#endif // COLORCHART_H
