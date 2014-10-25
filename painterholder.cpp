#include "painterholder.h"

PainterHolder::PainterHolder(QWidget *parent, QString primaoc) :
    QWidget(parent)
{

    ekranZaCrtanje = new Widget(this);
    ekranZaCrtanje->show();

    if(_primaoc == 0){
        form1 = new FormaZaPrimaoca(this);
        form1->move(this->x() + 30, this->y() + 30);
        connect(form1, SIGNAL(emitujImePrimaoca(QString)), this, SLOT(postaviPrimaoca(QString)));
    }else
        _primaoc = primaoc;

    connect(this->ekranZaCrtanje, SIGNAL(crtano(QByteArray)), this, SLOT(preusmeriSignal(QByteArray)));

    tajmerZaKoordinate.setInterval(1000);
    connect(&tajmerZaKoordinate, SIGNAL(timeout()), this, SLOT(posaljiZahtevZaKoordinate()));

    tajmerZaKoordinate.start();
}

PainterHolder::~PainterHolder()
{
    tajmerZaKoordinate.stop();
    emit gasenjeCrtaca();
}

void PainterHolder::resizeEvent(QResizeEvent *e)
{
    this->ekranZaCrtanje->resize(this->width(), this->height());

    QWidget::resizeEvent(e);
}

void PainterHolder::primiKordinate(QByteArray paket)
{
    this->ekranZaCrtanje->ubaciKordinate(paket);
}

void PainterHolder::preusmeriSignal(QByteArray s)
{
    emit saljiPaket(s, _primaoc);
}

void PainterHolder::posaljiZahtevZaKoordinate()
{
    if(_primaoc != "")
        emit zahtevZaKoordinate(_primaoc);
    else{
        qDebug() << "GRESKA: nije definisan _primaoc u PainterHolder-u" << endl;
        tajmerZaKoordinate.stop();
    }
}

void PainterHolder::postaviPrimaoca(QString p)
{
    this->_primaoc = p;
    tajmerZaKoordinate.start();
}


//KLASA FORMAZAPRIMAOCA--------


FormaZaPrimaoca::FormaZaPrimaoca(QWidget *parent) : QWidget(parent)
{

    label1 = new QLabel("Unesite ime primaoca", this);
    line_edit1 = new QLineEdit(this);
    push_button1 = new QPushButton("Ok", this);

    label1->setGeometry(20,100,200,50);
    line_edit1->setGeometry(240,100,200,50);
    push_button1->setGeometry(200,220,100,50);

    connect(this->push_button1, SIGNAL(clicked()), this, SLOT(posaljiImePrimaoca()));
}

FormaZaPrimaoca::~FormaZaPrimaoca()
{
    delete label1;
    delete line_edit1;
    delete push_button1;
}

void FormaZaPrimaoca::posaljiImePrimaoca()
{
    emit emitujImePrimaoca(this->line_edit1->text());

    this->close();
}
