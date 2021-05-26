#include "management.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "managestudent.h"
#include "manageteacher.h"
#include "serverlogin.h"
#include "ui_management.h"
management::management(QWidget* parent) : QWidget(parent), ui(new Ui::management) {
    ui->setupUi(this);

    //    connect(ui->btn_manageStudent, &QPushButton::clicked, this, &management::setStudentChecked);
}

management::~management() { delete ui; }

//    QSqlQuery query;
//    query.exec("select * from student");
//    while (query.next()) {  //一行一行遍历
//        //取出当前行的内容
//        qDebug() << query.value(0).toString() << query.value(1).toString() << query.value(2).toString()
//                 << query.value(3).toString() << query.value(4).toInt() << query.value(5).toInt();
//    }

void management::on_btn_manageStudent_clicked() {
    //创建放在堆里对象，否则会被释放

    ManageStudent* manageInfo = new ManageStudent;
    manageInfo->show();
    this->hide();
}

void management::on_btn_manageTeacher_clicked() {
    ManageTeacher* manageInfo = new ManageTeacher();
    manageInfo->show();
    this->hide();
}
