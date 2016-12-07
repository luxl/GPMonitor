#include "calibratedialog.h"
#include "ui_calibratedialog.h"
#include <QtXml>

CalibrateDialog::CalibrateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrateDialog)
{
    ui->setupUi(this);

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
    QDir dir;
    pathdir=dir.currentPath();
    Readxml();

    calData = 0;
    initLineEdit();
    initHashTable();
    timer = new QTimer(this);
    lastSelected = NULL;
    timer->start(200);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateInput()));
    for(int i = 0; i < 10; i++){
        output[i]->setReadOnly(true);
    }
    ui->gpaver->close();
    ui->gpdia->close();
}

CalibrateDialog::~CalibrateDialog()
{
    delete ui;
}

void CalibrateDialog::on_btn_Cancel_clicked()
{
    this->close();
}
void CalibrateDialog::btnNumslot(int num)
{
        if(ui->Txthrinput1->hasFocus())
        {
            if(num<10)
                ui->Txthrinput1->insert(QString::number(num));
            else if(num==10)
                ui->Txthrinput1->backspace();
        }
        else if(ui->Txthrinput2->hasFocus())
        {
            if(num<10)
                ui->Txthrinput2->insert(QString::number(num));
            else if(num==10)
                ui->Txthrinput2->backspace();
        }
        else if(ui->Txthrinput3->hasFocus())
        {
            if(num<10)
                ui->Txthrinput3->insert(QString::number(num));
            else if(num==10)
                ui->Txthrinput3->backspace();
        }
        else if(ui->Txthrinput4->hasFocus())
        {
            if(num<10)
                ui->Txthrinput4->insert(QString::number(num));
            else if(num==10)
                ui->Txthrinput4->backspace();
        }
        else if(ui->Txthrinput5->hasFocus())
        {
            if(num<10)
                ui->Txthrinput5->insert(QString::number(num));
            else if(num==10)
                ui->Txthrinput5->backspace();
        }
        else if(ui->Txthrinput6->hasFocus())
        {
            if(num<10)
                ui->Txthrinput6->insert(QString::number(num));
            else if(num==10)
                ui->Txthrinput6->backspace();
        }
        else if(ui->Txthrinput7->hasFocus())
        {
            if(num<10)
                ui->Txthrinput7->insert(QString::number(num));
            else if(num==10)
                ui->Txthrinput7->backspace();
        }
        else if(ui->Txthrinput8->hasFocus())
        {
            if(num<10)
                ui->Txthrinput8->insert(QString::number(num));
            else if(num==10)
                ui->Txthrinput8->backspace();
        }
        else if(ui->Txthrinput9->hasFocus())
        {
            if(num<10)
                ui->Txthrinput9->insert(QString::number(num));
            else if(num==10)
                ui->Txthrinput9->backspace();
        }
        else if(ui->Txthrinput10->hasFocus())
        {
            if(num<10)
                ui->Txthrinput10->insert(QString::number(num));
            else if(num==10)
                ui->Txthrinput10->backspace();
        }
        else if(ui->Txthroutput1->hasFocus())
        {
            if(num<10)
                ui->Txthroutput1->insert(QString::number(num));
            else if(num==10)
                ui->Txthroutput1->backspace();
        }
        else if(ui->Txthroutput2->hasFocus())
        {
            if(num<10)
                ui->Txthroutput2->insert(QString::number(num));
            else if(num==10)
                ui->Txthroutput2->backspace();
        }
        else if(ui->Txthroutput3->hasFocus())
        {
            if(num<10)
                ui->Txthroutput3->insert(QString::number(num));
            else if(num==10)
                ui->Txthroutput3->backspace();
        }
        else if(ui->Txthroutput4->hasFocus())
        {
            if(num<10)
                ui->Txthroutput4->insert(QString::number(num));
            else if(num==10)
                ui->Txthroutput4->backspace();
        }
        else if(ui->Txthroutput5->hasFocus())
        {
            if(num<10)
                ui->Txthroutput5->insert(QString::number(num));
            else if(num==10)
                ui->Txthroutput5->backspace();
        }
        else if(ui->Txthroutput6->hasFocus())
        {
            if(num<10)
                ui->Txthroutput6->insert(QString::number(num));
            else if(num==10)
                ui->Txthroutput6->backspace();
        }
        else if(ui->Txthroutput7->hasFocus())
        {
            if(num<10)
                ui->Txthroutput7->insert(QString::number(num));
            else if(num==10)
                ui->Txthroutput7->backspace();
        }
        else if(ui->Txthroutput8->hasFocus())
        {
            if(num<10)
                ui->Txthroutput8->insert(QString::number(num));
            else if(num==10)
                ui->Txthroutput8->backspace();
        }
        else if(ui->Txthroutput9->hasFocus())
        {
            if(num<10)
                ui->Txthroutput9->insert(QString::number(num));
            else if(num==10)
                ui->Txthroutput9->backspace();
        }
        else if(ui->Txthroutput10->hasFocus())
        {
            if(num<10)
                ui->Txthroutput10->insert(QString::number(num));
            else if(num==10)
                ui->Txthroutput10->backspace();
        }
        else if(ui->Txtspo2input1->hasFocus())
        {
            if(num<10)
                ui->Txtspo2input1->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2input1->backspace();
        }
        else if(ui->Txtspo2input2->hasFocus())
        {
            if(num<10)
                ui->Txtspo2input2->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2input2->backspace();
        }
        else if(ui->Txtspo2input3->hasFocus())
        {
            if(num<10)
                ui->Txtspo2input3->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2input3->backspace();
        }
        else if(ui->Txtspo2input4->hasFocus())
        {
            if(num<10)
                ui->Txtspo2input4->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2input4->backspace();
        }
        else if(ui->Txtspo2input5->hasFocus())
        {
            if(num<10)
                ui->Txtspo2input5->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2input5->backspace();
        }
        else if(ui->Txtspo2input6->hasFocus())
        {
            if(num<10)
                ui->Txtspo2input6->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2input6->backspace();
        }
        else if(ui->Txtspo2input7->hasFocus())
        {
            if(num<10)
                ui->Txtspo2input7->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2input7->backspace();
        }
        else if(ui->Txtspo2input8->hasFocus())
        {
            if(num<10)
                ui->Txtspo2input8->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2input8->backspace();
        }
        else if(ui->Txtspo2input9->hasFocus())
        {
            if(num<10)
                ui->Txtspo2input9->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2input9->backspace();
        }
        else if(ui->Txtspo2input10->hasFocus())
        {
            if(num<10)
                ui->Txtspo2input10->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2input10->backspace();
        }
        else if(ui->Txtspo2output1->hasFocus())
        {
            if(num<10)
                ui->Txtspo2output1->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2output1->backspace();
        }
        else if(ui->Txtspo2output2->hasFocus())
        {
            if(num<10)
                ui->Txtspo2output2->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2output2->backspace();
        }
        else if(ui->Txtspo2output3->hasFocus())
        {
            if(num<10)
                ui->Txtspo2output3->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2output3->backspace();
        }
        else if(ui->Txtspo2output4->hasFocus())
        {
            if(num<10)
                ui->Txtspo2output4->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2output4->backspace();
        }
        else if(ui->Txtspo2output5->hasFocus())
        {
            if(num<10)
                ui->Txtspo2output5->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2output5->backspace();
        }
        else if(ui->Txtspo2output6->hasFocus())
        {
            if(num<10)
                ui->Txtspo2output6->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2output6->backspace();
        }
        else if(ui->Txtspo2output7->hasFocus())
        {
            if(num<10)
                ui->Txtspo2output7->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2output7->backspace();
        }
        else if(ui->Txtspo2output8->hasFocus())
        {
            if(num<10)
                ui->Txtspo2output8->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2output8->backspace();
        }
        else if(ui->Txtspo2output9->hasFocus())
        {
            if(num<10)
                ui->Txtspo2output9->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2output9->backspace();
        }
        else if(ui->Txtspo2output10->hasFocus())
        {
            if(num<10)
                ui->Txtspo2output10->insert(QString::number(num));
            else if(num==10)
                ui->Txtspo2output10->backspace();
        }
        else if(ui->Txtsysinput1->hasFocus())
        {
            if(num<10)
                ui->Txtsysinput1->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysinput1->backspace();
        }
        else if(ui->Txtsysinput2->hasFocus())
        {
            if(num<10)
                ui->Txtsysinput2->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysinput2->backspace();
        }
        else if(ui->Txtsysinput3->hasFocus())
        {
            if(num<10)
                ui->Txtsysinput3->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysinput3->backspace();
        }
        else if(ui->Txtsysinput4->hasFocus())
        {
            if(num<10)
                ui->Txtsysinput4->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysinput4->backspace();
        }
        else if(ui->Txtsysinput5->hasFocus())
        {
            if(num<10)
                ui->Txtsysinput5->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysinput5->backspace();
        }
        else if(ui->Txtsysinput6->hasFocus())
        {
            if(num<10)
                ui->Txtsysinput6->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysinput6->backspace();
        }
        else if(ui->Txtsysinput7->hasFocus())
        {
            if(num<10)
                ui->Txtsysinput7->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysinput7->backspace();
        }
        else if(ui->Txtsysinput8->hasFocus())
        {
            if(num<10)
                ui->Txtsysinput8->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysinput8->backspace();
        }
        else if(ui->Txtsysinput9->hasFocus())
        {
            if(num<10)
                ui->Txtsysinput9->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysinput9->backspace();
        }
        else if(ui->Txtsysinput10->hasFocus())
        {
            if(num<10)
                ui->Txtsysinput10->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysinput10->backspace();
        }
        else if(ui->Txtsysoutput1->hasFocus())
        {
            if(num<10)
                ui->Txtsysoutput1->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysoutput1->backspace();
        }
        else if(ui->Txtsysoutput2->hasFocus())
        {
            if(num<10)
                ui->Txtsysoutput2->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysoutput2->backspace();
        }
        else if(ui->Txtsysoutput3->hasFocus())
        {
            if(num<10)
                ui->Txtsysoutput3->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysoutput3->backspace();
        }
        else if(ui->Txtsysoutput4->hasFocus())
        {
            if(num<10)
                ui->Txtsysoutput4->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysoutput4->backspace();
        }
        else if(ui->Txtsysoutput5->hasFocus())
        {
            if(num<10)
                ui->Txtsysoutput5->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysoutput5->backspace();
        }
        else if(ui->Txtsysoutput6->hasFocus())
        {
            if(num<10)
                ui->Txtsysoutput6->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysoutput6->backspace();
        }
        else if(ui->Txtsysoutput7->hasFocus())
        {
            if(num<10)
                ui->Txtsysoutput7->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysoutput7->backspace();
        }
        else if(ui->Txtsysoutput8->hasFocus())
        {
            if(num<10)
                ui->Txtsysoutput8->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysoutput8->backspace();
        }
        else if(ui->Txtsysoutput9->hasFocus())
        {
            if(num<10)
                ui->Txtsysoutput9->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysoutput9->backspace();
        }
        else if(ui->Txtsysoutput10->hasFocus())
        {
            if(num<10)
                ui->Txtsysoutput10->insert(QString::number(num));
            else if(num==10)
                ui->Txtsysoutput10->backspace();
        }
        else if(ui->Txtaverinput1->hasFocus())
        {
            if(num<10)
                ui->Txtaverinput1->insert(QString::number(num));
            else if(num==10)
                ui->Txtaverinput1->backspace();
        }
        else if(ui->Txtaverinput2->hasFocus())
        {
            if(num<10)
                ui->Txtaverinput2->insert(QString::number(num));
            else if(num==10)
                ui->Txtaverinput2->backspace();
        }
        else if(ui->Txtaverinput3->hasFocus())
        {
            if(num<10)
                ui->Txtaverinput3->insert(QString::number(num));
            else if(num==10)
                ui->Txtaverinput3->backspace();
        }
        else if(ui->Txtaverinput4->hasFocus())
        {
            if(num<10)
                ui->Txtaverinput4->insert(QString::number(num));
            else if(num==10)
                ui->Txtaverinput4->backspace();
        }
        else if(ui->Txtaverinput5->hasFocus())
        {
            if(num<10)
                ui->Txtaverinput5->insert(QString::number(num));
            else if(num==10)
                ui->Txtaverinput5->backspace();
        }
        else if(ui->Txtaverinput6->hasFocus())
        {
            if(num<10)
                ui->Txtaverinput6->insert(QString::number(num));
            else if(num==10)
                ui->Txtaverinput6->backspace();
        }
        else if(ui->Txtaverinput7->hasFocus())
        {
            if(num<10)
                ui->Txtaverinput7->insert(QString::number(num));
            else if(num==10)
                ui->Txtaverinput7->backspace();
        }
        else if(ui->Txtaverinput8->hasFocus())
        {
            if(num<10)
                ui->Txtaverinput8->insert(QString::number(num));
            else if(num==10)
                ui->Txtaverinput8->backspace();
        }
        else if(ui->Txtaverinput9->hasFocus())
        {
            if(num<10)
                ui->Txtaverinput9->insert(QString::number(num));
            else if(num==10)
                ui->Txtaverinput9->backspace();
        }
        else if(ui->Txtaverinput10->hasFocus())
        {
            if(num<10)
                ui->Txtaverinput10->insert(QString::number(num));
            else if(num==10)
                ui->Txtaverinput10->backspace();
        }
        else if(ui->Txtaveroutput1->hasFocus())
        {
            if(num<10)
                ui->Txtaveroutput1->insert(QString::number(num));
            else if(num==10)
                ui->Txtaveroutput1->backspace();
        }
        else if(ui->Txtaveroutput2->hasFocus())
        {
            if(num<10)
                ui->Txtaveroutput2->insert(QString::number(num));
            else if(num==10)
                ui->Txtaveroutput2->backspace();
        }
        else if(ui->Txtaveroutput3->hasFocus())
        {
            if(num<10)
                ui->Txtaveroutput3->insert(QString::number(num));
            else if(num==10)
                ui->Txtaveroutput3->backspace();
        }
        else if(ui->Txtaveroutput4->hasFocus())
        {
            if(num<10)
                ui->Txtaveroutput4->insert(QString::number(num));
            else if(num==10)
                ui->Txtaveroutput4->backspace();
        }
        else if(ui->Txtaveroutput5->hasFocus())
        {
            if(num<10)
                ui->Txtaveroutput5->insert(QString::number(num));
            else if(num==10)
                ui->Txtaveroutput5->backspace();
        }
        else if(ui->Txtaveroutput6->hasFocus())
        {
            if(num<10)
                ui->Txtaveroutput6->insert(QString::number(num));
            else if(num==10)
                ui->Txtaveroutput6->backspace();
        }
        else if(ui->Txtaveroutput7->hasFocus())
        {
            if(num<10)
                ui->Txtaveroutput7->insert(QString::number(num));
            else if(num==10)
                ui->Txtaveroutput7->backspace();
        }
        else if(ui->Txtaveroutput8->hasFocus())
        {
            if(num<10)
                ui->Txtaveroutput8->insert(QString::number(num));
            else if(num==10)
                ui->Txtaveroutput8->backspace();
        }
        else if(ui->Txtaveroutput9->hasFocus())
        {
            if(num<10)
                ui->Txtaveroutput9->insert(QString::number(num));
            else if(num==10)
                ui->Txtaveroutput9->backspace();
        }
        else if(ui->Txtaveroutput10->hasFocus())
        {
            if(num<10)
                ui->Txtaveroutput10->insert(QString::number(num));
            else if(num==10)
                ui->Txtaveroutput10->backspace();
        }
        else if(ui->Txtdiainput1->hasFocus())
        {
            if(num<10)
                ui->Txtdiainput1->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiainput1->backspace();
        }
        else if(ui->Txtdiainput2->hasFocus())
        {
            if(num<10)
                ui->Txtdiainput2->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiainput2->backspace();
        }
        else if(ui->Txtdiainput3->hasFocus())
        {
            if(num<10)
                ui->Txtdiainput3->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiainput3->backspace();
        }
        else if(ui->Txtdiainput4->hasFocus())
        {
            if(num<10)
                ui->Txtdiainput4->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiainput4->backspace();
        }
        else if(ui->Txtdiainput5->hasFocus())
        {
            if(num<10)
                ui->Txtdiainput5->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiainput5->backspace();
        }
        else if(ui->Txtdiainput6->hasFocus())
        {
            if(num<10)
                ui->Txtdiainput6->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiainput6->backspace();
        }
        else if(ui->Txtdiainput7->hasFocus())
        {
            if(num<10)
                ui->Txtdiainput7->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiainput7->backspace();
        }
        else if(ui->Txtdiainput8->hasFocus())
        {
            if(num<10)
                ui->Txtdiainput8->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiainput8->backspace();
        }
        else if(ui->Txtdiainput9->hasFocus())
        {
            if(num<10)
                ui->Txtdiainput9->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiainput9->backspace();
        }
        else if(ui->Txtdiainput10->hasFocus())
        {
            if(num<10)
                ui->Txtdiainput10->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiainput10->backspace();
        }
        else if(ui->Txtdiaoutput1->hasFocus())
        {
            if(num<10)
                ui->Txtdiaoutput1->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiaoutput1->backspace();
        }
        else if(ui->Txtdiaoutput2->hasFocus())
        {
            if(num<10)
                ui->Txtdiaoutput2->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiaoutput2->backspace();
        }
        else if(ui->Txtdiaoutput3->hasFocus())
        {
            if(num<10)
                ui->Txtdiaoutput3->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiaoutput3->backspace();
        }
        else if(ui->Txtdiaoutput4->hasFocus())
        {
            if(num<10)
                ui->Txtdiaoutput4->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiaoutput4->backspace();
        }
        else if(ui->Txtdiaoutput5->hasFocus())
        {
            if(num<10)
                ui->Txtdiaoutput5->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiaoutput5->backspace();
        }
        else if(ui->Txtdiaoutput6->hasFocus())
        {
            if(num<10)
                ui->Txtdiaoutput6->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiaoutput6->backspace();
        }
        else if(ui->Txtdiaoutput7->hasFocus())
        {
            if(num<10)
                ui->Txtdiaoutput7->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiaoutput7->backspace();
        }
        else if(ui->Txtdiaoutput8->hasFocus())
        {
            if(num<10)
                ui->Txtdiaoutput8->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiaoutput8->backspace();
        }
        else if(ui->Txtdiaoutput9->hasFocus())
        {
            if(num<10)
                ui->Txtdiaoutput9->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiaoutput9->backspace();
        }
        else if(ui->Txtdiaoutput10->hasFocus())
        {
            if(num<10)
                ui->Txtdiaoutput10->insert(QString::number(num));
            else if(num==10)
                ui->Txtdiaoutput10->backspace();
        }
}


