#ifndef VISUALCHART_H
#define VISUALCHART_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

namespace Ui {
class VisualChart;
}

class VisualChart : public QWidget
{
    Q_OBJECT
    
public:
    explicit VisualChart(QWidget *parent = 0);
    ~VisualChart();
    virtual bool eventFilter(QObject *target, QEvent *event);
    void DrawE(int dir);
//    void PainterSet(int x,int y);
public slots:
    void IRProc(unsigned char code);

private slots:
    void on_btnRestart_clicked();

    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

    void on_btnMore_clicked();

//    void on_btnPass_clicked();

//    void on_btnFail_clicked();

//    void on_btnResult_clicked();
    void LoadLangue(bool langue);

private:
    Ui::VisualChart *ui;

    QPainterPath path;
    double xscale,yscale,angle;
    double grade,value,direction;
    double farvisual[14][4];
    double result[14][2];
    int idx;
    bool IsChinese;
};

#endif // VISUALCHART_H
