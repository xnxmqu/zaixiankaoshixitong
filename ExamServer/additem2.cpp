#include "additem2.h"

#include <QMessageBox>

#include "ui_additem2.h"
AddItem2::AddItem2(QWidget* parent) : QDialog(parent), ui(new Ui::AddItem2) {
    ui->setupUi(this);
    lineList.append(ui->lineEdit);
}

AddItem2::~AddItem2() { delete ui; }
void AddItem2::bind(FullBlank* t) { exmple = t; }

void AddItem2::on_pushButton_clicked() {
    QLineEdit* line = new QLineEdit;
    (ui->verticalLayout)->addWidget(line);
    lineList.append(line);
}

void AddItem2::on_pushButton_2_clicked() {
    exmple->title = ui->textEdit->toPlainText();
    exmple->num = lineList.count();
    bool isempty = false;
    foreach (auto item, lineList) {
        exmple->answer.append(item->text());
        if (item->text().isEmpty())
            isempty = true;
    }
    if (isempty || exmple->title.isEmpty()) {
        QMessageBox::information(this, tr("请填写完整"), QString("请填写完整"), QMessageBox::Ok);
    } else {
        QMessageBox::information(this, tr("题目添加成功"), QString("题目添加成功"), QMessageBox::Ok);
        exmple = nullptr;
        QDialog::accept();
    }
}

void AddItem2::on_pushButton_3_clicked() { QDialog::reject(); }
