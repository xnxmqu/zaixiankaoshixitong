#ifndef WIDGET3_H
#define WIDGET3_H

#include <QWidget>

#include "threeques.h"
namespace Ui {
    class Widget3;
}

class Widget3 : public QWidget {
    Q_OBJECT

  public:
    explicit Widget3(QWidget* parent = 0);
    ~Widget3();
    void setContent(ShortAnswer t);
    QString getAnswer() const;

  private:
    Ui::Widget3* ui;
};

#endif  // WIDGET3_H
