#ifndef PROMPTFORM_H
#define PROMPTFORM_H

#include <QWidget>

namespace Ui {
class PromptForm;
}

class PromptForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit PromptForm(QWidget *parent = 0);
    ~PromptForm();
    
private slots:
    void on_btnOK_clicked();

private:
    Ui::PromptForm *ui;
};

#endif // PROMPTFORM_H
