#include "additem1.h"

#include <QDebug>
#include <QMessageBox>

#include "ui_additem1.h"

AddItem1::AddItem1(QWidget* parent) : QDialog(parent), ui(new Ui::AddItem1) { ui->setupUi(this); }

AddItem1::~AddItem1() { delete ui; }
void AddItem1::bind(ChoiceQues* t) { exmple = t; }

void AddItem1::on_pushButton_clicked() {
    exmple->title = ui->textEdit->toPlainText();
    exmple->a = ui->lineEdit->text();
    exmple->b = ui->lineEdit_2->text();
    exmple->c = ui->lineEdit_3->text();
    exmple->d = ui->lineEdit_4->text();

    if (ui->radio1->isChecked())
        exmple->answer = "A";
    if (ui->radio2->isChecked())
        exmple->answer = "B";
    if (ui->radio3->isChecked())
        exmple->answer = "C";
    if (ui->radio4->isChecked())
        exmple->answer = "D";
    if (exmple->a.isEmpty() || exmple->b.isEmpty() || exmple->c.isEmpty() || exmple->d.isEmpty() ||
        exmple->title.isEmpty()) {
        QMessageBox::information(this, tr("请填写完整"), QString("请填写完整"), QMessageBox::Ok);
    } else {
        QMessageBox::information(this, tr("题目添加成功"), QString("题目添加成功"), QMessageBox::Ok);
        exmple = nullptr;
        QDialog::accept();
    }
}

void AddItem1::on_pushButton_2_clicked() { QDialog::reject(); }
