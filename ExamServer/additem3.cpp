#include "additem3.h"

#include <QMessageBox>

#include "ui_additem3.h"
AddItem3::AddItem3(QWidget* parent) : QDialog(parent), ui(new Ui::AddItem3) { ui->setupUi(this); }

AddItem3::~AddItem3() { delete ui; }
void AddItem3::bind(ShortAnswer* t) { exmple = t; }

void AddItem3::on_pushButton_ensure_clicked() {
    exmple->title = ui->textEdit->toPlainText();
    exmple->answer = ui->lineEdit->text();
    if (exmple->title.isEmpty()) {
        QMessageBox::information(this, tr("请填写完整"), QString("请填写完整"), QMessageBox::Ok);
    } else {
        QMessageBox::information(this, tr("题目添加成功"), QString("题目添加成功"), QMessageBox::Ok);
        exmple = nullptr;
        QDialog::accept();
    }
}

void AddItem3::on_pushButton_cancel_clicked() { QDialog::reject(); }
