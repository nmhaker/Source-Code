#include "splashscreen.h"

SplashScreen::SplashScreen(QWidget *parent) :
    QWidget(parent)
{

    this->setGeometry(0,0,500,100);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x, y);

    this->setStyleSheet("background-color: qlineargradient(spread:reflect, x1:0.498, y1:0.510955, x2:0.492, y2:0, stop:0 rgba(30,30,30,255), stop:1 rgba(0,0,0, 255));");

    tajmer.setSingleShot(true);
    tajmer.setInterval(2000);

    connect(&tajmer, SIGNAL(timeout()), this, SLOT(zatvoriSplashScreen()));

    tajmer.start();
}

void SplashScreen::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::green));
    painter.setFont(QFont("Times New Roman", 25));
    painter.drawText(this->width()/2-70,this->height()/2+10, "Chat&Paint");
    painter.setFont(QFont("Times New Roman", 15));
    painter.drawText(this->width()-220, this->height()-5, "Autor: Nikola Milutinovic");
    QWidget::paintEvent(e);
}

void SplashScreen::zatvoriSplashScreen()
{
    tajmer.stop();
    mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}
