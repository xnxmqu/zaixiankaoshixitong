#include "widget2.h"

#include "ui_widget2.h"

Widget2::Widget2(QWidget* parent) : QWidget(parent), ui(new Ui::Widget2) {
    ui->setupUi(this);
    list.append(ui->lineEdit_answer);
}

Widget2::~Widget2() { delete ui; }

void Widget2::setContent(FullBlank t) {
    ui->textEdit_questionn->setText(t.title);
    int num = t.num;
    //    ui->lineEdit_answer->setText(t.answer.at(0));
    int i = 1;
    while (num > 1) {
        QLineEdit* line = new QLineEdit;
        (ui->verticalLayout)->addWidget(line);
        //        line->setText(t.answer.at(i++));
        num--;
    }
}

QStringList Widget2::getAnswer() const {
    QStringList ls;
    for (auto elem : list) {
        ls.append(elem->text().simplified());
    }
    return ls;
}
