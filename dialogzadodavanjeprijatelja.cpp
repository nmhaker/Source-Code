#include "dialogzadodavanjeprijatelja.h"
#include "ui_dialogzadodavanjeprijatelja.h"

DialogZaDodavanjePrijatelja::DialogZaDodavanjePrijatelja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogZaDodavanjePrijatelja)
{
    ui->setupUi(this);

    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(posaljiInformaciju()));
    connect(this->ui->lineEdit, SIGNAL(textEdited(QString)), this, SIGNAL(proveri(QString)));

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x, y);

    status.setGeometry(110, 100, 200, 25);
    status.hide();
    status.setParent(this);
}

DialogZaDodavanjePrijatelja::~DialogZaDodavanjePrijatelja()
{
    delete ui;
}

void DialogZaDodavanjePrijatelja::posaljiInformaciju()
{
    emit salji(this->ui->lineEdit->text());
    this->close();
}

void DialogZaDodavanjePrijatelja::izbaciObavestenje(bool s)
{
    if(s){
        status.setText("Postoji takav Korisnik");
        status.setFont(QFont("Arial", 14, 3));
        status.setStyleSheet("background-color: rgba(255,255,255,0); color: rgb(0,255,0);");
        if(!status.isVisible())
            status.show();
    }else{
        status.setText("Ne postoji takav Korisnik");
        status.setFont(QFont("Arial", 14, 3));
        status.setStyleSheet("background-color: rgba(255,255,255,0); color: rgb(255,100,100);");
        if(!status.isVisible())
            status.show();
    }
}
