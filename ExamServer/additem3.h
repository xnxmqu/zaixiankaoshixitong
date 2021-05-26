#ifndef ADDITEM3_H
#define ADDITEM3_H

#include <QDialog>

#include "threeques.h"
namespace Ui {
    class AddItem3;
}

class AddItem3 : public QDialog {
    Q_OBJECT

  public:
    explicit AddItem3(QWidget* parent = 0);
    ~AddItem3();

    void bind(ShortAnswer* d);
  private slots:
    void on_pushButton_ensure_clicked();

    void on_pushButton_cancel_clicked();

  private:
    Ui::AddItem3* ui;
    ShortAnswer* exmple;
};

#endif  // ADDITEM3_H
