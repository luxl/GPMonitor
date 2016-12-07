#include "resetdialog.h"
#include "ui_resetdialog.h"

ResetDialog::ResetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResetDialog)
{
    ui->setupUi(this);
}

ResetDialog::~ResetDialog()
{
    delete ui;
}

void ResetDialog::on_btnOK_clicked()
{
    this->accept();
    this->close();
}

void ResetDialog::on_btn_Cancel_clicked()
{
    this->reject();
    this->close();
}
void ResetDialog::Loadresetlangue(bool langue)
{
    IsChinese=langue;
    if(IsChinese)
    {
        this->setWindowTitle(QString::fromUtf8("重启"));
        ui->label_25->setText(QString::fromUtf8("确认重启系统么?"));
        ui->label_25->setGeometry(120,100,311,41);
        ui->btnOK->setText(QString::fromUtf8("确认"));
        ui->btn_Cancel->setText(QString::fromUtf8("取消"));
    }
    else
    {
        this->setWindowTitle(QString::fromUtf8("Restart"));
        ui->label_25->setText("Are you sure restart system?");
        ui->label_25->setGeometry(10,100,521,41);
        ui->btnOK->setText("OK");
        ui->btn_Cancel->setText("Cancel");
    }
}
