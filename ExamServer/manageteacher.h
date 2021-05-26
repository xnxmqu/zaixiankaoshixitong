#ifndef MANAGETEACHER_H
#define MANAGETEACHER_H

#include <QButtonGroup>
#include <QSqlTableModel>
#include <QWidget>
namespace Ui {
    class ManageTeacher;
}

class ManageTeacher : public QWidget {
    Q_OBJECT

  public:
    explicit ManageTeacher(QWidget* parent = 0);
    ~ManageTeacher();

  signals:

  private slots:
    void on_btn_add_clicked();

    void on_btn_delete_clicked();

    void on_btn_saveChanges_clicked();

    void on_btn_find_clicked();

    void on_pushButton_clicked();

  private:
    Ui::ManageTeacher* ui;
    QSqlTableModel* model;
    QButtonGroup* buttonGroup;
};

#endif  // MANAGETEACHER_H
