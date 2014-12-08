#include "statuswidget.h"

//DUGMEZACRTAC
DugmeZaCrtac::DugmeZaCrtac(QWidget *parent) : Dugmad(parent)
{

}

void DugmeZaCrtac::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pixmap(":/statusWidget/images/DugmeZaCrtac.jpg");
    painter.drawPixmap(QRect(1,1,48,49), pixmap.scaled(size()));

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
    this->setGeometry(mainWindowRect.width()-65,25,50,mainWindowRect.height()-44);
    this->setStyleSheet("background-color: black;");

    dugmeZaCrtac = new DugmeZaCrtac(this);
    dugmeZaCrtac->show();

    connect(dugmeZaCrtac, SIGNAL(clicked()), this, SIGNAL(dugmeZaCrtac_clicked()));

    this->mainWindowGeometry = mainWindowRect;

    this->setWindowFlags(Qt::FramelessWindowHint);

}

void StatusWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(Qt::green);
    painter.setBrush(Qt::black);
    painter.drawRect(rect());
    painter.drawLine(0,mainWindowGeometry.height()-45, 50,mainWindowGeometry.height()-45);
    QWidget::paintEvent(e);
}
