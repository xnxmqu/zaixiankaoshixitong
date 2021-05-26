#ifndef MANAGESTUDENT_H
#define MANAGESTUDENT_H

#include <QButtonGroup>
#include <QSqlTableModel>
#include <QWidget>
namespace Ui {
    class ManageStudent;
}

class ManageStudent : public QWidget {
    Q_OBJECT

  public:
    explicit ManageStudent(QWidget* parent = 0);
    ~ManageStudent();

    void limit();

  private slots:
    void on_btn_add_clicked();

    void on_btn_saveChanges_clicked();

    void on_btn_delete_clicked();

    void on_btn_find_clicked();

    void on_pushButton_clicked();

  private:
    Ui::ManageStudent* ui;
    QSqlTableModel* model;
    QButtonGroup* buttonGroup;
    //    bool checkStudent;
};

#endif  // MANAGESTUDENT_H
