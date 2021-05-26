#include "teacherwidget.h"

#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMessageBox>

#include "managestudent.h"
#include "ui_teacherwidget.h"
TeacherWidget::TeacherWidget(QWidget* parent) : QWidget(parent), ui(new Ui::TeacherWidget) {
    ui->setupUi(this);

    //测试
    //    Widget1* ws = new Widget1;
    //    ws->show();

    ui->stackedWidget->setCurrentIndex(0);
    this->setWindowTitle("考试系统");

    //默认选中第一个试卷
    ui->listWidget->setCurrentRow(0);

    //题库
    displayPaper = new DisplayPaper(ui->groupBox_paper);
    displayPaper->move(0, 8);
    displayPaper->resize(ui->groupBox_paper->size());

    QString currentName = ui->listWidget->currentItem()->text();
    ui->groupBox_paper->setTitle(currentName + QString("试卷"));
    ui->label_add0->setText(QString("向%1试卷中添加选择题").arg(currentName));
    ui->label_add1->setText(QString("向%1试卷中添加填空题").arg(currentName));
    ui->label_add2->setText(QString("向%1试卷中添加简答题").arg(currentName));

    int count = ui->listWidget->count();
    //遍历框中的题库名字
    for (int i = 0; i < count; i++) {
        bank_nameList.append(ui->listWidget->item(i)->text());
        totalMap[ui->listWidget->item(i)->text()];
    }
    //加载所有的题库
    load_file();

    //未与客户端连接时，发送文件按钮关闭
    ui->btn_send->setEnabled(false);
    connect(&timer, &QTimer::timeout, [=]() {
        //关闭定时器
        timer.stop();

        //发送文件
        sendData();
    });
    isStart = true;
    connect(this, &TeacherWidget::refresh, this, &TeacherWidget::on_listWidget_itemClicked);
    //    on_pushButton_8_clicked();

    //显示从客户端传过来的试卷
    paperScoring = new DisplayPaper(ui->groupBox_scoring);
    paperScoring->move(0, 8);
    paperScoring->resize(ui->groupBox_scoring->size());
}

TeacherWidget::~TeacherWidget() { delete ui; }

//加载已有的题库,加载第一个题库
void TeacherWidget::load_file() {
    displayPaper->clear();
    int count = ui->listWidget->count();
    for (int i = 0; i < count; i++) {
        TotalQues tt;
        fileToJson(tt, ui->listWidget->item(i)->text());

        totalMap[ui->listWidget->item(i)->text()] = tt;
    }

    //显示第一个列表中的第一个默认题库
    displayPaper->clear();
    for (auto it : totalMap[ui->listWidget->currentItem()->text()].choiceQuesList)
        displayPaper->addChoiceQues(it);
    for (auto it : totalMap[ui->listWidget->currentItem()->text()].fullBlankList)
        displayPaper->addFullBlank(it);
    for (auto it : totalMap[ui->listWidget->currentItem()->text()].shortAnswerList)
        displayPaper->addShortAnswer(it);
}

void TeacherWidget::on_pushButton_clicked() { ui->stackedWidget->setCurrentIndex(1); }

//向某个题库中添加选择题，添加后自动保存到json文件
void TeacherWidget::on_pushButton_4_clicked() {
    QString str = ui->listWidget->currentItem()->text();
    ChoiceQues d;
    AddItem1 dd;
    dd.bind(&d);
    dd.setWindowTitle("添加选择题");
    if (dd.exec() == QDialog::Accepted) {
        displayPaper->addChoiceQues(d);
        totalMap[ui->listWidget->currentItem()->text()].choiceQuesList.append(d);
        jsonToFile(totalMap[str], str);
    }
    QString current_name = ui->listWidget->currentItem()->text();
    if (totalMap.keys().contains(current_name)) {
    } else {
        //        TotalQues tt;
        //        fileToJson(tt,current_name);

        //        totalMap[current_name]=tt;
        qDebug() << "error teacherwidget.cpp,77h";
    }
    auto item = ui->listWidget->selectedItems().at(0);
    emit refresh(item);
}

//向某个题库中添加填空题，添加后自动保存到json文件
void TeacherWidget::on_pushButton_5_clicked() {
    QString str = ui->listWidget->currentItem()->text();
    FullBlank d;
    AddItem2 dd;
    dd.bind(&d);
    dd.setWindowTitle("添加填空题");
    if (dd.exec() == QDialog::Accepted) {
        displayPaper->addFullBlank(d);
        totalMap[ui->listWidget->currentItem()->text()].fullBlankList.append(d);
        jsonToFile(totalMap[str], str);
    }
    QString current_name = ui->listWidget->currentItem()->text();
    if (totalMap.keys().contains(current_name)) {
    } else {
        qDebug() << "error teacherwidget.cpp,99h";
    }
    emit refresh(ui->listWidget->selectedItems().at(0));
}

