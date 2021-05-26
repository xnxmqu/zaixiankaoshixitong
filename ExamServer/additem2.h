#ifndef ADDITEM2_H
#define ADDITEM2_H

#include <QDialog>
#include <QLineEdit>

#include "threeques.h"
namespace Ui {
    class AddItem2;
}

class AddItem2 : public QDialog {
    Q_OBJECT

  public:
    explicit AddItem2(QWidget* parent = 0);
    ~AddItem2();

    void bind(FullBlank* d);

  private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

  private:
    Ui::AddItem2* ui;
    QList<QLineEdit*> lineList;
    FullBlank* exmple;
};

#endif  // ADDITEM2_H
