#include "pomerac.h"

Pomerac::Pomerac(QWidget *parent) :
    QWidget(parent)
{
    this->setGeometry(0,0,parent->width(),25);

    //this->setWindowFlags(Qt::FramelessWindowHint);
    setajuciTekst.setStyleSheet("background-color: qlineargradient(spread:reflect, x1:0.54, y1:0.510955, x2:0.545, y2:0, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(121, 121, 121, 255));color:blue");
    setajuciTekst.setGeometry(0,0,this->width(),this->height());
    setajuciTekst.setAlignment(Qt::AlignCenter);
    setajuciTekst.setFont(QFont("Arial", 20));
    setajuciTekst.setText("Messenger-Painter");
    setajuciTekst.setParent(this);
    setajuciTekst.show();

}

void Pomerac::mousePressEvent(QMouseEvent *event)
{
    event->accept(); // do not propagate
        if (isWindow())
            offset = event->globalPos() - pos();
        else
            offset = event->pos();
    QWidget::mousePressEvent(event);
}

void Pomerac::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept(); // do not propagate
        offset = QPoint();
    QWidget::mouseReleaseEvent(event);
}

void Pomerac::mouseMoveEvent(QMouseEvent *event)
{
    event->accept(); // do not propagate
        if (isWindow())
            emit pozicijaPromenjena(event->globalPos() - offset);
        else
            emit pozicijaPromenjena(event->globalPos() - offset); //mapToParent(event->pos()
        QWidget::mouseMoveEvent(event);
}

void Pomerac::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush brush;
    brush.setColor(Qt::black);
    painter.drawRect(0,0,this->width(),this->height());

    QWidget::paintEvent(event);
}

