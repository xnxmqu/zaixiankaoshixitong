#ifndef TEACHERWIDGET_H
#define TEACHERWIDGET_H

//#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QWidget>

#include "additem1.h"
#include "additem2.h"
#include "additem3.h"
#include "displaypaper.h"
#include "teacherwidget.h"
#include "threeques.h"
namespace Ui {
    class TeacherWidget;
}

class TeacherWidget : public QWidget {
    Q_OBJECT

  public:
    explicit TeacherWidget(QWidget* parent = 0);
    ~TeacherWidget();

    void load_file();  //加载试卷
    void sendData();   //发送文件数据
    void paperReceived();

  signals:
    void refresh(QListWidgetItem* item);
    //    void limit();

  private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_listWidget_itemClicked(QListWidgetItem* item);

    void on_btn_openSer_clicked();

    void on_btn_send_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

  private:
    Ui::TeacherWidget* ui;

    //已有的题库
    QStringList bank_nameList;
    DisplayPaper* displayPaper;
    QMap<QString, TotalQues> totalMap;

    //进行通信和发送文件(试卷)
    QList<QTcpSocket*> socketList;

    QTcpServer* tcpServer;  //监听套接字
    QTcpSocket* tcpSocket;  //通信套接字
    QFile file;
    QString fileName;
    qint64 fileSize;
    //已发送文件的信息
    qint64 sendSize;  //已发送文件的大小
    QTimer timer;     //定时器

    //接收客户端发送来的文件（试卷）
    QFile getFile;
    QString getFileName;
    qint64 getFileSize;
    qint64 receivedSize;
    bool isStart;

    DisplayPaper* paperScoring;
};

#endif  // TEACHERWIDGET_H
