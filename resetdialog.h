#ifndef RESETDIALOG_H
#define RESETDIALOG_H

#include <QDialog>

namespace Ui {
class ResetDialog;
}

class ResetDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ResetDialog(QWidget *parent = 0);
    ~ResetDialog();
    
private slots:
    void on_btnOK_clicked();

    void on_btn_Cancel_clicked();
    void Loadresetlangue(bool langue);

private:
    Ui::ResetDialog *ui;
    bool IsChinese;
};

#endif // RESETDIALOG_H
