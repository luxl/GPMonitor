#include "passworddialog.h"
#include "ui_passworddialog.h"
#include <QMessageBox>

PassWordDialog::PassWordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PassWordDialog)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);
//    DialogResult=false;

    ui->Txtpassword->setMaxLength(8);
    ui->Txtpassword->setFocus();
    ui->Txtpassword->setEchoMode(QLineEdit::Password);
    ui->labwarn->setVisible(false);
    QButtonGroup *btngroup=new QButtonGroup();
    btngroup->addButton(ui->btn0,0);
    btngroup->addButton(ui->btn1,1);
    btngroup->addButton(ui->btn2,2);
    btngroup->addButton(ui->btn3,3);
    btngroup->addButton(ui->btn4,4);
    btngroup->addButton(ui->btn5,5);
    btngroup->addButton(ui->btn6,6);
    btngroup->addButton(ui->btn7,7);
    btngroup->addButton(ui->btn8,8);
    btngroup->addButton(ui->btn9,9);
    btngroup->addButton(ui->btnDelete,10);
    connect(btngroup,SIGNAL(buttonClicked(int)),this,SLOT(btnNumslot(int)));
}
void PassWordDialog::btnNumslot(int num)
{
    if(ui->Txtpassword->hasFocus())
    {
        if(num<10)
            ui->Txtpassword->insert(QString::number(num));
        else
            ui->Txtpassword->backspace();
    }
}

PassWordDialog::~PassWordDialog()
{
    delete ui;
}

void PassWordDialog::on_btnOK_clicked()
{
    QString psw=ui->Txtpassword->text().trimmed();
    if(psw!="20000238")
    {
       ui->labwarn->setVisible(true);
        return;
    }
    else
    {
        ui->labwarn->setVisible(false);
        this->accept();
        this->close();
    }
}

void PassWordDialog::on_btn_Cancel_clicked()
{
    this->reject();
    this->close();
}
void PassWordDialog::Cleartxt()
{
    ui->Txtpassword->setText("");
    ui->Txtpassword->setFocus();
    ui->labwarn->setVisible(false);
}
void PassWordDialog::Loadpswlangue(bool langue)
{
    IsChinese=langue;
    if(IsChinese)
    {
        this->setWindowTitle(QString::fromUtf8("密码验证"));
        ui->labwarn->setText(QString::fromUtf8("密码输入错误"));
        ui->label_25->setText(QString::fromUtf8("密码"));
        ui->btnOK->setText(QString::fromUtf8("确认"));
        ui->btn_Cancel->setText(QString::fromUtf8("取消"));
        ui->btnDelete->setText(QString::fromUtf8("删除"));
//        ui->label_25->setGeometry(140,60,131,41);
    }
    else
    {
        this->setWindowTitle("PassWord Confirmation");
        ui->labwarn->setText("Wrong PassWord");
        ui->label_25->setText("PassWord");
        ui->btnOK->setText("OK");
        ui->btn_Cancel->setText("Cancel");
        ui->btnDelete->setText("DEL");
//        ui->label_25->setGeometry(90,60,131,41);
    }
}
