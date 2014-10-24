#include "painterscreen.h"

PainterScreen::PainterScreen(QWidget *parent) :
    QWidget(parent)
{
    this->pretisnutoDugme = false;
}

void PainterScreen::mousePressEvent(QMouseEvent *e)
{
    pretisnutoDugme = true;
}

void PainterScreen::mouseReleaseEvent(QMouseEvent *e)
{
    pretisnutoDugme = false;
}

void PainterScreen::mouseMoveEvent(QMouseEvent *e)
{
    tacke.append(e->pos());
}
