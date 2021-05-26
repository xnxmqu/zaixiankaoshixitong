#ifndef SERVERLOGIN_H
#define SERVERLOGIN_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>

namespace Ui {
    class ServerLogin;
}

class ServerLogin : public QMainWindow {
    Q_OBJECT

  public:
    explicit ServerLogin(QWidget* parent = 0);
    ~ServerLogin();

  private slots:
    void on_pushButton_clicked();

  private:
    Ui::ServerLogin* ui;

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

#endif  // SERVERLOGIN_H
