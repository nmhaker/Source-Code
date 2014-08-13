#include "pomerac.h"

Pomerac::Pomerac(QWidget *parent) :
    QWidget(parent)
{
    this->setGeometry(0,0,65,25);
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x - 200, y - 100);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("background-color:rgb(106, 106, 106);");

    text.setParent(this);
    text.setText("Move Me");
    text.setStyleSheet("color:white;");
    text.setGeometry(5,5, 75,15);
    text.show();

}

void Pomerac::mousePressEvent(QMouseEvent *event)
{
    event->accept(); // do not propagate
        if (isWindow())
            offset = event->globalPos() - pos();
        else
            offset = event->pos();
}

void Pomerac::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept(); // do not propagate
        offset = QPoint();
}

void Pomerac::mouseMoveEvent(QMouseEvent *event)
{
    event->accept(); // do not propagate
        if (isWindow())
            move(event->globalPos() - offset);
        else
            move(mapToParent(event->pos() - offset));
    emit pozicijaPromenjena();
}

