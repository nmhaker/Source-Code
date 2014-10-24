#include "painterholder.h"

PainterHolder::PainterHolder(QWidget *parent, QString primaoc) :
    QWidget(parent)
{

    ekranZaCrtanje = new Widget(this);
    ekranZaCrtanje->show();

    _primaoc = primaoc;

    connect(this->ekranZaCrtanje, SIGNAL(crtano(QByteArray)), this, SIGNAL(saljiPaket(QByteArray, QString)));

    tajmerZaKoordinate.setInterval(500);
    connect(&tajmerZaKoordinate, SIGNAL(timeout()), this, SIGNAL(zahtevZaKoordinate(QString)));

    tajmerZaKoordinate.start();
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

