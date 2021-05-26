#ifndef INFORMATIONEXAM_H
#define INFORMATIONEXAM_H

#include <QWidget>

namespace Ui {
class InformationExam;
}

class InformationExam : public QWidget
{
    Q_OBJECT

public:
    explicit InformationExam(QWidget *parent = 0);
    ~InformationExam();

private:
    Ui::InformationExam *ui;
};

#endif // INFORMATIONEXAM_H
