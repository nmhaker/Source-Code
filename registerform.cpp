#include "registerform.h"
#include "ui_registerform.h"

RegisterForm::RegisterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterForm)
{
    ui->setupUi(this);

    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(posaljiPodatke()));
}

RegisterForm::~RegisterForm()
{
    delete ui;
}

void RegisterForm::posaljiPodatke()
{
    emit salji(this->ui->lineEdit->text(), this->ui->lineEdit_2->text(), this->ui->lineEdit_3->text(), this->ui->lineEdit_4->text(), this->ui->lineEdit_5->text());

    this->close();
}
