#include "serverlogin.h"

#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>

#include "management.h"
#include "teacherwidget.h"
#include "threeques.h"
#include "ui_serverlogin.h"
ServerLogin::ServerLogin(QWidget* parent) : QMainWindow(parent), ui(new Ui::ServerLogin) {
    ui->setupUi(this);

    //    contentToJson();

    //打印qt支持的数据库驱动
    //    qDebug() << QSqlDatabase::drivers();
    //    //添加Mysql数据库
    //    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    //    //连接数据库
    //    db.setHostName("127.0.0.1");  //数据库服务器地址
    //    db.setUserName("root");       //数据库用户名
    //    db.setPassword("123456");     //密码
    //    db.setDatabaseName("exam");   //使用哪个数据库
    //    db.setPort(3306);

    //    //打开数据库
    //    if (!db.open()) {
    //        QMessageBox::warning(this, "错误", db.lastError().text());
    //        return;
    //    }
    //    QSqlQuery query(db);
    //    query.exec("CREATE TABLE student(学号 char(12) not null primary key,姓名 varchar(32) not null,性别 "
    //               "char(2) not null,专业 char(16) not null,班级 int not null,成绩 int null)");
    //    qDebug() << query.lastError().text();

    //    query.exec(
    //        "insert into student(学号,姓名,性别,专业,班级)values('201714670229','侯煜国','男','计算机科学与技术',4)");
    //    qDebug() << query.lastError().text();
    //    query.exec(
    //        "create table management(工号 char(12) primary key not null,姓名 varchar(32) not null,密码 varchar(32))");
    //    qDebug() << query.lastError().text();
    //    query.exec("insert into management(工号,姓名,密码)values('201714670229','侯煜国','hyg123456')");
    //    query.exec("insert into management(工号,姓名,密码)values('301714670223','李大国','hyg1234567')");
    //    qDebug() << query.lastError().text();
    //
}

ServerLogin::~ServerLogin() { delete ui; }

void ServerLogin::on_pushButton_clicked() {
    createMySqlConn();
    QSqlQuery query;
    query.exec("select * from management");
    bool status = false;
    while (query.next()) {
        if (query.value(0).toString() == ui->lineEdit_user->text()) {
            if (query.value(2).toString() == ui->lineEdit_passwd->text()) {
                status = true;
                management* manage = new management();
                manage->show();
                this->hide();
                break;
            }
        }
    }
    QSqlQuery query2;
    query2.exec("select * from teacher");
    while (query2.next()) {
        if (query2.value(0).toString() == ui->lineEdit_user->text()) {
            if (query2.value(2).toString() == ui->lineEdit_passwd->text()) {
                status = true;
                TeacherWidget* teacherWidget = new TeacherWidget();
                teacherWidget->show();
                this->hide();
                break;
            }
        }
    }
    if (!status) {
        QMessageBox::warning(this, "错误", "账号或密码错误");
    }
}
