#ifndef CLIENTLOGIN_H
#define CLIENTLOGIN_H

#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QTcpSocket>
#include <QTimer>
#include <QWidget>

#include "displaypaper.h"
#include "threeques.h"
namespace Ui {
    class ClientLogin;
}

class ClientLogin : public QWidget {
    Q_OBJECT

  public:
    explicit ClientLogin(QWidget* parent = 0);
    ~ClientLogin();

    QString get_No() { return stu_No; }
    QString get_name() { return stu_name; }
    QString get_prof() { return stu_Prof; }
    QString get_class() { return stu_class; }

    void sendData();
  private slots:
    void on_btn_LogIn_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

  private:
    Ui::ClientLogin* ui;
    QString stu_No;
    QString stu_name;
    QString stu_Prof;
    QString stu_class;

    //进行通信的对象
    QTcpSocket* tcpSocket;
    QFile file;           //文件对象
    QString fileName;     //文件名字
    qint64 fileSize;      //文件大小
    qint64 receivedSize;  //已接收文件的信息
    bool isStart;

    //显示试卷的对象
    DisplayPaper* displayPaper;
    QMap<QString, TotalQues> totalMap;

    //向服务器端发送文件（试卷）的对象
    QFile send_File;
    QString send_FileName;
    qint64 send_fileSize;
    qint64 sentSize;
    QTimer timer;

    //    //提交试卷时所用的对象
    //    TotalQues totalExam;

    static void createMySqlConn() {
        //        qDebug() << QSqlDatabase::drivers();
        //添加Mysql数据库
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        //连接数据库
        db.setHostName("127.0.0.1");  //数据库服务器地址
        db.setUserName("root");       //数据库用户名
        db.setPassword("123456");     //密码
        db.setDatabaseName("exam");   //使用哪个数据库
        db.setPort(3306);

        //打开数据库
        if (!db.open()) {
            QMessageBox::warning(nullptr, "错误", db.lastError().text());
            return;
        }
        qDebug() << db.lastError().text();
    }
};

#endif  // CLIENTLOGIN_H