void CalibrateDialog::on_btnOK_clicked()
{
    hrinput1=ui->Txthrinput1->text().toInt();
    hrinput2=ui->Txthrinput2->text().toInt();
    hrinput3=ui->Txthrinput3->text().toInt();
    hrinput4=ui->Txthrinput4->text().toInt();
    hrinput5=ui->Txthrinput5->text().toInt();
    hrinput6=ui->Txthrinput6->text().toInt();
    hrinput7=ui->Txthrinput7->text().toInt();
    hrinput8=ui->Txthrinput8->text().toInt();
    hrinput9=ui->Txthrinput9->text().toInt();
    hrinput10=ui->Txthrinput10->text().toInt();

    hroutput1=ui->Txthroutput1->text().toInt();
    hroutput2=ui->Txthroutput2->text().toInt();
    hroutput3=ui->Txthroutput3->text().toInt();
    hroutput4=ui->Txthroutput4->text().toInt();
    hroutput5=ui->Txthroutput5->text().toInt();
    hroutput6=ui->Txthroutput6->text().toInt();
    hroutput7=ui->Txthroutput7->text().toInt();
    hroutput8=ui->Txthroutput8->text().toInt();
    hroutput9=ui->Txthroutput9->text().toInt();
    hroutput10=ui->Txthroutput10->text().toInt();

    spo2input1=ui->Txtspo2input1->text().toInt();
    spo2input2=ui->Txtspo2input2->text().toInt();
    spo2input3=ui->Txtspo2input3->text().toInt();
    spo2input4=ui->Txtspo2input4->text().toInt();
    spo2input5=ui->Txtspo2input5->text().toInt();
    spo2input6=ui->Txtspo2input6->text().toInt();
    spo2input7=ui->Txtspo2input7->text().toInt();
    spo2input8=ui->Txtspo2input8->text().toInt();
    spo2input9=ui->Txtspo2input9->text().toInt();
    spo2input10=ui->Txtspo2input10->text().toInt();

    spo2output1=ui->Txtspo2output1->text().toInt();
    spo2output2=ui->Txtspo2output2->text().toInt();
    spo2output3=ui->Txtspo2output3->text().toInt();
    spo2output4=ui->Txtspo2output4->text().toInt();
    spo2output5=ui->Txtspo2output5->text().toInt();
    spo2output6=ui->Txtspo2output6->text().toInt();
    spo2output7=ui->Txtspo2output7->text().toInt();
    spo2output8=ui->Txtspo2output8->text().toInt();
    spo2output9=ui->Txtspo2output9->text().toInt();
    spo2output10=ui->Txtspo2output10->text().toInt();

    sysinput1=ui->Txtsysinput1->text().toInt();
    sysinput2=ui->Txtsysinput2->text().toInt();
    sysinput3=ui->Txtsysinput3->text().toInt();
    sysinput4=ui->Txtsysinput4->text().toInt();
    sysinput5=ui->Txtsysinput5->text().toInt();
    sysinput6=ui->Txtsysinput6->text().toInt();
    sysinput7=ui->Txtsysinput7->text().toInt();
    sysinput8=ui->Txtsysinput8->text().toInt();
    sysinput9=ui->Txtsysinput9->text().toInt();
    sysinput10=ui->Txtsysinput10->text().toInt();

    sysoutput1=ui->Txtsysoutput1->text().toInt();
    sysoutput2=ui->Txtsysoutput2->text().toInt();
    sysoutput3=ui->Txtsysoutput3->text().toInt();
    sysoutput4=ui->Txtsysoutput4->text().toInt();
    sysoutput5=ui->Txtsysoutput5->text().toInt();
    sysoutput6=ui->Txtsysoutput6->text().toInt();
    sysoutput7=ui->Txtsysoutput7->text().toInt();
    sysoutput8=ui->Txtsysoutput8->text().toInt();
    sysoutput9=ui->Txtsysoutput9->text().toInt();
    sysoutput10=ui->Txtsysoutput10->text().toInt();

    averinput1=ui->Txtaverinput1->text().toInt();
    averinput2=ui->Txtaverinput2->text().toInt();
    averinput3=ui->Txtaverinput3->text().toInt();
    averinput4=ui->Txtaverinput4->text().toInt();
    averinput5=ui->Txtaverinput5->text().toInt();
    averinput6=ui->Txtaverinput6->text().toInt();
    averinput7=ui->Txtaverinput7->text().toInt();
    averinput8=ui->Txtaverinput8->text().toInt();
    averinput9=ui->Txtaverinput9->text().toInt();
    averinput10=ui->Txtaverinput10->text().toInt();

    averoutput1=ui->Txtaveroutput1->text().toInt();
    averoutput2=ui->Txtaveroutput2->text().toInt();
    averoutput3=ui->Txtaveroutput3->text().toInt();
    averoutput4=ui->Txtaveroutput4->text().toInt();
    averoutput5=ui->Txtaveroutput5->text().toInt();
    averoutput6=ui->Txtaveroutput6->text().toInt();
    averoutput7=ui->Txtaveroutput7->text().toInt();
    averoutput8=ui->Txtaveroutput8->text().toInt();
    averoutput9=ui->Txtaveroutput9->text().toInt();
    averoutput10=ui->Txtaveroutput10->text().toInt();

    diainput1=ui->Txtdiainput1->text().toInt();
    diainput2=ui->Txtdiainput2->text().toInt();
    diainput3=ui->Txtdiainput3->text().toInt();
    diainput4=ui->Txtdiainput4->text().toInt();
    diainput5=ui->Txtdiainput5->text().toInt();
    diainput6=ui->Txtdiainput6->text().toInt();
    diainput7=ui->Txtdiainput7->text().toInt();
    diainput8=ui->Txtdiainput8->text().toInt();
    diainput9=ui->Txtdiainput9->text().toInt();
    diainput10=ui->Txtdiainput10->text().toInt();

    diaoutput1=ui->Txtdiaoutput1->text().toInt();
    diaoutput2=ui->Txtdiaoutput2->text().toInt();
    diaoutput3=ui->Txtdiaoutput3->text().toInt();
    diaoutput4=ui->Txtdiaoutput4->text().toInt();
    diaoutput5=ui->Txtdiaoutput5->text().toInt();
    diaoutput6=ui->Txtdiaoutput6->text().toInt();
    diaoutput7=ui->Txtdiaoutput7->text().toInt();
    diaoutput8=ui->Txtdiaoutput8->text().toInt();
    diaoutput9=ui->Txtdiaoutput9->text().toInt();
    diaoutput10=ui->Txtdiaoutput10->text().toInt();
    Createxml();
    this->accept();
    this->close();
}
void CalibrateDialog::Createxml()
{
    QFile db(pathdir+"/calibrate.xml");
    if(!db.exists())
    {
        db.open((QIODevice::ReadWrite|QIODevice::Text));
        db.close();
    }
    db.open(QIODevice::WriteOnly|QIODevice::Truncate);

    QDomDocument doc;
    QDomElement root=doc.createElement("calibrates");
    doc.appendChild(root);

    QDomElement ele_hrin1=doc.createElement("hrinput1");
    QDomText elementval;
    QDomAttr id;
    elementval=doc.createTextNode(QString::number(hrinput1));
    ele_hrin1.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("1");
    ele_hrin1.setAttributeNode(id);
    root.appendChild(ele_hrin1);

    QDomElement ele_hrin2=doc.createElement("hrinput2");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hrinput2));
    ele_hrin2.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("2");
    ele_hrin2.setAttributeNode(id);
    root.appendChild(ele_hrin2);

    QDomElement ele_hrin3=doc.createElement("hrinput3");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hrinput3));
    ele_hrin3.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("3");
    ele_hrin3.setAttributeNode(id);
    root.appendChild(ele_hrin3);

    QDomElement ele_hrin4=doc.createElement("hrinput4");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hrinput4));
    ele_hrin4.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("4");
    ele_hrin4.setAttributeNode(id);
    root.appendChild(ele_hrin4);

    QDomElement ele_hrin5=doc.createElement("hrinput5");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hrinput5));
    ele_hrin5.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("5");
    ele_hrin5.setAttributeNode(id);
    root.appendChild(ele_hrin5);

    QDomElement ele_hrin6=doc.createElement("hrinput6");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hrinput6));
    ele_hrin6.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("6");
    ele_hrin6.setAttributeNode(id);
    root.appendChild(ele_hrin6);

    QDomElement ele_hrin7=doc.createElement("hrinput7");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hrinput7));
    ele_hrin7.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("7");
    ele_hrin7.setAttributeNode(id);
    root.appendChild(ele_hrin7);

    QDomElement ele_hrin8=doc.createElement("hrinput8");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hrinput8));
    ele_hrin8.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("8");
    ele_hrin8.setAttributeNode(id);
    root.appendChild(ele_hrin8);

    QDomElement ele_hrin9=doc.createElement("hrinput9");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hrinput9));
    ele_hrin9.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("9");
    ele_hrin9.setAttributeNode(id);
    root.appendChild(ele_hrin9);

    QDomElement ele_hrin10=doc.createElement("hrinput10");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hrinput10));
    ele_hrin10.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("10");
    ele_hrin10.setAttributeNode(id);
    root.appendChild(ele_hrin10);

    QDomElement ele_hrout1=doc.createElement("hroutput1");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hroutput1));
    ele_hrout1.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("11");
    ele_hrout1.setAttributeNode(id);
    root.appendChild(ele_hrout1);

    QDomElement ele_hrout2=doc.createElement("hroutput2");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hroutput2));
    ele_hrout2.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("12");
    ele_hrout2.setAttributeNode(id);
    root.appendChild(ele_hrout2);

    QDomElement ele_hrout3=doc.createElement("hroutput3");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hroutput3));
    ele_hrout3.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("13");
    ele_hrout3.setAttributeNode(id);
    root.appendChild(ele_hrout3);

    QDomElement ele_hrout4=doc.createElement("hroutput4");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hroutput4));
    ele_hrout4.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("14");
    ele_hrout4.setAttributeNode(id);
    root.appendChild(ele_hrout4);

    QDomElement ele_hrout5=doc.createElement("hroutput5");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hroutput5));
    ele_hrout5.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("15");
    ele_hrout5.setAttributeNode(id);
    root.appendChild(ele_hrout5);

    QDomElement ele_hrout6=doc.createElement("hroutput6");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hroutput6));
    ele_hrout6.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("16");
    ele_hrout6.setAttributeNode(id);
    root.appendChild(ele_hrout6);

    QDomElement ele_hrout7=doc.createElement("hroutput7");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hroutput7));
    ele_hrout7.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("17");
    ele_hrout7.setAttributeNode(id);
    root.appendChild(ele_hrout7);

    QDomElement ele_hrout8=doc.createElement("hroutput8");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hroutput8));
    ele_hrout8.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("18");
    ele_hrout8.setAttributeNode(id);
    root.appendChild(ele_hrout8);

    QDomElement ele_hrout9=doc.createElement("hroutput9");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hroutput9));
    ele_hrout9.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("19");
    ele_hrout9.setAttributeNode(id);
    root.appendChild(ele_hrout9);

    QDomElement ele_hrout10=doc.createElement("hroutput10");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(hroutput10));
    ele_hrout10.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("20");
    ele_hrout10.setAttributeNode(id);
    root.appendChild(ele_hrout10);

    QDomElement ele_spo2in1=doc.createElement("spo2input1");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2input1));
    ele_spo2in1.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("21");
    ele_spo2in1.setAttributeNode(id);
    root.appendChild(ele_spo2in1);

    QDomElement ele_spo2in2=doc.createElement("spo2input2");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2input2));
    ele_spo2in2.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("22");
    ele_spo2in2.setAttributeNode(id);
    root.appendChild(ele_spo2in2);

    QDomElement ele_spo2in3=doc.createElement("spo2input3");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2input3));
    ele_spo2in3.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("23");
    ele_spo2in3.setAttributeNode(id);
    root.appendChild(ele_spo2in3);

    QDomElement ele_spo2in4=doc.createElement("spo2input4");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2input4));
    ele_spo2in4.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("24");
    ele_spo2in4.setAttributeNode(id);
    root.appendChild(ele_spo2in4);

    QDomElement ele_spo2in5=doc.createElement("spo2input5");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2input5));
    ele_spo2in5.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("25");
    ele_spo2in5.setAttributeNode(id);
    root.appendChild(ele_spo2in5);

    QDomElement ele_spo2in6=doc.createElement("spo2input6");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2input6));
    ele_spo2in6.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("26");
    ele_spo2in6.setAttributeNode(id);
    root.appendChild(ele_spo2in6);

    QDomElement ele_spo2in7=doc.createElement("spo2input7");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2input7));
    ele_spo2in7.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("27");
    ele_spo2in7.setAttributeNode(id);
    root.appendChild(ele_spo2in7);

    QDomElement ele_spo2in8=doc.createElement("spo2input8");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2input8));
    ele_spo2in8.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("28");
    ele_spo2in8.setAttributeNode(id);
    root.appendChild(ele_spo2in8);

    QDomElement ele_spo2in9=doc.createElement("spo2input9");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2input9));
    ele_spo2in9.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("29");
    ele_spo2in9.setAttributeNode(id);
    root.appendChild(ele_spo2in9);

    QDomElement ele_spo2in10=doc.createElement("spo2input10");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2input10));
    ele_spo2in10.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("30");
    ele_spo2in10.setAttributeNode(id);
    root.appendChild(ele_spo2in10);

    QDomElement ele_spo2out1=doc.createElement("spo2output1");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2output1));
    ele_spo2out1.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("31");
    ele_spo2out1.setAttributeNode(id);
    root.appendChild(ele_spo2out1);

    QDomElement ele_spo2out2=doc.createElement("spo2output2");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2output2));
    ele_spo2out2.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("32");
    ele_spo2out2.setAttributeNode(id);
    root.appendChild(ele_spo2out2);

    QDomElement ele_spo2out3=doc.createElement("spo2output3");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2output3));
    ele_spo2out3.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("33");
    ele_spo2out3.setAttributeNode(id);
    root.appendChild(ele_spo2out3);

    QDomElement ele_spo2out4=doc.createElement("spo2output4");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2output4));
    ele_spo2out4.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("34");
    ele_spo2out4.setAttributeNode(id);
    root.appendChild(ele_spo2out4);

    QDomElement ele_spo2out5=doc.createElement("spo2output5");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2output5));
    ele_spo2out5.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("35");
    ele_spo2out5.setAttributeNode(id);
    root.appendChild(ele_spo2out5);

    QDomElement ele_spo2out6=doc.createElement("spo2output6");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2output6));
    ele_spo2out6.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("36");
    ele_spo2out6.setAttributeNode(id);
    root.appendChild(ele_spo2out6);

    QDomElement ele_spo2out7=doc.createElement("spo2output7");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2output7));
    ele_spo2out7.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("37");
    ele_spo2out7.setAttributeNode(id);
    root.appendChild(ele_spo2out7);

    QDomElement ele_spo2out8=doc.createElement("spo2output8");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2output8));
    ele_spo2out8.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("38");
    ele_spo2out8.setAttributeNode(id);
    root.appendChild(ele_spo2out8);

    QDomElement ele_spo2out9=doc.createElement("spo2output9");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2output9));
    ele_spo2out9.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("39");
    ele_spo2out9.setAttributeNode(id);
    root.appendChild(ele_spo2out9);

    QDomElement ele_spo2out10=doc.createElement("spo2output10");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(spo2output10));
    ele_spo2out10.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("40");
    ele_spo2out10.setAttributeNode(id);
    root.appendChild(ele_spo2out10);

    QDomElement ele_sysin1=doc.createElement("sysinput1");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysinput1));
    ele_sysin1.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("41");
    ele_sysin1.setAttributeNode(id);
    root.appendChild(ele_sysin1);


    QDomElement ele_sysin2=doc.createElement("sysinput2");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysinput2));
    ele_sysin2.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("42");
    ele_sysin2.setAttributeNode(id);
    root.appendChild(ele_sysin2);

    QDomElement ele_sysin3=doc.createElement("sysinput2");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysinput3));
    ele_sysin3.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("43");
    ele_sysin3.setAttributeNode(id);
    root.appendChild(ele_sysin3);

    QDomElement ele_sysin4=doc.createElement("sysinput4");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysinput4));
    ele_sysin4.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("44");
    ele_sysin4.setAttributeNode(id);
    root.appendChild(ele_sysin4);

    QDomElement ele_sysin5=doc.createElement("sysinput5");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysinput5));
    ele_sysin5.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("45");
    ele_sysin5.setAttributeNode(id);
    root.appendChild(ele_sysin5);

    QDomElement ele_sysin6=doc.createElement("sysinput6");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysinput6));
    ele_sysin6.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("46");
    ele_sysin6.setAttributeNode(id);
    root.appendChild(ele_sysin6);

    QDomElement ele_sysin7=doc.createElement("sysinput7");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysinput7));
    ele_sysin7.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("47");
    ele_sysin7.setAttributeNode(id);
    root.appendChild(ele_sysin7);

    QDomElement ele_sysin8=doc.createElement("sysinput8");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysinput8));
    ele_sysin8.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("48");
    ele_sysin8.setAttributeNode(id);
    root.appendChild(ele_sysin8);

    QDomElement ele_sysin9=doc.createElement("sysinput9");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysinput9));
    ele_sysin9.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("49");
    ele_sysin9.setAttributeNode(id);
    root.appendChild(ele_sysin9);

    QDomElement ele_sysin10=doc.createElement("sysinput10");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysinput10));
    ele_sysin10.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("50");
    ele_sysin10.setAttributeNode(id);
    root.appendChild(ele_sysin10);

    QDomElement ele_sysout1=doc.createElement("sysoutput1");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysoutput1));
    ele_sysout1.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("51");
    ele_sysout1.setAttributeNode(id);
    root.appendChild(ele_sysout1);

    QDomElement ele_sysout2=doc.createElement("sysoutput2");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysoutput2));
    ele_sysout2.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("52");
    ele_sysout2.setAttributeNode(id);
    root.appendChild(ele_sysout2);

    QDomElement ele_sysout3=doc.createElement("sysoutput3");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysoutput3));
    ele_sysout3.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("53");
    ele_sysout3.setAttributeNode(id);
    root.appendChild(ele_sysout3);

    QDomElement ele_sysout4=doc.createElement("sysoutput4");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysoutput4));
    ele_sysout4.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("54");
    ele_sysout4.setAttributeNode(id);
    root.appendChild(ele_sysout4);

    QDomElement ele_sysout5=doc.createElement("sysoutput5");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysoutput5));
    ele_sysout5.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("55");
    ele_sysout5.setAttributeNode(id);
    root.appendChild(ele_sysout5);

    QDomElement ele_sysout6=doc.createElement("sysoutput6");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysoutput6));
    ele_sysout6.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("56");
    ele_sysout6.setAttributeNode(id);
    root.appendChild(ele_sysout6);

    QDomElement ele_sysout7=doc.createElement("sysoutput7");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysoutput7));
    ele_sysout7.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("57");
    ele_sysout7.setAttributeNode(id);
    root.appendChild(ele_sysout7);

    QDomElement ele_sysout8=doc.createElement("sysoutput8");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysoutput8));
    ele_sysout8.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("58");
    ele_sysout8.setAttributeNode(id);
    root.appendChild(ele_sysout8);

    QDomElement ele_sysout9=doc.createElement("sysoutput9");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysoutput9));
    ele_sysout9.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("59");
    ele_sysout9.setAttributeNode(id);
    root.appendChild(ele_sysout9);

    QDomElement ele_sysout10=doc.createElement("sysoutput10");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(sysoutput10));
    ele_sysout10.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("60");
    ele_sysout10.setAttributeNode(id);
    root.appendChild(ele_sysout10);

    QDomElement ele_averin1=doc.createElement("averinput1");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averinput1));
    ele_averin1.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("61");
    ele_averin1.setAttributeNode(id);
    root.appendChild(ele_averin1);

    QDomElement ele_averin2=doc.createElement("averinput2");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averinput2));
    ele_averin2.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("62");
    ele_averin2.setAttributeNode(id);
    root.appendChild(ele_averin2);

    QDomElement ele_averin3=doc.createElement("averinput3");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averinput3));
    ele_averin3.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("63");
    ele_averin3.setAttributeNode(id);
    root.appendChild(ele_averin3);

    QDomElement ele_averin4=doc.createElement("averinput4");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averinput4));
    ele_averin4.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("64");
    ele_averin4.setAttributeNode(id);
    root.appendChild(ele_averin4);

    QDomElement ele_averin5=doc.createElement("averinput5");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averinput5));
    ele_averin5.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("65");
    ele_averin5.setAttributeNode(id);
    root.appendChild(ele_averin5);

    QDomElement ele_averin6=doc.createElement("averinput6");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averinput6));
    ele_averin6.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("66");
    ele_averin6.setAttributeNode(id);
    root.appendChild(ele_averin6);

    QDomElement ele_averin7=doc.createElement("averinput7");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averinput7));
    ele_averin7.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("67");
    ele_averin7.setAttributeNode(id);
    root.appendChild(ele_averin7);

    QDomElement ele_averin8=doc.createElement("averinput8");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averinput8));
    ele_averin8.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("68");
    ele_averin8.setAttributeNode(id);
    root.appendChild(ele_averin8);

    QDomElement ele_averin9=doc.createElement("averinput9");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averinput9));
    ele_averin9.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("69");
    ele_averin9.setAttributeNode(id);
    root.appendChild(ele_averin9);

    QDomElement ele_averin10=doc.createElement("averinput10");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averinput10));
    ele_averin10.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("70");
    ele_averin10.setAttributeNode(id);
    root.appendChild(ele_averin10);

    QDomElement ele_averout1=doc.createElement("averoutput1");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averoutput1));
    ele_averout1.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("71");
    ele_averout1.setAttributeNode(id);
    root.appendChild(ele_averout1);

    QDomElement ele_averout2=doc.createElement("averoutput2");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averoutput2));
    ele_averout2.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("72");
    ele_averout2.setAttributeNode(id);
    root.appendChild(ele_averout2);

    QDomElement ele_averout3=doc.createElement("averoutput3");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averoutput3));
    ele_averout3.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("73");
    ele_averout3.setAttributeNode(id);
    root.appendChild(ele_averout3);

    QDomElement ele_averout4=doc.createElement("averoutput4");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averoutput4));
    ele_averout4.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("74");
    ele_averout4.setAttributeNode(id);
    root.appendChild(ele_averout4);

    QDomElement ele_averout5=doc.createElement("averoutput5");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averoutput5));
    ele_averout5.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("75");
    ele_averout5.setAttributeNode(id);
    root.appendChild(ele_averout5);

    QDomElement ele_averout6=doc.createElement("averoutput6");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averoutput6));
    ele_averout6.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("76");
    ele_averout6.setAttributeNode(id);
    root.appendChild(ele_averout6);

    QDomElement ele_averout7=doc.createElement("averoutput7");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averoutput7));
    ele_averout7.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("77");
    ele_averout7.setAttributeNode(id);
    root.appendChild(ele_averout7);

    QDomElement ele_averout8=doc.createElement("averoutput8");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averoutput8));
    ele_averout8.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("78");
    ele_averout8.setAttributeNode(id);
    root.appendChild(ele_averout8);

    QDomElement ele_averout9=doc.createElement("averoutput9");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averoutput9));
    ele_averout9.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("79");
    ele_averout9.setAttributeNode(id);
    root.appendChild(ele_averout9);

    QDomElement ele_averout10=doc.createElement("averoutput10");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(averoutput10));
    ele_averout10.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("80");
    ele_averout10.setAttributeNode(id);
    root.appendChild(ele_averout10);

    QDomElement ele_diain1=doc.createElement("diainput1");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diainput1));
    ele_diain1.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("81");
    ele_diain1.setAttributeNode(id);
    root.appendChild(ele_diain1);

    QDomElement ele_diain2=doc.createElement("diainput2");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diainput2));
    ele_diain2.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("82");
    ele_diain2.setAttributeNode(id);
    root.appendChild(ele_diain2);

    QDomElement ele_diain3=doc.createElement("diainput3");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diainput3));
    ele_diain3.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("83");
    ele_diain3.setAttributeNode(id);
    root.appendChild(ele_diain3);

    QDomElement ele_diain4=doc.createElement("diainput4");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diainput4));
    ele_diain4.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("84");
    ele_diain4.setAttributeNode(id);
    root.appendChild(ele_diain4);

    QDomElement ele_diain5=doc.createElement("diainput5");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diainput5));
    ele_diain5.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("85");
    ele_diain5.setAttributeNode(id);
    root.appendChild(ele_diain5);

    QDomElement ele_diain6=doc.createElement("diainput6");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diainput6));
    ele_diain6.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("86");
    ele_diain6.setAttributeNode(id);
    root.appendChild(ele_diain6);


    QDomElement ele_diain7=doc.createElement("diainput7");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diainput7));
    ele_diain7.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("87");
    ele_diain7.setAttributeNode(id);
    root.appendChild(ele_diain7);

    QDomElement ele_diain8=doc.createElement("diainput8");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diainput8));
    ele_diain8.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("88");
    ele_diain8.setAttributeNode(id);
    root.appendChild(ele_diain8);

    QDomElement ele_diain9=doc.createElement("diainput9");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diainput9));
    ele_diain9.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("89");
    ele_diain9.setAttributeNode(id);
    root.appendChild(ele_diain9);

    QDomElement ele_diain10=doc.createElement("diainput10");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diainput10));
    ele_diain10.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("90");
    ele_diain10.setAttributeNode(id);
    root.appendChild(ele_diain10);

    QDomElement ele_diaout1=doc.createElement("diaoutput1");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diaoutput1));
    ele_diaout1.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("91");
    ele_diaout1.setAttributeNode(id);
    root.appendChild(ele_diaout1);

    QDomElement ele_diaout2=doc.createElement("diaoutput2");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diaoutput2));
    ele_diaout2.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("92");
    ele_diaout2.setAttributeNode(id);
    root.appendChild(ele_diaout2);

    QDomElement ele_diaout3=doc.createElement("diaoutput3");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diaoutput3));
    ele_diaout3.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("93");
    ele_diaout3.setAttributeNode(id);
    root.appendChild(ele_diaout3);

    QDomElement ele_diaout4=doc.createElement("diaoutput4");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diaoutput4));
    ele_diaout4.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("94");
    ele_diaout4.setAttributeNode(id);
    root.appendChild(ele_diaout4);

    QDomElement ele_diaout5=doc.createElement("diaoutput5");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diaoutput5));
    ele_diaout5.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("95");
    ele_diaout5.setAttributeNode(id);
    root.appendChild(ele_diaout5);

    QDomElement ele_diaout6=doc.createElement("diaoutput6");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diaoutput6));
    ele_diaout6.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("96");
    ele_diaout6.setAttributeNode(id);
    root.appendChild(ele_diaout6);

    QDomElement ele_diaout7=doc.createElement("diaoutput7");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diaoutput7));
    ele_diaout7.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("97");
    ele_diaout7.setAttributeNode(id);
    root.appendChild(ele_diaout7);

    QDomElement ele_diaout8=doc.createElement("diaoutput8");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diaoutput8));
    ele_diaout8.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("98");
    ele_diaout8.setAttributeNode(id);
    root.appendChild(ele_diaout8);

    QDomElement ele_diaout9=doc.createElement("diaoutput9");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diaoutput9));
    ele_diaout9.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("99");
    ele_diaout9.setAttributeNode(id);
    root.appendChild(ele_diaout9);

    QDomElement ele_diaout10=doc.createElement("diaoutput10");
