#include "splashscreen.h"

SplashScreen::SplashScreen(QWidget *parent) :
    QWidget(parent)
{


    this->setGeometry(0,0,500,350);
    this->setWindowFlags(Qt::FramelessWindowHint);
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x, y);

//    this->layout = new QGridLayout(this);
//    this->setLayout(layout);

    QPushButton *dugme = new QPushButton(this);
//    layout->addWidget(dugme);

    dugme->setGeometry(this->width()/2-50, this->height()/2-25, 100,50);
    dugme->setStyleSheet(":active{"
                         "background-color: qlineargradient(spread:reflect, x1:0.469, y1:0.522682, x2:0.469, y2:0, stop:0.473958 rgba(25, 25, 25, 255), stop:1 rgba(67, 67, 67, 255));"
                         "color:green;"
                         "}"
                         ":hover{"
                         "background-color:red; "
                         "color:black"
                         "}");
    dugme->setText("Messenger");

    connect(dugme, SIGNAL(clicked()), this, SLOT(zatvoriSplashScreen()));

    tajmer.setSingleShot(true);
    tajmer.setInterval(5000);

    connect(&tajmer, SIGNAL(timeout()), this, SLOT(zatvoriSplashScreen()));

    tajmer.start();



}

void SplashScreen::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(QRect(0,0, this->width()/2, this->height()), QPixmap(":/pozadina/images/screenshot.jpg").scaled(size()), QRect(0,0,this->width()/2, this->height()));
    painter.drawPixmap(QRect(this->width()/2, 0, this->width(), this->height()), QPixmap(":/pozadina/images/screenshot.jpg").scaled(size()), QRect(this->width()/2, 0, this->width(), this->height()));
    QWidget::paintEvent(e);
}

void SplashScreen::zatvoriSplashScreen()
{
    tajmer.stop();
    mainWindow = new MainWindow();
    mainWindow->show();
    this->close();

}
