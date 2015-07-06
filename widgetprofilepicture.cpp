#include "widgetprofilepicture.h"

WidgetProfilePicture::WidgetProfilePicture(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(QRect(0,0,100,100));
    this->profileImage = QImage(":/profil/images/noImg.jpg");
}

void WidgetProfilePicture::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawImage(this->rect(), this->profileImage);

    QWidget::paintEvent(e);
}

void WidgetProfilePicture::mousePressEvent(QMouseEvent *e)
{
    QString fileName = QFileDialog::getOpenFileName(0, "Izaberite sliku", "Documents", "(*.bmp, *.jpg)");
    this->profileImage = QImage(fileName);
    this->repaint();
    QWidget::mousePressEvent(e);
}
