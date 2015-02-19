#include "debugprozor.h"
#include "ui_debugprozor.h"

DebugProzor::DebugProzor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugProzor)
{
    ui->setupUi(this);
}

DebugProzor::~DebugProzor()
{
    delete ui;
}

void DebugProzor::updateCoordinates(int x, int y, int w, int h)
{
    this->ui->lineEdit->setText(QString::number(x));
    this->ui->lineEdit_2->setText(QString::number(y));
    this->ui->lineEdit_3->setText(QString::number(w));
    this->ui->lineEdit_4->setText(QString::number(h));
}

