#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <QWidget>

namespace Ui {
    class management;
}

class management : public QWidget {
    Q_OBJECT

  public:
    explicit management(QWidget* parent = 0);
    ~management();
  signals:
    void setStudentChecked();

  private slots:

    void on_btn_manageStudent_clicked();

    void on_btn_manageTeacher_clicked();

  private:
    Ui::management* ui;
};

#endif  // MANAGEMENT_H