//    QDomText elementval;
    elementval=doc.createTextNode(QString::number(diaoutput10));
    ele_diaout10.appendChild(elementval);
    id=doc.createAttribute("id");
    id.setValue("100");
    ele_diaout10.setAttributeNode(id);
    root.appendChild(ele_diaout10);


    QTextStream out(&db);
    out.setCodec("UTF-8");
    doc.save(out,4);
    db.close();
}

void CalibrateDialog::Readxml()
{
    QFile file(pathdir+"/calibrate.xml");
    if(!file.exists())
        return;
    file.open(QIODevice::ReadOnly|QFile::Text);

    QDomDocument doc;
    QString element;
    QString value;
    int id;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    QDomElement docElem=doc.documentElement();
    QDomNode node=docElem.firstChild();
    while(!node.isNull())
    {
        if(node.isElement())
        {
            element=node.nodeName();
            value=node.toElement().text();
            id=node.toElement().attribute("id").toInt();
            switch(id)
            {
            case 1:
                hrinput1=value.toInt();
                break;
            case 2:
                hrinput2=value.toInt();
                break;
            case 3:
                hrinput3=value.toInt();
                break;
            case 4:
                hrinput4=value.toInt();
                break;
            case 5:
                hrinput5=value.toInt();
                break;
            case 6:
                hrinput6=value.toInt();
                break;
            case 7:
                hrinput7=value.toInt();
                break;
            case 8:
                hrinput8=value.toInt();
                break;
            case 9:
                hrinput9=value.toInt();
                break;
            case 10:
                hrinput10=value.toInt();
                break;
            case 11:
                hroutput1=value.toInt();
                break;
            case 12:
                hroutput2=value.toInt();
                break;
            case 13:
                hroutput3=value.toInt();
                break;
            case 14:
                hroutput4=value.toInt();
                break;
            case 15:
                hroutput5=value.toInt();
                break;
            case 16:
                hroutput6=value.toInt();
                break;
            case 17:
                hroutput7=value.toInt();
                break;
            case 18:
                hroutput8=value.toInt();
                break;
            case 19:
                hroutput9=value.toInt();
                break;
            case 20:
                hroutput10=value.toInt();
                break;
            case 21:
                spo2input1=value.toInt();
                break;
            case 22:
                spo2input2=value.toInt();
                break;
            case 23:
                spo2input3=value.toInt();
                break;
            case 24:
                spo2input4=value.toInt();
                break;
            case 25:
                spo2input5=value.toInt();
                break;
            case 26:
                spo2input6=value.toInt();
                break;
            case 27:
                spo2input7=value.toInt();
                break;
            case 28:
                spo2input8=value.toInt();
                break;
            case 29:
                spo2input9=value.toInt();
                break;
            case 30:
                spo2input10=value.toInt();
                break;
            case 31:
                spo2output1=value.toInt();
                break;
            case 32:
                spo2output2=value.toInt();
                break;
            case 33:
                spo2output3=value.toInt();
                break;
            case 34:
                spo2output4=value.toInt();
                break;
            case 35:
                spo2output5=value.toInt();
                break;
            case 36:
                spo2output6=value.toInt();
                break;
            case 37:
                spo2output7=value.toInt();
                break;
            case 38:
                spo2output8=value.toInt();
                break;
            case 39:
                spo2output9=value.toInt();
                break;
            case 40:
                spo2output10=value.toInt();
                break;
            case 41:
                sysinput1=value.toInt();
                break;
            case 42:
                sysinput2=value.toInt();
                break;
            case 43:
                sysinput3=value.toInt();
                break;
            case 44:
                sysinput4=value.toInt();
                break;
            case 45:
                sysinput5=value.toInt();
                break;
            case 46:
                sysinput6=value.toInt();
                break;
            case 47:
                sysinput7=value.toInt();
                break;
            case 48:
                sysinput8=value.toInt();
                break;
            case 49:
                sysinput9=value.toInt();
                break;
            case 50:
                sysinput10=value.toInt();
                break;
            case 51:
                sysoutput1=value.toInt();
                break;
            case 52:
                sysoutput2=value.toInt();
                break;
            case 53:
                sysoutput3=value.toInt();
                break;
            case 54:
                sysoutput4=value.toInt();
                break;
            case 55:
                sysoutput5=value.toInt();
                break;
            case 56:
                sysoutput6=value.toInt();
                break;
            case 57:
                sysoutput7=value.toInt();
                break;
            case 58:
                sysoutput8=value.toInt();
                break;
            case 59:
                sysoutput9=value.toInt();
                break;
            case 60:
                sysoutput10=value.toInt();
                break;
            case 61:
                averinput1=value.toInt();
                break;
            case 62:
                averinput2=value.toInt();
                break;
            case 63:
                averinput3=value.toInt();
                break;
            case 64:
                averinput4=value.toInt();
                break;
            case 65:
                averinput5=value.toInt();
                break;
            case 66:
                averinput6=value.toInt();
                break;
            case 67:
                averinput7=value.toInt();
                break;
            case 68:
                averinput8=value.toInt();
                break;
            case 69:
                averinput9=value.toInt();
                break;
            case 70:
                averinput10=value.toInt();
                break;
            case 71:
                averoutput1=value.toInt();
                break;
            case 72:
                averoutput2=value.toInt();
                break;
            case 73:
                averoutput3=value.toInt();
                break;
            case 74:
                averoutput4=value.toInt();
                break;
            case 75:
                averoutput5=value.toInt();
                break;
            case 76:
                averoutput6=value.toInt();
                break;
            case 77:
                averoutput7=value.toInt();
                break;
            case 78:
                averoutput8=value.toInt();
                break;
            case 79:
                averoutput9=value.toInt();
                break;
            case 80:
                averoutput10=value.toInt();
                break;
            case 81:
                diainput1=value.toInt();
                break;
            case 82:
                diainput2=value.toInt();
                break;
            case 83:
                diainput3=value.toInt();
                break;
            case 84:
                diainput4=value.toInt();
                break;
            case 85:
                diainput5=value.toInt();
                break;
            case 86:
                diainput6=value.toInt();
                break;
            case 87:
                diainput7=value.toInt();
                break;
            case 88:
                diainput8=value.toInt();
                break;
            case 89:
                diainput9=value.toInt();
                break;
            case 90:
                diainput10=value.toInt();
                break;
            case 91:
                diaoutput1=value.toInt();
                break;
            case 92:
                diaoutput2=value.toInt();
                break;
            case 93:
                diaoutput3=value.toInt();
                break;
            case 94:
                diaoutput4=value.toInt();
                break;
            case 95:
                diaoutput5=value.toInt();
                break;
            case 96:
                diaoutput6=value.toInt();
                break;
            case 97:
                diaoutput7=value.toInt();
                break;
            case 98:
                diaoutput8=value.toInt();
                break;
            case 99:
                diaoutput9=value.toInt();
                break;
            case 100:
                diaoutput10=value.toInt();
                break;
            }
        }
        node=node.nextSibling();
    }


    ui->Txthrinput1->setText(QString::number(hrinput1));
    ui->Txthrinput2->setText(QString::number(hrinput2));
    ui->Txthrinput3->setText(QString::number(hrinput3));
    ui->Txthrinput4->setText(QString::number(hrinput4));
    ui->Txthrinput5->setText(QString::number(hrinput5));
    ui->Txthrinput6->setText(QString::number(hrinput6));
    ui->Txthrinput7->setText(QString::number(hrinput7));
    ui->Txthrinput8->setText(QString::number(hrinput8));
    ui->Txthrinput9->setText(QString::number(hrinput9));
    ui->Txthrinput10->setText(QString::number(hrinput10));

    ui->Txthroutput1->setText(QString::number(hroutput1));
    ui->Txthroutput2->setText(QString::number(hroutput2));
    ui->Txthroutput3->setText(QString::number(hroutput3));
    ui->Txthroutput4->setText(QString::number(hroutput4));
    ui->Txthroutput5->setText(QString::number(hroutput5));
    ui->Txthroutput6->setText(QString::number(hroutput6));
    ui->Txthroutput7->setText(QString::number(hroutput7));
    ui->Txthroutput8->setText(QString::number(hroutput8));
    ui->Txthroutput9->setText(QString::number(hroutput9));
    ui->Txthroutput10->setText(QString::number(hroutput10));


    ui->Txtspo2input1->setText(QString::number(spo2input1));
    ui->Txtspo2input2->setText(QString::number(spo2input2));
    ui->Txtspo2input3->setText(QString::number(spo2input3));
    ui->Txtspo2input4->setText(QString::number(spo2input4));
    ui->Txtspo2input5->setText(QString::number(spo2input5));
    ui->Txtspo2input6->setText(QString::number(spo2input6));
    ui->Txtspo2input7->setText(QString::number(spo2input7));
    ui->Txtspo2input8->setText(QString::number(spo2input8));
    ui->Txtspo2input9->setText(QString::number(spo2input9));
    ui->Txtspo2input10->setText(QString::number(spo2input10));

    ui->Txtspo2output1->setText(QString::number(spo2output1));
    ui->Txtspo2output2->setText(QString::number(spo2output2));
    ui->Txtspo2output3->setText(QString::number(spo2output3));
    ui->Txtspo2output4->setText(QString::number(spo2output4));
    ui->Txtspo2output5->setText(QString::number(spo2output5));
    ui->Txtspo2output6->setText(QString::number(spo2output6));
    ui->Txtspo2output7->setText(QString::number(spo2output7));
    ui->Txtspo2output8->setText(QString::number(spo2output8));
    ui->Txtspo2output9->setText(QString::number(spo2output9));
    ui->Txtspo2output10->setText(QString::number(spo2output10));

    ui->Txtsysinput1->setText(QString::number(sysinput1));
    ui->Txtsysinput2->setText(QString::number(sysinput2));
    ui->Txtsysinput3->setText(QString::number(sysinput3));
    ui->Txtsysinput4->setText(QString::number(sysinput4));
    ui->Txtsysinput5->setText(QString::number(sysinput5));
    ui->Txtsysinput6->setText(QString::number(sysinput6));
    ui->Txtsysinput7->setText(QString::number(sysinput7));
    ui->Txtsysinput8->setText(QString::number(sysinput8));
    ui->Txtsysinput9->setText(QString::number(sysinput9));
    ui->Txtsysinput10->setText(QString::number(sysinput10));

    ui->Txtsysoutput1->setText(QString::number(sysoutput1));
    ui->Txtsysoutput2->setText(QString::number(sysoutput2));
    ui->Txtsysoutput3->setText(QString::number(sysoutput3));
    ui->Txtsysoutput4->setText(QString::number(sysoutput4));
    ui->Txtsysoutput5->setText(QString::number(sysoutput5));
    ui->Txtsysoutput6->setText(QString::number(sysoutput6));
    ui->Txtsysoutput7->setText(QString::number(sysoutput7));
    ui->Txtsysoutput8->setText(QString::number(sysoutput8));
    ui->Txtsysoutput9->setText(QString::number(sysoutput9));
    ui->Txtsysoutput10->setText(QString::number(sysoutput10));

    ui->Txtaverinput1->setText(QString::number(averinput1));
    ui->Txtaverinput2->setText(QString::number(averinput2));
    ui->Txtaverinput3->setText(QString::number(averinput3));
    ui->Txtaverinput4->setText(QString::number(averinput4));
    ui->Txtaverinput5->setText(QString::number(averinput5));
    ui->Txtaverinput6->setText(QString::number(averinput6));
    ui->Txtaverinput7->setText(QString::number(averinput7));
    ui->Txtaverinput8->setText(QString::number(averinput8));
    ui->Txtaverinput9->setText(QString::number(averinput9));
    ui->Txtaverinput10->setText(QString::number(averinput10));

    ui->Txtaveroutput1->setText(QString::number(averoutput1));
    ui->Txtaveroutput2->setText(QString::number(averoutput2));
    ui->Txtaveroutput3->setText(QString::number(averoutput3));
    ui->Txtaveroutput4->setText(QString::number(averoutput4));
    ui->Txtaveroutput5->setText(QString::number(averoutput5));
    ui->Txtaveroutput6->setText(QString::number(averoutput6));
    ui->Txtaveroutput7->setText(QString::number(averoutput7));
    ui->Txtaveroutput8->setText(QString::number(averoutput8));
    ui->Txtaveroutput9->setText(QString::number(averoutput9));
    ui->Txtaveroutput10->setText(QString::number(averoutput10));

    ui->Txtdiainput1->setText(QString::number(diainput1));
    ui->Txtdiainput2->setText(QString::number(diainput2));
    ui->Txtdiainput3->setText(QString::number(diainput3));
    ui->Txtdiainput4->setText(QString::number(diainput4));
    ui->Txtdiainput5->setText(QString::number(diainput5));
    ui->Txtdiainput6->setText(QString::number(diainput6));
    ui->Txtdiainput7->setText(QString::number(diainput7));
    ui->Txtdiainput8->setText(QString::number(diainput8));
    ui->Txtdiainput9->setText(QString::number(diainput9));
    ui->Txtdiainput10->setText(QString::number(diainput10));

    ui->Txtdiaoutput1->setText(QString::number(diaoutput1));
    ui->Txtdiaoutput2->setText(QString::number(diaoutput2));
    ui->Txtdiaoutput3->setText(QString::number(diaoutput3));
    ui->Txtdiaoutput4->setText(QString::number(diaoutput4));
    ui->Txtdiaoutput5->setText(QString::number(diaoutput5));
    ui->Txtdiaoutput6->setText(QString::number(diaoutput6));
    ui->Txtdiaoutput7->setText(QString::number(diaoutput7));
    ui->Txtdiaoutput8->setText(QString::number(diaoutput8));
    ui->Txtdiaoutput9->setText(QString::number(diaoutput9));
    ui->Txtdiaoutput10->setText(QString::number(diaoutput10));
    file.close();

}