//向某个题库中添加简答题，添加后自动保存到json文件

void TeacherWidget::on_pushButton_6_clicked() {
    QString str = ui->listWidget->currentItem()->text();
    ShortAnswer d;
    AddItem3 dd;
    dd.bind(&d);
    dd.setWindowTitle("添加简答题");
    if (dd.exec() == QDialog::Accepted) {
        displayPaper->addShortAnswer(d);
        totalMap[ui->listWidget->currentItem()->text()].shortAnswerList.append(d);
        jsonToFile(totalMap[str], str);
    }
    QString current_name = ui->listWidget->currentItem()->text();
    if (totalMap.keys().contains(current_name)) {
    } else {
        qDebug() << "error teacherwidget.cpp,119h";
    }
    emit refresh(ui->listWidget->selectedItems().at(0));
}
void TeacherWidget::on_pushButton_3_clicked() { ui->stackedWidget->setCurrentIndex(0); }

//从文件中打开试卷
void TeacherWidget::on_pushButton_7_clicked() {
    QString path =
        QFileDialog::getOpenFileName(this, "添加", QApplication::applicationDirPath(), "files(*.json)\nAll files(*.*)");
    qDebug() << path;
    QStringList strls = path.split("/");
    QString str = strls.last();
    ui->listWidget->addItem(str.split(".").first());

    QString current_name = str.split(".").first();
    if (totalMap.keys().contains(current_name)) {
        qDebug() << "包含对应试卷";
    } else {
        TotalQues tt;
        fileToJson(tt, current_name);
        totalMap[current_name] = tt;
        bank_nameList.append(current_name);

        //        qDebug() << "error teacherwidget.cpp 142h";
    }
}

//点击试卷名，加载到右边的groupbox
void TeacherWidget::on_listWidget_itemClicked(QListWidgetItem* item) {
    QString str = item->text();
    if (str.isEmpty())
        return;
    ui->groupBox_paper->setTitle(str + QString("题库"));
    ui->label_add0->setText(QString("向%1题库中添加选择题").arg(str));
    ui->label_add1->setText(QString("向%1题库中添加填空题").arg(str));
    ui->label_add2->setText(QString("向%1题库中添加简答题").arg(str));

    displayPaper->clear();
    foreach (auto it, totalMap[ui->listWidget->currentItem()->text()].choiceQuesList) {
        displayPaper->addChoiceQues(it);
        qDebug() << "显示对应文件的选择题";
    }
    foreach (auto it, totalMap[ui->listWidget->currentItem()->text()].fullBlankList) {
        displayPaper->addFullBlank(it);
        qDebug() << "显示对应文件的填空题";
    }
    foreach (auto it, totalMap[ui->listWidget->currentItem()->text()].shortAnswerList) {
        displayPaper->addShortAnswer(it);
        qDebug() << "显示对应文件的简答题";
    }
}

//打开服务器
void TeacherWidget::on_btn_openSer_clicked() {
    qDebug() << "执行开始";
    tcpServer = new QTcpServer(this);
    //监听
    qDebug() << "未开始监听";
    tcpServer->listen(QHostAddress::Any, 8888);
    qDebug() << "已开始监听";
    ui->textEdit_conInfo->append("服务器端口为：8888");

    //    ui->btn_send->setEnabled(true);
    //    QListWidgetItem* item = ui->listWidget->selectedItems().at(0);
    //    QString fileName = item->text();
    //    qDebug() << fileName;

    //如果客户端成功和服务器连接
    connect(tcpServer, &QTcpServer::newConnection, [=]() {
        //取出建立好连接的套接字
        tcpSocket = tcpServer->nextPendingConnection();
        qDebug() << "执行到221h";
        while (1)
            break;
        socketList.append(tcpSocket);
        qDebug() << "执行到223h";
        //获取对方的ip和端口
        for (int i = 0; i < socketList.length(); i++) {
            QString ip = socketList.at(i)->peerAddress().toString();
            quint16 port = socketList.at(i)->peerPort();
            QString str = QString("[%1:%2] 成功连接").arg(ip).arg(port);
            ui->textEdit_conInfo->append(str);
        }
        //成功连接后，send按钮才可用
        ui->btn_send->setEnabled(true);
        //文件选择
        QListWidgetItem* item = ui->listWidget->selectedItems().at(0);
        fileName = item->text();
        qDebug() << fileName;
        QString filePath(QApplication::applicationDirPath() + QString("/") + fileName + ".json");
        if (!filePath.isEmpty()) {
            fileName.clear();
            fileSize = 0;
            //获取文件信息
            QFileInfo info(filePath);
            fileName = info.fileName();
            qDebug() << fileName << "fileName";  //打印下文件名字，与listwidget框中所选名字是否相同
            fileSize = info.size();              //获取文件大小

            sendSize = 0;
            //只读方式打开文件
            //指定文件的名字
            file.setFileName(filePath);
            if (!file.open(QIODevice::ReadOnly)) {
                qDebug() << "只读方式打开文件失败";
            }

            //提示文件的路径
            ui->textEdit_conInfo->append(filePath);
        } else {
            qDebug() << "文件不存在";
        }
    });
}

