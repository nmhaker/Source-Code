#include "painterholder.h"

PainterHolder::PainterHolder(QWidget *parent, QString primaoc) :
    QWidget(parent)
{
    this->setMinimumSize(600,600);

    ekranZaCrtanje = new Widget(this);
    ekranZaCrtanje->setGeometry(0,0,this->width(), this->height());

    panel = new PanelKontrola(this);
    panel->setGeometry(this->width()/2 - 100,5,200,50);

    connect(panel, SIGNAL(izabranaBoja(QColor)), this, SLOT(primiBojuOlovke(QColor)));

    connect(panel, SIGNAL(zapamtiCrtez()), this->ekranZaCrtanje, SLOT(zapamtiCrtez()));

    _primaoc = primaoc;

    connect(this->ekranZaCrtanje, SIGNAL(crtano(QByteArray&)), this, SLOT(preusmeriSignal(QByteArray&)));

    tajmerZaKoordinate = new QTimer();
    tajmerZaKoordinate->setInterval(1000);
    connect(tajmerZaKoordinate, SIGNAL(timeout()), this, SLOT(posaljiZahtevZaKoordinate()));

    tajmerZaKoordinate->start();

    this->showMaximized();
}

PainterHolder::~PainterHolder()
{
    tajmerZaKoordinate->stop();
}

void PainterHolder::resizeEvent(QResizeEvent *e)
{
    this->ekranZaCrtanje->resize(e->size().width(),e->size().height());
    this->panel->setGeometry(e->size().width()/2 -100,5,200,50);

    QWidget::resizeEvent(e);
}

void PainterHolder::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        this->tajmerZaKoordinate->stop();

    QWidget::keyPressEvent(e);
}

void PainterHolder::closeEvent(QCloseEvent *e)
{
    emit gasenjeCrtaca();
    this->tajmerZaKoordinate->stop();
    QWidget::closeEvent(e);
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
    this->boja = QColor(0,0,255,255);

    QPixmap p_pick(":/dugmadi/images/pick_color_icon.png");

    QIcon icon_pick_color(p_pick.scaled(50,50));

    izaberiBoju = new QPushButton(this);
    izaberiBoju->setIcon(icon_pick_color);
    izaberiBoju->setGeometry(0,0,50,50);
    connect(izaberiBoju, SIGNAL(clicked()), this, SLOT(prikaziColorDialog()));

//    label = new QLabel("Boja:", this);
//    label->setGeometry(20,25, 40, 25);
//    label->setStyleSheet("text: rgb(255,255,255);");
//    label->show();

    colorShown = new QWidget(this);
    colorShown->setGeometry(50,0,100,50);
    colorShown->setStyleSheet("background-color: rgba(" + QString::number(this->boja.red()) + "," + QString::number(this->boja.green()) + "," + QString::number(this->boja.blue()) + "," + QString::number(this->boja.alpha()) + ");" );

    saveImage = new QPushButton(this);

    QPixmap p_save(":/dugmadi/images/save_icon.png");

    QIcon icon_save_image(p_save.scaled(50,50));
    saveImage->setIcon(icon_save_image);

    saveImage->setGeometry(150,0,50,50);
    connect(saveImage, SIGNAL(clicked()), this, SIGNAL(zapamtiCrtez()));
}

void PanelKontrola::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setBrush(QColor(255,255,255,0));

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
    this->colorDialog->setFocus();

    connect(colorDialog, SIGNAL(colorSelected(QColor)), this, SIGNAL(izabranaBoja(QColor)));
    connect(colorDialog, SIGNAL(colorSelected(QColor)), this, SLOT(postaviBoju(QColor)));

}

void PanelKontrola::postaviBoju(QColor c)
{
    this->boja = c;
    colorShown->setStyleSheet("background-color: rgba(" + QString::number(this->boja.red()) + "," + QString::number(this->boja.green()) + "," + QString::number(this->boja.blue()) + "," + QString::number(this->boja.alpha()) + ");" );
}
