#include "threeques.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

//该函数测试将内容写到文件，后面再无调用过
void contentToJson() {
    QFile file(QApplication::applicationDirPath() + QString("/") + "test.json");
    if (file.open(QIODevice::WriteOnly)) {
        qDebug() << "文件打开成功";
    } else {
        qDebug() << "文件打开失败";
    }
    QJsonDocument jdoc;
    QJsonObject totalObj;
    QJsonArray choiceQuesArr;
    QJsonArray fullBlankArr;

    //保存选择题
    {
        QJsonObject obj;
        obj["title"] = "这是第1个个选择题";
        obj["A"] = QString("选项1");
        obj["B"] = QString("选项1");
        obj["C"] = QString("选项1");
        obj["D"] = QString("选项1");
        obj["answer"] = "A";
        choiceQuesArr.append(obj);
    }

    //保存选择题2
    {
        QJsonObject obj;
        obj["title"] = "这是第1个个选择题";
        obj["A"] = QString("选项1");
        obj["B"] = QString("选项1");
        obj["C"] = QString("选项1");
        obj["D"] = QString("选项1");
        obj["answer"] = "B";
        choiceQuesArr.append(obj);
    }
    totalObj["choiceQues"] = choiceQuesArr;

    //保存填空题
    {
        QJsonObject obj;
        obj["title"] = "这是第一个填空题";
        obj["num"] = 2;
        obj["1"] = QString("第一空");
        obj["2"] = QString("第二空");
        choiceQuesArr.append(obj);
    }
    {
        QJsonObject obj;
        obj["title"] = "这是第二个填空题";
        obj["num"] = 2;
        obj["1"] = QString("第一空");
        obj["2"] = QString("第二空");
        fullBlankArr.append(obj);
    }
    totalObj["fullBlank"] = fullBlankArr;
    jdoc.setObject(totalObj);
    file.write(jdoc.toJson(QJsonDocument::Indented));
    file.close();
}

void fileToJson(TotalQues& total, QString name) {
    //打开文件
    QFile file(QApplication::applicationDirPath() + QString("/") + name + ".json");
    //在与客户端相连后，文件已打开，再调用次函数可能会造成异常，因此先关闭下文件
    file.close();
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File open failed!";
    } else {
        qDebug() << "File open successfully";
    }
    QJsonParseError* error = new QJsonParseError;
    QJsonDocument jdc = QJsonDocument::fromJson(file.readAll(), error);

    //判断文件是否完整
    if (error->error != QJsonParseError::NoError) {
        qDebug() << "parseJson:" << error->errorString();
        return;
    }
    QJsonObject obj = jdc.object();  //获取对象
    qDebug() << "object size:" << obj.size();

    // ToatalQues total
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

        total.choiceQuesList.append(choiceQues);
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
        total.fullBlankList.append(fullBlank);
    }

    //解析简答题
    QJsonArray shortAnswerArr = obj["shortAnswer"].toArray();
    for (int i = 0; i < shortAnswerArr.count(); i++) {
        QJsonObject obj = shortAnswerArr[i].toObject();
        ShortAnswer shortAnswer;
        shortAnswer.title = obj["title"].toString();
        shortAnswer.answer = obj["answer"].toString().simplified();

        total.shortAnswerList.append(shortAnswer);
    }
    file.close();
}

