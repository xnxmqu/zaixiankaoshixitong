#ifndef WIDGET1_H
#define WIDGET1_H

#include <QWidget>
#include "threeques.h"
namespace Ui {
class Widget1;
}

class Widget1 : public QWidget
{
    Q_OBJECT

public:
    explicit Widget1(QWidget *parent = 0);
    ~Widget1();
    void setcontent(ChoiceQues t);
    void setChoiceQues();
    QString getAnswer();
//    void settip(QString str);

private:
    Ui::Widget1 *ui;
};

#endif // WIDGET1_H