void TeacherWidget::on_btn_send_clicked() {
    //先发送文件头信息
    //再发送文件真正信息
    //文件名##文件大小
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    //发送头部信息
    for (int i = 0; i < socketList.length(); i++) {
        qint64 len = socketList.at(i)->write(head.toUtf8());
        if (len > 0) {  //头部信息发送成功
            //发送文件内部信息 防止TCP粘包
            //需要通过定时器延时20ms
            timer.start(200);
        } else {
            qDebug() << "头部信息发送失败 245h";
            file.close();
        }
        qDebug() << "发送一次qqqqqqqqqqqqq";
        QTimer timer2;
        connect(&timer2, &QTimer::timeout, [&]() { timer2.start(1000); });
    }
    //从链表中删除与服务端断开的（客户端的）—套接字
    connect(tcpSocket, &QTcpSocket::disconnected, this, [=]() {
        tcpSocket = (QTcpSocket*)this->sender();  //得到发出信号的客户端
        QString temp = QString("[%1:%2]:退出").arg(tcpSocket->peerAddress().toString()).arg(tcpSocket->peerPort());
        ui->textEdit_conInfo->append(temp);
        for (int i = 0; i < socketList.length(); i++) {
            if (socketList.at(i)->peerAddress() == tcpSocket->peerAddress() &&
                socketList.at(i)->peerPort() == tcpSocket->peerPort()) {
                socketList.removeAt(i);
                break;
            }
        }
    });
}

