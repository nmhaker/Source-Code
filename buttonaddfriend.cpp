#include "buttonaddfriend.h"

ButtonAddFriend::ButtonAddFriend(QWidget *parent) :
    QPushButton(parent)
{
    this->setGeometry(parent->width()-30,0,30,parent->height());
}

void ButtonAddFriend::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 5,5));
    painter.drawLine(15,7,15,this->height()-7);
    painter.drawLine(7,15,23,15);
}
