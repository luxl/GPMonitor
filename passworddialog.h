#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class PassWordDialog;
}

class PassWordDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PassWordDialog(QWidget *parent = 0);
    ~PassWordDialog();

private slots:
    void on_btnOK_clicked();
    void btnNumslot(int);
    void on_btn_Cancel_clicked();
    void Cleartxt();
    void Loadpswlangue(bool langue);

private:
    Ui::PassWordDialog *ui;
    bool IsChinese;
};

#endif // PASSWORDDIALOG_H
