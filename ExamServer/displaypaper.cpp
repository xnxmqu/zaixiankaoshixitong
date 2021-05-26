#include "displaypaper.h"

#include <QDebug>

#include "ui_displaypaper.h"
DisplayPaper::DisplayPaper(QWidget* parent) : QWidget(parent), ui(new Ui::DisplayPaper) { ui->setupUi(this); }

DisplayPaper::~DisplayPaper() { delete ui; }

void DisplayPaper::addChoiceQues(ChoiceQues t) {
    Widget1* d = new Widget1;
    choiceList.append(d);
    d->setcontent(t);
    ui->layout_2->addWidget(d);
    qDebug() << "解析一次选择题UI";
}
void DisplayPaper::addFullBlank(FullBlank t) {
    Widget2* d = new Widget2;
    fullList.append(d);
    d->setContent(t);
    ui->layout_2->addWidget(d);
    qDebug() << "解析一次填空题UI";
}

void DisplayPaper::addShortAnswer(ShortAnswer t) {
    Widget3* d = new Widget3;
    shortList.append(d);
    d->setContent(t);
    ui->layout_2->addWidget(d);
    qDebug() << "解析一次简答题UI";
}

void DisplayPaper::totop() {
    ui->scrollArea->scroll(0, -200);
    ui->layout_2->setEnabled(false);
}

void DisplayPaper::clear() {
    for (auto elem : choiceList)
        delete elem;
    for (auto elem : fullList)
        delete elem;
    for (auto elem : shortList)
        delete elem;
    choiceList.clear();
    fullList.clear();
    shortList.clear();
}
