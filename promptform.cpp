#include "promptform.h"
#include "ui_promptform.h"

PromptForm::PromptForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PromptForm)
{
    ui->setupUi(this);
}

PromptForm::~PromptForm()
{
    delete ui;
}
