#include "widget3.h"
#include "ui_widget3.h"

Widget3::Widget3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget3)
{
    ui->setupUi(this);
}

Widget3::~Widget3()
{
    delete ui;
}
void Widget3::setContent(ShortAnswer t){
    ui->textEdit_question->setText(t.title);
    ui->lineEdit_answer->setText(t.answer);
}

QString Widget3::getAnswer(){
    return ui->lineEdit_answer->text();
}
