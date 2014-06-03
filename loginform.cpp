#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(posaljiPodatke()));
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::posaljiPodatke()
{
    emit salji(this->ui->lineEdit->text(), this->ui->lineEdit_2->text());

    this->close();
}
