#include "listviewzaporuke.h"

ListViewZaPoruke::ListViewZaPoruke(QWidget *parent) :
    QListView(parent)
{
    meni = new Meni(this);
    meni->move(270,160);
    meni->hide();
    connect(meni, SIGNAL(clearClicked()), this, SIGNAL(obrisiCet()));
    this->setMouseTracking(true);
}

void ListViewZaPoruke::mouseMoveEvent(QMouseEvent *e)
{
    if(e->pos().x() > this->width() - 100 && e->pos().y() > this->height() - 50)
    {
        meni->show();
    }
    else
    {
        meni->hide();
    }

    QListView::mouseMoveEvent(e);
}

void ListViewZaPoruke::leaveEvent(QEvent *e)
{
    meni->hide();

    QListView::leaveEvent(e);
}

//CLEARDUGME

ClearDugme::ClearDugme(QWidget *parent) : Dugmad(parent)
{
    this->setGeometry(0,0,50,50);
}

void ClearDugme::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pixmap(":/dugmadi/images/DugmeZaBrisanje.jpg");
    painter.drawPixmap(this->rect(), pixmap.scaled(size()));

    lg.setStart(0.505909, 0.505);
    lg.setFinalStop(0.511, 0);
    lg.setSpread(QLinearGradient::ReflectSpread);

    painter.save();
    painter.setBrush(QBrush(lg));
    painter.drawRect(rect());
    painter.restore();

    Dugmad::paintEvent(e);
}

//MENI

Meni::Meni(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0, 0, 50, 50);
    this->setWindowFlags(Qt::FramelessWindowHint);
    dugmeZaBrisanje = new ClearDugme(this);
    connect(dugmeZaBrisanje, SIGNAL(clicked()), this, SIGNAL(clearClicked()));
    dugmeZaBrisanje->show();
}

void Meni::paintEvent(QPaintEvent *e)
{

    QWidget::paintEvent(e);
}
