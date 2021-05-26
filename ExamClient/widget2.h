#ifndef WIDGET2_H
#define WIDGET2_H

#include <threeques.h>

#include <QLineEdit>
#include <QWidget>
namespace Ui {
    class Widget2;
}

class Widget2 : public QWidget {
    Q_OBJECT

  public:
    explicit Widget2(QWidget* parent = 0);
    ~Widget2();

    void setContent(FullBlank t);
    QStringList getAnswer() const;

  private:
    Ui::Widget2* ui;

    //填空题空有多个时，使用
    QList<QLineEdit*> list;
};

#endif  // WIDGET2_H
