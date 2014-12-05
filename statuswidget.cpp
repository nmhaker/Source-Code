#include "statuswidget.h"

Dugmad::Dugmad(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0,0,50,50);
    lg.setColorAt(0, QColor(58,58,58,178));
    lg.setColorAt(1, QColor(14,255,10,185));
}

void Dugmad::paintEvent(QPaintEvent *e)
{

    QWidget::paintEvent(e);
}

void Dugmad::enterEvent(QEvent *e)
{
    lg.setColorAt(0, QColor(48,48,48,178));
    lg.setColorAt(1, QColor(4,245,0,185));
    repaint();

    QWidget::enterEvent(e);
}

void Dugmad::leaveEvent(QEvent *e)
{
    lg.setColorAt(0, QColor(58,58,58,178));
    lg.setColorAt(1, QColor(14,255,10,185));
    repaint();

    QWidget::leaveEvent(e);
}

void Dugmad::mousePressEvent(QMouseEvent *e)
{
    lg.setColorAt(0, QColor(58,58,58,178));
    lg.setColorAt(1, QColor(0,200,0,185));
    repaint();
    QWidget::mousePressEvent(e);
}

void Dugmad::mouseReleaseEvent(QMouseEvent *e)
{
    lg.setColorAt(0, QColor(48,48,48,178));
    lg.setColorAt(1, QColor(4,245,0,185));
    repaint();

    emit clicked();

    QWidget::mouseReleaseEvent(e);
}

//DUGMEZACRTAC
DugmeZaCrtac::DugmeZaCrtac(QWidget *parent) : Dugmad(parent)
{

}

void DugmeZaCrtac::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pixmap(":/statusWidget/images/DugmeZaCrtac.jpg");
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
//STATUSWIDGET
StatusWidget::StatusWidget(QWidget *parent, QRect mainWindowRect) :
    QWidget(parent)
{
    this->setGeometry(mainWindowRect.x() + mainWindowRect.width()+ 5,mainWindowRect.y(),50,mainWindowRect.height());
    this->setStyleSheet("background-color: black;");

    widgetZaFarbanjeGoregKvadrata = new QWidget(this);
    widgetZaFarbanjeGoregKvadrata->setStyleSheet("background-color: rgb(200,200,200);");
    widgetZaFarbanjeGoregKvadrata->setGeometry(0,0,50,25);

    dugmeZaCrtac = new DugmeZaCrtac(this);
    dugmeZaCrtac->move(0,25);
    dugmeZaCrtac->show();

    connect(dugmeZaCrtac, SIGNAL(clicked()), this, SIGNAL(dugmeZaCrtac_clicked()));

    this->mainWindowGeometry = mainWindowRect;

    this->setWindowFlags(Qt::FramelessWindowHint);

}

void StatusWidget::promeniPoziciju(QPoint p)
{
    this->move(p.x() + mainWindowGeometry.x() + 35 , p.y());
}
