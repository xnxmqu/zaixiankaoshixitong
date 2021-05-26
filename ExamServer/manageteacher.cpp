#include "manageteacher.h"

#include <QMessageBox>
#include <QSqlRecord>

#include "management.h"
#include "ui_manageteacher.h"
ManageTeacher::ManageTeacher(QWidget* parent) : QWidget(parent), ui(new Ui::ManageTeacher) {
    ui->setupUi(this);

    model = new QSqlTableModel(this);

    //上个页面选中管理教师表
    model->setTable("teacher");
    model->setHeaderData(0, Qt::Horizontal, "工号");

    //把model放在view里
    ui->tableView->setModel(model);

    //显示model里的数据
    model->select();

    //设置model的编辑模式,手动提交修改
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    //设置默认按工号查询教师信息
    ui->radioButton_tchNo->setChecked(true);

    //使用QButtonGroup管理单选框
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->radioButton_tchNo, 0);
    buttonGroup->addButton(ui->radioButton_tchName, 1);
}

ManageTeacher::~ManageTeacher() { delete ui; }

void ManageTeacher::on_btn_add_clicked() {
    //添加空记录
    QSqlRecord record = model->record();
    //获取行号
    int row = model->rowCount();
    //向第row行插入数据，此时0至row-1行有数据
    model->insertRecord(row, record);
}

void ManageTeacher::on_btn_delete_clicked() {
    QItemSelectionModel* sModel = ui->tableView->selectionModel();
    QModelIndexList list = sModel->selectedRows();
    //删除所有选中的行
    for (int i = 0; i < list.size(); i++) {
        model->removeRow(list.at(i).row());
    }
}

void ManageTeacher::on_btn_saveChanges_clicked() {
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

void ManageTeacher::on_btn_find_clicked() {
    QString content = ui->lineEdit->text();
    QString str = "";
    if (buttonGroup->checkedId() == 0) {
        str = QString("工号='%1'").arg(content);
    }
    if (buttonGroup->checkedId() == 1) {
        str = QString("姓名='%1'").arg(content);
    }
    model->setFilter(str);
    model->select();
}

void ManageTeacher::on_pushButton_clicked() {
    management* manageChoose = new management();
    manageChoose->show();
    this->hide();
}
