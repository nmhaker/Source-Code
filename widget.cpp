#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    pretisnutoDugme = false;

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::white));
    for(int i=0; i < dots.count(); i++){
        if(i > 1){
            if(dots.at(i-1).x() != -100 && dots.at(i).x() != -100)
                painter.drawLine(dots.at(i-1), dots.at(i));
        }else{
            if(dots.at(i).x() != -100)
                painter.drawPoint(dots.at(i));
        }
    }

    painter.setPen(QPen(Qt::red));
    for(int i=0; i < dotsPrijatelja.count(); i++){
        if(i > 1){
            if(dotsPrijatelja.at(i-1).x() != -100 && dotsPrijatelja.at(i).x() != -100)
                painter.drawLine(dotsPrijatelja.at(i-1), dotsPrijatelja.at(i));
        }else{
            if(dotsPrijatelja.at(i).x() != -100)
                painter.drawPoint(dotsPrijatelja.at(i));
        }
    }

    QWidget::paintEvent(e);
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    pretisnutoDugme = true;

    QWidget::mousePressEvent(e);
}

void Widget::mouseReleaseEvent(QMouseEvent *e)
{
    pretisnutoDugme = false;
    dots.append(QPoint(-100,0));

    QString delimiter("%");

    kordinate.append(QString::number(-100)).append(delimiter);
    kordinate.append(QString::number(-100)).append(delimiter);

//    tcpSocketZaSlanje->write(kordinate);
//    if(!tcpSocketZaSlanje->flush())
//        qDebug() << tcpSocketZaSlanje->errorString() << endl;

    emit crtano(kordinate);

    kordinate.clear();

    QWidget::mouseReleaseEvent(e);
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(pretisnutoDugme){
        dots.append(e->pos());

        QString delimiter("%");

        qDebug() << "X = " << e->x() << endl;
        qDebug() << "Y = " << e->y() << endl;
        kordinate.append(QString::number(e->x())).append(delimiter);
        kordinate.append(QString::number(e->y())).append(delimiter);

    }

    this->repaint();

    QWidget::mouseMoveEvent(e);
}

void Widget::keyPressEvent(QKeyEvent *e)
{
//    if(e->key() == Qt::Key_F1){
//        QHostAddress address("178.221.227.87");
//        this->tcpSocketZaSlanje->connectToHost(address,4900);
//    }
//    else if(e->key() == Qt::Key_F2){
//        this->dots.clear();
//        this->dotsPrijatelja.clear();
//    }


    QWidget::keyPressEvent(e);
}

void Widget::checkData()
{

}


void Widget::readDataFromSocket()
{
    QByteArray ba; //= socketHandle->readLine();

    qDebug() <<  "Citam podatke socketa: " << ba << endl;

    int brojTacaka;
    QList<QString> listaTacaka;
    QString tacka;
    for(int i=0;i<ba.size();i++){
        if(ba.at(i) != '%')
            tacka.append(ba.at(i));
        else{
            listaTacaka.append(tacka);
            brojTacaka++;
            tacka.clear();
        }
    }

    int counter = 0;
    int iks;
    int ipsilon;

    for(int i=0; i < listaTacaka.count(); i++){
        if(i % 2 == 0){
            iks = listaTacaka.at(i).toInt();
            counter++;
        }else{
            ipsilon = listaTacaka.at(i).toInt();
            counter++;
        }
        if(counter == 2){
            dotsPrijatelja.append(QPoint(iks, ipsilon));
            counter = 0;
        }
    }

    this->repaint();
}

void Widget::ubaciKordinate(QByteArray paket)
{
    int brojTacaka;
    QList<QString> listaTacaka;
    QString tacka;
    for(int i=0;i<paket.size();i++){
        if(paket.at(i) != '%')
            tacka.append(paket.at(i));
        else{
            listaTacaka.append(tacka);
            brojTacaka++;
            tacka.clear();
        }
    }

    int counter = 0;
    int iks;
    int ipsilon;

    for(int i=0; i < listaTacaka.count(); i++){
        if(i % 2 == 0){
            iks = listaTacaka.at(i).toInt();
            counter++;
        }else{
            ipsilon = listaTacaka.at(i).toInt();
            counter++;
        }
        if(counter == 2){
            dotsPrijatelja.append(QPoint(iks, ipsilon));
            counter = 0;
        }
    }

    this->repaint();
}