void CalibrateDialog::loadlanguexml(bool IsChinese)
{
    if(IsChinese)
    {
        ui->btnOK->setText(QString::fromUtf8("确认"));
        ui->btn_Cancel->setText(QString::fromUtf8("取消"));
        ui->btnDelete->setText(QString::fromUtf8("删除"));
        this->setWindowTitle(QString::fromUtf8("校准"));
        ui->gphr->setTitle(QString::fromUtf8("脉率校准值"));
        ui->gpspo2->setTitle(QString::fromUtf8("血氧校准值"));
        ui->gpsys->setTitle(QString::fromUtf8("收缩压校准值"));
        ui->gpaver->setTitle(QString::fromUtf8("平均压校准值"));
        ui->gpdia->setTitle(QString::fromUtf8("舒张压校准值"));
        ui->lab_hrtop->setText(QString::fromUtf8("输入"));
        ui->lab_hrtop_11->setText(QString::fromUtf8("输入"));
        ui->lab_hrtop_21->setText(QString::fromUtf8("输入"));
        ui->lab_hrtop_31->setText(QString::fromUtf8("输入"));
        ui->lab_hrtop_41->setText(QString::fromUtf8("输入"));
        ui->lab_hrlow->setText(QString::fromUtf8("输出"));
        ui->lab_hrlow_11->setText(QString::fromUtf8("输出"));
        ui->lab_hrlow_21->setText(QString::fromUtf8("输出"));
        ui->lab_hrlow_31->setText(QString::fromUtf8("输出"));
        ui->lab_hrlow_41->setText(QString::fromUtf8("输出"));
    }
    else
    {
        ui->btnOK->setText("OK");
        ui->btn_Cancel->setText("Cancel");
        ui->btnDelete->setText("DEL");
        this->setWindowTitle("Calibration");
        ui->gphr->setTitle("PR Calibrate");
        ui->gpspo2->setTitle("SPO2 Calibrate");
        ui->gpsys->setTitle("SBP Calibrate");
        ui->gpaver->setTitle("MAP Calibrate");
        ui->gpdia->setTitle("DBP Calibrate");
        ui->lab_hrtop->setText("Input");
        ui->lab_hrtop_11->setText("Input");
        ui->lab_hrtop_21->setText("Input");
        ui->lab_hrtop_31->setText("Input");
        ui->lab_hrtop_41->setText("Input");
        ui->lab_hrlow->setText("Output");
        ui->lab_hrlow_11->setText("Output");
        ui->lab_hrlow_21->setText("Output");
        ui->lab_hrlow_31->setText("Output");
        ui->lab_hrlow_41->setText("Output");
    }
}

