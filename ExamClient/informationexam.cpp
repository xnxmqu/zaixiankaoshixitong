#include "informationexam.h"

#include "clientlogin.h"
#include "ui_informationexam.h"
InformationExam::InformationExam(QWidget* parent) : QWidget(parent), ui(new Ui::InformationExam) {
    ui->setupUi(this);
    ClientLogin login;
    ui->label_stuNo->text() = login.get_No();
    ui->label_stuName->text() = login.get_name();
    ui->label_stuProf->text() = login.get_prof();
    ui->label_stuClass->text() = login.get_class();
}

InformationExam::~InformationExam() { delete ui; }