void TeacherWidget::sendData() {
    qint64 len = 0;
    do {
        //每次发送文件的大小
        char buf[4 * 1024] = {0};
        //往文件中读数据
        len = file.read(buf, sizeof(buf));

        //发送数据,发多少，读多少
        len = tcpSocket->write(buf, len);
        qDebug() << "文件发送一次";

        //发送数据长度累加
        sendSize += len;
    } while (len > 0);

    //是否发送文件完毕
    if (sendSize == fileSize) {
        ui->textEdit_conInfo->append("文件发送完毕");
        file.close();
        //与客户端断开
        //        tcpSocket->disconnectFromHost();
        //        tcpSocket->close();
    }
    paperReceived();
}
void TeacherWidget::paperReceived() {
    for (int i = 0; i < socketList.length(); i++) {
        connect(socketList.at(i), &QTcpSocket ::readyRead, [=]() {
//            for (int i = 0; i < socketList.length(); i++) {
                QByteArray buf = socketList.at(i)->readAll();
                if (isStart) {
                    isStart = false;
                    getFileName = QString(buf).section("##", 0, 0);
                    getFileSize = QString(buf).section("##", 1, 1).toInt();
                    receivedSize = 0;
                    getFile.close();
                    getFile.setFileName(getFileName);
                    qDebug() << getFileName << "文头件已接收!!!!!!!!!!!!!!!!";
                    if (!getFile.open(QIODevice ::WriteOnly)) {
                        qDebug() << "writeOnly方式打开发来的文件失败";
                    }
                } else {
                    qint64 len = getFile.write(buf);
                    qDebug() << "文件内容接收一次";
                    receivedSize += len;
                    isStart=true;
                    getFile.close();
//                    if (receivedSize == getFileSize) {
//                        isStart=true;
//                        getFile.close();
//                        QMessageBox ::information(this, "完成", "文件接收完成");
//                        //                tcpSocket->disconnectFromHost();
//                        //                tcpSocket->close();
//                    }
                    //            }
                }

        });
    }
    qDebug() << "文件接收***************************************";
}
void TeacherWidget::on_pushButton_8_clicked() {
    //**********************************************************************
    QString filePath = QFileDialog::getOpenFileName(this, "open", "./", "JSON(*.json)");
    QFile file;
    file.setFileName(filePath);
    QFileInfo fileinfo(filePath);
    QString name = fileinfo.fileName();
    qDebug() << name;
    QString pre_filename = name.section(".", 0, 1);
    ui->label_tips->setText(name.section(".", 1, 1));
    //        file.close();
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "传过来的文件打开失败";
    } else {
        qDebug() << "传过来的文件打开成功";
    }
    TotalQues total_paper;
    QJsonParseError* error = new QJsonParseError;
    QJsonDocument jdc = QJsonDocument::fromJson(file.readAll(), error);

    //判断文件是否完整
    if (error->error != QJsonParseError::NoError) {
        qDebug() << "parseJson:" << error->errorString();
        return;
    }
    QJsonObject obj = jdc.object();  //获取对象
    qDebug() << "object size:" << obj.size();

    //解析选择题
    QJsonArray choiceQuesArr = obj["choiceQues"].toArray();
    for (int i = 0; i < choiceQuesArr.count(); i++) {
        QJsonObject obj = choiceQuesArr[i].toObject();
        ChoiceQues choiceQues;
        choiceQues.title = obj["title"].toString();
        choiceQues.a = obj["A"].toString();
        choiceQues.b = obj["B"].toString();
        choiceQues.c = obj["C"].toString();
        choiceQues.d = obj["D"].toString();
        choiceQues.answer = obj["answer"].toString();

        total_paper.choiceQuesList.append(choiceQues);
        qDebug() << "解析出一个选择题";
    }

    //解析填空题
    QJsonArray fullBlankArr = obj["fullBlank"].toArray();
    for (int i = 0; i < fullBlankArr.count(); i++) {
        QJsonObject obj = fullBlankArr[i].toObject();
        FullBlank fullBlank;
        fullBlank.title = obj["title"].toString();
        int num = obj["num"].toInt();
        fullBlank.num = num;
        for (int i = 1; i <= num; i++) {
            QString str = QString("%1").arg(i);
            fullBlank.answer.append(obj[str].toString().simplified());
        }
        total_paper.fullBlankList.append(fullBlank);
    }

    //解析简答题
    QJsonArray shortAnswerArr = obj["shortAnswer"].toArray();
    for (int i = 0; i < shortAnswerArr.count(); i++) {
        QJsonObject obj = shortAnswerArr[i].toObject();
        ShortAnswer shortAnswer;
        shortAnswer.title = obj["title"].toString();
        shortAnswer.answer = obj["answer"].toString().simplified();

        total_paper.shortAnswerList.append(shortAnswer);
        qDebug() << "解析出一个简答题";
    }
    file.close();
    ////********************************************************************************

    ui->stackedWidget->setCurrentIndex(2);
    //    DisplayPaper* paperScoring = new DisplayPaper(ui->groupBox_scoring);
    //    paperScoring->move(0, 8);
    //    paperScoring->resize(ui->groupBox_scoring->size());
    //        TotalQues t;
    //        QString str;
    //    QString str = getFileName.section(".", 0, 1);
    //    QString stu_no = getFileName.section(".", 1, 1);
    //    ui->groupBox_scoring->title().append(stu_no);
    //    ui->label_tips->setText(stu_no);
    //        fileToJson_2(t, str);
    //        QString _openFileName = str.section(".", 0, 1);
    //        totalMap[_openFileName] = t;
    //        QString stu_NO = str.section(".", 1, 1);
    //        ui->label_tips->setText(stu_NO);
    totalMap[pre_filename] = total_paper;
    paperScoring->clear();
    for (auto it : totalMap[pre_filename].choiceQuesList) {
        paperScoring->addChoiceQues(it);
        qDebug() << "添加选择题UI一次UIUIUIUIUIUIUIUIUIUIUIUIUI";
    }
    for (auto it : totalMap[pre_filename].fullBlankList) {
        paperScoring->addFullBlank(it);
        qDebug() << "添加填空题UI一次UIUIUIUIUIUIUIUIUIUIUIUIUI";
    }
    for (auto it : totalMap[pre_filename].shortAnswerList) {
        paperScoring->addShortAnswer(it);
        qDebug() << "添加简答题UIUIUIUIUUIUIUIUIUIUIUIUIUIUIUIUI";
    }
    qDebug() << "解析完毕，over";
}
void TeacherWidget::on_pushButton_2_clicked() {}
void TeacherWidget::on_pushButton_10_clicked() { ui->stackedWidget->setCurrentIndex(0); }
void TeacherWidget::on_pushButton_9_clicked() {
    ManageStudent* manage = new ManageStudent();
    manage->show();
    manage->limit();
}
