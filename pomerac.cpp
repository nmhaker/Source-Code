#include "pomerac.h"

Pomerac::Pomerac(QWidget *parent) :
    QWidget(parent)
{
    this->setGeometry(0,0,parent->width(),25);
    //this->setWindowFlags(Qt::FramelessWindowHint);
    setajuciTekst.setStyleSheet("background-color: rgba(200,200,200,1);color:black");
    setajuciTekst.setGeometry(0,0,this->width(),this->height());
    setajuciTekst.setAlignment(Qt::AlignCenter);
    setajuciTekst.setFont(QFont("Arial", 15));
    setajuciTekst.setText("Messenger");
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

