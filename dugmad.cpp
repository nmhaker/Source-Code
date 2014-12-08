#include "dugmad.h"

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
