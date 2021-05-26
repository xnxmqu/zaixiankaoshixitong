#include "clientlogin.h"

#include <QFileInfo>
#include <QHostAddress>
#include <QSqlQuery>

#include "informationexam.h"
#include "ui_clientlogin.h"

ClientLogin::ClientLogin(QWidget* parent) : QWidget(parent), ui(new Ui::ClientLogin) {
    ui->setupUi(this);
    //试卷实例
    displayPaper = new DisplayPaper(ui->groupPaper);
    displayPaper->move(0, 8);
    displayPaper->resize(ui->groupPaper->size());

    ui->stackedWidget->setCurrentIndex(0);
    tcpSocket = new QTcpSocket(this);
    isStart = true;
    connect(tcpSocket, &QTcpSocket::readyRead, [=]() {
        //取出接收的内容
        QByteArray buf = tcpSocket->readAll();
        if (isStart) {
            //接收头
            isStart = false;
            //解析头部信息
            fileName = QString(buf).section("##", 0, 0);
            fileSize = QString(buf).section("##", 1, 1).toInt();
            receivedSize = 0;
            //打开文件
            file.setFileName(fileName);
            qDebug() << "文件头已接收";

            if (!file.open(QIODevice::WriteOnly)) {
                qDebug() << "WriteOnly erro 27h";
            }

        } else {  //接收文件内部信息
            qint64 len = file.write(buf);
            qDebug() << "文件接收一次";
            receivedSize += len;
            if (receivedSize == fileSize) {
                file.close();
                QMessageBox::information(this, "完成", "文件接收完成");
                //                tcpSocket->disconnectFromHost();
                //                tcpSocket->close();
            }
        }
    });
    ui->label_paperName->setText(fileName);
    connect(&timer, &QTimer::timeout, [=]() {
        timer.stop();
        sendData();
    });
}

ClientLogin::~ClientLogin() { delete ui; }

void ClientLogin::on_btn_LogIn_clicked() {
    createMySqlConn();
    QSqlQuery query;
    query.exec("select * from student");
    bool status = false;
    while (query.next()) {
        if (query.value(0).toString() == ui->lineEdit_user->text()) {
            if (query.value(2).toString() == ui->lineEdit_passwd->text()) {
                status = true;
                stu_No = query.value(0).toString();
                ui->label_stuNo_2->setText(stu_No);
                stu_name = query.value(1).toString();
                ui->label_stuName_2->setText(stu_name);
                stu_Prof = query.value(4).toString();
                ui->label_stuProf_2->setText(stu_Prof);
                stu_class = query.value(5).toString();
                ui->label_stuClass_2->setText(stu_class);
                ui->stackedWidget->setCurrentIndex(1);
                break;
            }
        }
    }
    if (!status) {
        QMessageBox::warning(this, "错误", "账号或密码错误");
    }
}

void ClientLogin::on_pushButton_clicked() {
    //获取服务器的ip和端口
    QString ip = ui->lineEdit_ip->text();
    quint64 port = ui->lineEdit_port->text().toInt();
    tcpSocket->connectToHost(QHostAddress(ip), port);
}

void ClientLogin::on_pushButton_2_clicked() {
    if (fileName.isEmpty()) {
        QMessageBox::information(this, "试卷未接收", "试卷未接收");
        return;
    }
    ui->stackedWidget->setCurrentIndex(2);

    //    //试卷显示
    //    displayPaper = new DisplayPaper(ui->groupPaper);
    //    displayPaper->move(0, 8);
    //    displayPaper->resize(ui->groupPaper->size());

    //    QFile file(QApplication::applicationDirPath() + "./" + fileName + ".json");
    //    if (!file.open(QIODevice::ReadOnly)) {
    //        qDebug() << "传过来的文件打开失败";
    //    } else {
    //        qDebug() << "传过来的试卷打开成功";
    //    }
    TotalQues t;
    QString str1 = fileName.section(".", 0, 0);
    fileToJson(t, str1);
    totalMap[str1] = t;

    //显示试卷
    displayPaper->clear();

    for (auto it : totalMap[str1].choiceQuesList) {
        displayPaper->addChoiceQues(it);
    }
    for (auto it : totalMap[str1].fullBlankList)
        displayPaper->addFullBlank(it);
    for (auto it : totalMap[str1].shortAnswerList)
        displayPaper->addShortAnswer(it);
    qDebug() << "题目添加完成完成";
}

void ClientLogin::on_pushButton_3_clicked() {
    //    TotalQues t0;
    QString str1 = fileName.section(".", 0, 0);
    //    fileToJson(t0, str1);
    //    totalMap[str1] = t0;
    //    int ind = 1;
    int i = 0;
    foreach (auto it, displayPaper->choiceListUI) {
        //不能使用list.at(i),因为at返回的是一个常量对象，无法改变数据,[]返回非常量对象
        qDebug() << "选择题准备答案保存一次";
        totalMap[str1].choiceQuesList[i].answer = it->getAnswer();
        i++;
        qDebug() << "选择题答案保存一次";
    }
    i = 0;
    foreach (auto it, displayPaper->fullListUI) {
        totalMap[str1].fullBlankList[i].answer = it->getAnswer();
        i++;
        qDebug() << "选择题答案保存一次2222222";
    }
    i = 0;
    foreach (auto it, displayPaper->shortListUI) {
        totalMap[str1].shortAnswerList[i].answer = it->getAnswer();
        i++;
        qDebug() << "选择题答案保存一次3333333";
    }
    //    QString str2 = fileName.section(".", 0, 0);
    TotalQues t1 = totalMap[str1];

    jsonToFile(t1, str1 + "." + stu_No);
    //...........................从客户端往服务端发文件................
    //    on_pushButton_clicked();

    //    connect(tcpSocket, &QTcpSocket::connected, [=]() {
    send_FileName = str1 + "." + stu_No;
    QString send_FilePath(QApplication::applicationDirPath() + QString("/") + send_FileName + ".json");
    if (!send_FilePath.isEmpty()) {
        send_FileName.clear();
        send_fileSize = 0;
        QFileInfo info(send_FilePath);
        send_FileName = info.fileName();
        qDebug() << "发送的文件名称:" << info.fileName();
        send_fileSize = info.size();
        sentSize = 0;
        send_File.setFileName(send_FilePath);
        if (!send_File.open(QIODevice::ReadOnly)) {
            qDebug() << "只读方式打开文件失败";
        } else {
            qDebug() << "只读方式打开文成功";
        }
    } else {
        qDebug() << "要发送的文件不存在";
    }
    QString head = QString("%1##%2").arg(send_FileName).arg(send_fileSize);
    qDebug() << "head" << head;
    qint64 len = tcpSocket->write(head.toUtf8());

    qDebug() << "已发送文件的长度len:" << len;
    if (len > 0) {
        timer.start(200);
        qDebug() << "timer已开启";
    } else {
        qDebug() << "头部信息发送失败 179h";
        send_File.close();
    }
    //    });
}

void ClientLogin::sendData() {
    qint64 len = 0;
    do {
        char buf[4 * 1024] = {0};
        len = send_File.read(buf, sizeof(buf));
        len = tcpSocket->write(buf, len);
        qDebug() << "文件发送一行 191h";
        sentSize += len;
    } while (len > 0);
    if (sentSize == send_fileSize) {
        QMessageBox::information(this, "提示", "文件已发送");
        file.close();
        //        tcpSocket->disconnectFromHost();
        //        tcpSocket->close();
    }
}
