#include "threeques.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

void fileToJson(TotalQues& total, QString name) {
    //打开文件
    //    QFile file(QApplication::applicationDirPath()+ QString("/") + name);

    QString str = QDir::currentPath() + QString("/") + name;
    qDebug() << str;
    QFile file(QDir::currentPath() + QString("/") + name + ".json");
    //在与客户端相连后，文件已打开，再调用次函数可能会造成异常，因此先关闭下文件

    file.close();
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "传过来的文件打开失败";
    } else {
        qDebug() << "传过来的文件打开成功";
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
        qDebug()<<"解析出一个选择题";
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
        qDebug()<<"解析出一个简答题";
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
