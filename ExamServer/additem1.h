#ifndef ADDITEM1_H
#define ADDITEM1_H

#include <QDialog>

#include "threeques.h"
namespace Ui {
    class AddItem1;
}

class AddItem1 : public QDialog {
    Q_OBJECT

  public:
    explicit AddItem1(QWidget* parent = 0);
    ~AddItem1();

    void bind(ChoiceQues* d);

  private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

  private:
    Ui::AddItem1* ui;
    ChoiceQues* exmple;
};

#endif  // ADDITEM1_H
