#include "managestudent.h"

#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include "management.h"
#include "serverlogin.h"
#include "ui_managestudent.h"
ManageStudent::ManageStudent(QWidget* parent) : QWidget(parent), ui(new Ui::ManageStudent) {
    ui->setupUi(this);
    //赋一个默认值,false默认为管理教师表
    //    checkStudent = false;
    //    management* tempManagement = new management();
    //    // management的页面选择点击管理学生按钮，槽函数改变checkStudent的值位true
    //    connect(tempManagement, &management::setStudentChecked, this, &ManageStudent::getStudentChecked);
    //设置模型

    model = new QSqlTableModel(this);
    //上个页面选中管理学生
    model->setTable("student");
    model->setHeaderData(0, Qt::Horizontal, "学号");
    //把model放在view里
    ui->tableView->setModel(model);

    //显示model里的数据
    model->select();

    //    model->setHeaderData(0, Qt::Horizontal, "学号");
    //设置model的 编辑模式，手动提交修改
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置view中的数据库不允许修改

    //设置默认按学号查询学生信息或者按工号查询教师信息
    ui->radioButton_stuNo->setChecked(true);

    //使用QButtonGroup管理单选框
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->radioButton_stuNo, 0);
    buttonGroup->addButton(ui->radioButton_stuName, 1);
}

ManageStudent::~ManageStudent() { delete ui; }

void ManageStudent::on_btn_add_clicked() {
    //添加空记录
    QSqlRecord record = model->record();
    //获取行号
    int row = model->rowCount();
    //向第row行插入数据，此时0至row-1行都有数据
    model->insertRecord(row, record);
}

void ManageStudent::on_btn_saveChanges_clicked() {
    int ret = QMessageBox::question(this, "询问", "是否保存？", QMessageBox::Ok | QMessageBox::Cancel);
    switch (ret) {
        case QMessageBox::Ok: model->submitAll(); break;
        case QMessageBox::Cancel:
            model->revertAll();
            model->submitAll();
            break;
        default: break;
    }
}

void ManageStudent::on_btn_delete_clicked() {
    QItemSelectionModel* sModel = ui->tableView->selectionModel();
    //取出模型中的索引,可进行单项或多项删除
    QModelIndexList list = sModel->selectedRows();
    //删除所有选中的行
    for (int i = 0; i < list.size(); i++) {
        model->removeRow(list.at(i).row());
    }
}

void ManageStudent::on_btn_find_clicked() {
    QString content = ui->lineEdit->text();

    if (buttonGroup->checkedId() == 0) {
        QString str = "";
        str = QString("学号='%1'").arg(content);
        //        else
        //            str = QString("工号='%1'").arg(content);
        model->setFilter(str);
        model->select();
    }
    if (buttonGroup->checkedId() == 1) {
        QString str = QString("姓名='%1'").arg(content);
        model->setFilter(str);
        model->select();
    }
}

void ManageStudent::on_pushButton_clicked() {
    management* manageChoose = new management();
    manageChoose->show();
    this->hide();
}

void ManageStudent::limit() {
    ui->btn_add->hide();
    ui->btn_delete->hide();
    ui->btn_saveChanges->hide();
    ui->pushButton->hide();
}
