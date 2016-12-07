#ifndef CALIBRATEDIALOG_H
#define CALIBRATEDIALOG_H

#include <QDialog>
#include <QHash>
#include <QtWidgets/QLineEdit>
#include <QtCore/QTimer>

namespace Ui {
class CalibrateDialog;
}

class CalibrateDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CalibrateDialog(QWidget *parent = 0);
    ~CalibrateDialog();

    // 校准数据
    void updateData(int data);
    void updateUI();
signals:
    // 校准结束，打开压力阀门
    void openValve();
    
private slots:
    void on_btn_Cancel_clicked();
    void btnNumslot(int num);

    void on_btnOK_clicked();
    void Createxml();
    void Readxml();
    void loadlanguexml(bool IsChinese);

    void updateInput();

private:
    int calData;  //校准值
    QHash<QString, QString> hash;
    QLineEdit* input[10];
    QLineEdit* output[10];
    QLineEdit* lastSelected;
    QTimer* timer;

    Ui::CalibrateDialog *ui;
    int hrinput1,hrinput2,hrinput3,hrinput4,hrinput5,hrinput6,hrinput7,hrinput8,hrinput9,hrinput10;
    int hroutput1,hroutput2,hroutput3,hroutput4,hroutput5,hroutput6,hroutput7,hroutput8,hroutput9,hroutput10;
    int spo2input1,spo2input2,spo2input3,spo2input4,spo2input5,spo2input6,spo2input7,spo2input8,spo2input9,spo2input10;
    int spo2output1,spo2output2,spo2output3,spo2output4,spo2output5,spo2output6,spo2output7,spo2output8,spo2output9,spo2output10;
    int diainput1,diainput2,diainput3,diainput4,diainput5,diainput6,diainput7,diainput8,diainput9,diainput10;
    int diaoutput1,diaoutput2,diaoutput3,diaoutput4,diaoutput5,diaoutput6,diaoutput7,diaoutput8,diaoutput9,diaoutput10;
    int averinput1,averinput2,averinput3,averinput4,averinput5,averinput6,averinput7,averinput8,averinput9,averinput10;
    int averoutput1,averoutput2,averoutput3,averoutput4,averoutput5,averoutput6,averoutput7,averoutput8,averoutput9,averoutput10;
    int sysinput1,sysinput2,sysinput3,sysinput4,sysinput5,sysinput6,sysinput7,sysinput8,sysinput9,sysinput10;
    int sysoutput1,sysoutput2,sysoutput3,sysoutput4,sysoutput5,sysoutput6,sysoutput7,sysoutput8,sysoutput9,sysoutput10;
    QString pathdir;

    bool close();
    void initHashTable();
    void initLineEdit();
};

#endif // CALIBRATEDIALOG_H
