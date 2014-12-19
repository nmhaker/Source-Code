#include "painterholder.h"

PainterHolder::PainterHolder(QWidget *parent, QString primaoc) :
    QWidget(parent)
{
    this->setMinimumSize(600,600);

    panel = new PanelKontrola(this);
    panel->setGeometry(this->width()-200,0,200,this->height());

    connect(panel, SIGNAL(izabranaBoja(QColor)), this, SLOT(primiBojuOlovke(QColor)));

    ekranZaCrtanje = new Widget(this);
    ekranZaCrtanje->setGeometry(0,0,this->width() - panel->width(), this->height());


    zatvoriButton = new QPushButton("Zatvori prozor", this->panel);
    zatvoriButton->move(0,this->height()-zatvoriButton->height());
    connect(zatvoriButton, SIGNAL(clicked()), this, SLOT(deleteLater()));

    connect(panel, SIGNAL(zapamtiCrtez()), this->ekranZaCrtanje, SLOT(zapamtiCrtez()));

    _primaoc = primaoc;

    connect(this->ekranZaCrtanje, SIGNAL(crtano(QByteArray&)), this, SLOT(preusmeriSignal(QByteArray&)));

    tajmerZaKoordinate = new QTimer(this);
    tajmerZaKoordinate->setInterval(1000);
    connect(tajmerZaKoordinate, SIGNAL(timeout()), this, SLOT(posaljiZahtevZaKoordinate()));

    tajmerZaKoordinate->start();

    this->showMaximized();
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
    this->ekranZaCrtanje->resize(e->size().width()-200,e->size().height());
    this->panel->setGeometry(e->size().width()-200,0,200,e->size().height());

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

void PainterHolder::preusmeriSignal(QByteArray &s)
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

void PainterHolder::primiBojuOlovke(QColor c)
{
    this->ekranZaCrtanje->postaviBoju(c);
}

//PANELKONTROLA

PanelKontrola::PanelKontrola(QWidget *parent) : QWidget(parent)
{
    izaberiBoju = new QPushButton("Izaberi Boju", this);
    izaberiBoju->setGeometry(0,0,200,25);
    connect(izaberiBoju, SIGNAL(clicked()), this, SLOT(prikaziColorDialog()));

    saveImage = new QPushButton(this);
    saveImage->setGeometry(0,25,200,25);
    connect(saveImage, SIGNAL(clicked()), this, SIGNAL(zapamtiCrtez()));


}

void PanelKontrola::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::red));

    painter.drawRect(0,0,this->width(),this->height());

    QWidget::paintEvent(e);
}

void PanelKontrola::enterEvent(QEvent *e)
{
    qDebug() << "Unutar Panela Kontrola" << endl;
    QWidget::enterEvent(e);
}

void PanelKontrola::prikaziColorDialog()
{
    this->colorDialog = new QColorDialog();
    this->colorDialog->show();

    connect(colorDialog, SIGNAL(colorSelected(QColor)), this, SIGNAL(izabranaBoja(QColor)));
}
