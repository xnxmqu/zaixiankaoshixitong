#include "widget1.h"

#include <QDebug>

#include "ui_widget1.h"

Widget1::Widget1(QWidget* parent) : QWidget(parent), ui(new Ui::Widget1) { ui->setupUi(this); }

Widget1::~Widget1() { delete ui; }
void Widget1::setcontent(ChoiceQues t) {
    //把ChoiceQues对象的title显示，即显示问题
    ui->textEdit_question->setText(t.title);

    //显示a、b、c、d项的内容
    ui->radioButton_a->setText(QString("A.%1").arg(t.a));
    ui->radioButton_b->setText(QString("B.%1").arg(t.b));
    ui->radioButton_c->setText(QString("C.%1").arg(t.c));
    ui->radioButton_d->setText(QString("D.%1").arg(t.d));
    qDebug() << "执行到widget1.cpp的24h";
    if (t.answer == "A")
        ui->radioButton_a->setChecked(true);
    if (t.answer == "B")
        ui->radioButton_b->setChecked(true);
    if (t.answer == "C")
        ui->radioButton_c->setChecked(true);
    if (t.answer == "D")
        ui->radioButton_d->setChecked(true);
}

QString Widget1::getAnswer() {
    if (ui->radioButton_a->isChecked())
        return "A";
    if (ui->radioButton_b->isChecked())
        return "B";
    if (ui->radioButton_c->isChecked())
        return "C";
    if (ui->radioButton_d->isChecked())
        return "D";
}