bool CalibrateDialog::close() {
    //TODO 退出手动模式
    emit openValve();
//    timer->stop();
    if(lastSelected){
        lastSelected->clearFocus();
        lastSelected->setStyleSheet("background-color:rgb(255,255,255)");
    }
    lastSelected = NULL;
    qDebug() << "发送命令，打开阀门";
    return QWidget::close();
}

void CalibrateDialog::updateData(int data) {
    calData = data;
    if(!timer->isActive()){
        timer->start(200);
    }
}
/**
 * 定时器定时更新数据，利用focuseWidget(需要判断是否为需要的)，得到对象的名字。利用QHash，得到与之对应的objectName, 在findChild。
 *
 */

void CalibrateDialog::initHashTable() {
    for(int i = 0; i < 10; i++){
        hash[output[i]->objectName()] = input[i]->objectName();
    }
}

void CalibrateDialog::initLineEdit() {
    input[0] = ui->Txtsysinput1;
    input[1] = ui->Txtsysinput2;
    input[2] = ui->Txtsysinput3;
    input[3] = ui->Txtsysinput4;
    input[4] = ui->Txtsysinput5;
    input[5] = ui->Txtsysinput6;
    input[6] = ui->Txtsysinput7;
    input[7] = ui->Txtsysinput8;
    input[8] = ui->Txtsysinput9;
    input[9] = ui->Txtsysinput10;

    output[0] = ui->Txtsysoutput1;
    output[1] = ui->Txtsysoutput2;
    output[2] = ui->Txtsysoutput3;
    output[3] = ui->Txtsysoutput4;
    output[4] = ui->Txtsysoutput5;
    output[5] = ui->Txtsysoutput6;
    output[6] = ui->Txtsysoutput7;
    output[7] = ui->Txtsysoutput8;
    output[8] = ui->Txtsysoutput9;
    output[9] = ui->Txtsysoutput10;
}

void CalibrateDialog::updateInput() {
    if(ui->gpsys->focusWidget() == NULL)
        return;
    // 如果被选中的控件不是需要的，则返回
    if(!hash.contains(ui->gpsys->focusWidget()->objectName())){
        return;
    }

    QLineEdit* outputEdit = (QLineEdit*)ui->gpsys->focusWidget();
    qDebug() << outputEdit->objectName() << " 被选中";
    outputEdit->setStyleSheet("background-color:rgb(0,255,0)");
    if(!lastSelected)
        lastSelected = outputEdit;
    else{
        if(lastSelected != outputEdit){
            lastSelected->setStyleSheet("background-color:rgb(255,255,255)");
            lastSelected = outputEdit;
        }
    }


    QLineEdit* inputEdit = ui->gpsys->findChild<QLineEdit *>(hash.value(outputEdit->objectName()));
    qDebug() << inputEdit->objectName() << " 为对应值";
    inputEdit->setText(QString::number(calData,10));

}

void CalibrateDialog::updateUI() {
    Readxml();
}