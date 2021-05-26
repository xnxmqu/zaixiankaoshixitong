#ifndef THREEQUES_H
#define THREEQUES_H
#include <QApplication>
//选择题的类
class ChoiceQues {
  public:
    QString title;
    QString a;
    QString b;
    QString c;
    QString d;
    QString answer;
};

class FullBlank {
  public:
    QString title;
    int num = 0;
    QStringList answer;
};

class ShortAnswer {
  public:
    QString title;
    QString answer;
};

class TotalQues {
  public:
    QList<ChoiceQues> choiceQuesList;
    QList<FullBlank> fullBlankList;
    QList<ShortAnswer> shortAnswerList;
};
void contentToJson();
void fileToJson(TotalQues& total, QString name);
void jsonToFile(TotalQues& T, QString name);
// void fileToJson_2(TotalQues& total, QString& name);
#endif  // THREEQUES_H
