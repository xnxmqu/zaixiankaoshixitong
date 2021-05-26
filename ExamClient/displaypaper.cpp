#include "displaypaper.h"

#include <QDebug>

#include "ui_displaypaper.h"

DisplayPaper::DisplayPaper(QWidget* parent) : QWidget(parent), ui(new Ui::DisplayPaper) { ui->setupUi(this); }

DisplayPaper::~DisplayPaper() { delete ui; }

void DisplayPaper::addChoiceQues(ChoiceQues t) {
    qDebug() << "要创建widget1对象";
    Widget1* d = new Widget1;
    qDebug() << "创建完对象";
    choiceListUI.append(d);
    qDebug() << "向choicelist添加完对象";
    d->setcontent(t);
    qDebug() << "添加UI_1开始";
    ui->layout_paper->addWidget(d);
    qDebug() << "添加UI_1完成";
}
void DisplayPaper::addFullBlank(FullBlank t) {
    Widget2* d = new Widget2;
    qDebug() << "创建完对象2";
    fullListUI.append(d);
    qDebug() << "向choicelist添加完对象";
    d->setContent(t);
    ui->layout_paper->addWidget(d);
    qDebug() << "添加UI——2完成";
}

void DisplayPaper::addShortAnswer(ShortAnswer t) {
    Widget3* d = new Widget3;
    shortListUI.append(d);
    d->setContent(t);
    ui->layout_paper->addWidget(d);
}

void DisplayPaper::totop() {
    ui->scrollArea->scroll(0, -200);
    ui->layout_paper->setEnabled(false);
}

void DisplayPaper::clear() {
    for (auto elem : choiceListUI)
        delete elem;
    for (auto elem : fullListUI)
        delete elem;
    for (auto elem : shortListUI)
        delete elem;
    choiceListUI.clear();
    fullListUI.clear();
    shortListUI.clear();
}
