#ifndef DISPLAYPAPER_H
#define DISPLAYPAPER_H

#include <QWidget>

#include "threeques.h"
#include "widget1.h"
#include "widget2.h"
#include "widget3.h"

namespace Ui {
class DisplayPaper;
}

class DisplayPaper : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayPaper(QWidget *parent = 0);
    ~DisplayPaper();

    void addChoiceQues(ChoiceQues t);
    void addFullBlank(FullBlank t);
    void addShortAnswer(ShortAnswer t);

    void totop();
    void clear();

    QList<Widget1*> choiceList;
    QList<Widget2*> fullList;
    QList<Widget3*> shortList;
private:
    Ui::DisplayPaper *ui;
};

#endif // DISPLAYPAPER_H