void jsonToFile(TotalQues& T, QString name) {
    //打开文件
    QFile file(QApplication::applicationDirPath() + QString("/") + name + ".json");
    //在与客户端相连后，文件已打开，再调用该函数向文件写内容会造成异常，因此先关闭下文件
    file.close();
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "File open failed,threeques.cpp 134h";
    } else {
        qDebug() << "File opepn successfully,threeques.cpp 137h";
    }
    QJsonDocument jdoc;
    QJsonObject total;
    QJsonArray choiceQuesArr;
    QJsonArray fullBlankArr;
    QJsonArray shortAnswerArr;

    //保存选择题
    QList<ChoiceQues> choiceQuesList = T.choiceQuesList;
    foreach (ChoiceQues item, choiceQuesList) {
        QJsonObject obj;
        obj["title"] = item.title;
        obj["A"] = item.a;
        obj["B"] = item.b;
        obj["C"] = item.c;
        obj["D"] = item.d;
        obj["answer"] = item.answer;
        choiceQuesArr.append(obj);
        qDebug() << obj << "threeques.cpp,156h";
    }
    total["choiceQues"] = choiceQuesArr;

    //保存填空题
    QList<FullBlank> fullBlankList = T.fullBlankList;
    foreach (FullBlank item, fullBlankList) {
        QJsonObject obj;
        obj["title"] = item.title;
        obj["num"] = item.num;
        for (int i = 1; i <= item.num; i++) {
            QString str = QString("%1").arg(i);
            obj[str] = item.answer.at(i - 1);
        }
        fullBlankArr.append(obj);
        qDebug() << obj << "threeques.cpp,170h";
    }
    total["fullBlank"] = fullBlankArr;

    //保存简答题
    QList<ShortAnswer> shortAnswerList = T.shortAnswerList;
    foreach (ShortAnswer item, shortAnswerList) {
        QJsonObject obj;
        obj["title"] = item.title;
        obj["answer"] = item.answer;
        shortAnswerArr.append(obj);
        qDebug() << obj << "threeques.cpp,182h";
    }
    total["shortAnswer"] = shortAnswerArr;

    //保存json文件
    jdoc.setObject(total);
    file.write(jdoc.toJson(QJsonDocument::Indented));  // Indented:表示自动添加/n回车符
    file.close();
}

// void fileToJson_2(TotalQues& total, QString& name) {
//    //    QString str = QDir::currentPath() + QString("/") + name;
//    //    qDebug() << str;
//    //    QFile file(QDir::currentPath() + QString("/") + name + ".json");
//    //在与客户端相连后，文件已打开，再调用次函数可能会造成异常，因此先关闭下文件

//    QString filePath = QFileDialog::getOpenFileName(this, "open", "../","*.json");
//    QFile file;
//    file.setFileName(filePath);
//    QFileInfo fileinfo(filePath);
//    name = fileinfo.fileName();
//    file.close();
//    if (!file.open(QIODevice::ReadOnly)) {
//        qDebug() << "传过来的文件打开失败";
//    } else {
//        qDebug() << "传过来的文件打开成功";
//    }
//    QJsonParseError* error = new QJsonParseError;
//    QJsonDocument jdc = QJsonDocument::fromJson(file.readAll(), error);

//    //判断文件是否完整
//    if (error->error != QJsonParseError::NoError) {
//        qDebug() << "parseJson:" << error->errorString();
//        return;
//    }
//    QJsonObject obj = jdc.object();  //获取对象
//    qDebug() << "object size:" << obj.size();

//    // ToatalQues total
//    //解析选择题
//    QJsonArray choiceQuesArr = obj["choiceQues"].toArray();
//    for (int i = 0; i < choiceQuesArr.count(); i++) {
//        QJsonObject obj = choiceQuesArr[i].toObject();
//        ChoiceQues choiceQues;
//        choiceQues.title = obj["title"].toString();
//        choiceQues.a = obj["A"].toString();
//        choiceQues.b = obj["B"].toString();
//        choiceQues.c = obj["C"].toString();
//        choiceQues.d = obj["D"].toString();
//        choiceQues.answer = obj["answer"].toString();

//        total.choiceQuesList.append(choiceQues);
//        qDebug() << "解析出一个选择题";
//    }

//    //解析填空题
//    QJsonArray fullBlankArr = obj["fullBlank"].toArray();
//    for (int i = 0; i < fullBlankArr.count(); i++) {
//        QJsonObject obj = fullBlankArr[i].toObject();
//        FullBlank fullBlank;
//        fullBlank.title = obj["title"].toString();
//        int num = obj["num"].toInt();
//        fullBlank.num = num;
//        for (int i = 1; i <= num; i++) {
//            QString str = QString("%1").arg(i);
//            fullBlank.answer.append(obj[str].toString().simplified());
//        }
//        total.fullBlankList.append(fullBlank);
//    }

//    //解析简答题
//    QJsonArray shortAnswerArr = obj["shortAnswer"].toArray();
//    for (int i = 0; i < shortAnswerArr.count(); i++) {
//        QJsonObject obj = shortAnswerArr[i].toObject();
//        ShortAnswer shortAnswer;
//        shortAnswer.title = obj["title"].toString();
//        shortAnswer.answer = obj["answer"].toString().simplified();

//        total.shortAnswerList.append(shortAnswer);
//        qDebug() << "解析出一个简答题";
//    }
//    file.close();
//}
