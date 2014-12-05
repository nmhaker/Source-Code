#include "painterholder.h"

PainterHolder::PainterHolder(QWidget *parent, QString primaoc) :
    QWidget(parent)
{

    ekranZaCrtanje = new Widget(this);
    ekranZaCrtanje->show();

    zatvoriButton = new QPushButton("Zatvori prozor", this);
    zatvoriButton->move(this->width()/2 - this->zatvoriButton->width()/2, this->height()-this->zatvoriButton->height());
    connect(zatvoriButton, SIGNAL(clicked()), this, SLOT(deleteLater()));
    _primaoc = primaoc;

    if(_primaoc == 0){
        form1 = new FormaZaPrimaoca(this);
        form1->move(this->x() + 30, this->y() + 30);
        connect(form1, SIGNAL(emitujImePrimaoca(QString)), this, SLOT(postaviPrimaoca(QString)));
    }else
        _primaoc = primaoc;

    connect(this->ekranZaCrtanje, SIGNAL(crtano(QByteArray)), this, SLOT(preusmeriSignal(QByteArray)));

    tajmerZaKoordinate = new QTimer(this);
    tajmerZaKoordinate->setInterval(1000);
    connect(tajmerZaKoordinate, SIGNAL(timeout()), this, SLOT(posaljiZahtevZaKoordinate()));

    tajmerZaKoordinate->start();

    //this->setWindowFlags(Qt::FramelessWindowHint);
}

PainterHolder::~PainterHolder()
{
    disconnect(tajmerZaKoordinate, SIGNAL(timeout()), this, SLOT(posaljiZahtevZaKoordinate()));
    tajmerZaKoordinate->stop();
    delete tajmerZaKoordinate;
    emit gasenjeCrtaca();
}

void PainterHolder::resizeEvent(QResizeEvent *e)
{
    this->ekranZaCrtanje->resize(this->width(), this->height());

    QWidget::resizeEvent(e);
}

void PainterHolder::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        this->tajmerZaKoordinate->stop();

    QWidget::keyPressEvent(e);
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
    if(tajmerZaKoordinate->isActive()){
        if(_primaoc != "")
            emit zahtevZaKoordinate(_primaoc);
        else{
            qDebug() << "GRESKA: nije definisan _primaoc u PainterHolder-u" << endl;
            tajmerZaKoordinate->stop();
        }
    }
}

void PainterHolder::postaviPrimaoca(QString p)
{
    this->_primaoc = p;
    tajmerZaKoordinate->start();
}

