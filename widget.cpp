#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    pretisnutoDugme = false;
    bojaOlovke = Qt::blue;
    poslednjiBrojDots = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    //Paint pozadinu
    painter.setBrush(QBrush(QColor(30,30,30,255)));
    painter.drawRect(this->rect());

    //Crtaj kordinate korisnika i prijatelja
    for(int i=0; i < dots.count(); i++){
        if(i > 1){
            if(dots.at(i-1).x != -100 && dots.at(i).x != -100)
            {
                painter.setPen(dots.at(i-1).boja);
                painter.drawLine(QPoint(dots.at(i-1).x, dots.at(i-1).y), QPoint(dots.at(i).x,dots.at(i).y));
            }
        }else{
            if(dots.at(i).x != -100)
            {
                painter.setPen(dots.at(i).boja);
                painter.drawPoint(QPoint(dots.at(i).x, dots.at(i).y));
            }
        }
    }

    painter.setPen(QPen(Qt::red));
    for(int i=0; i < dotsPrijatelja.count(); i++){
        if(i > 1){
            if(dotsPrijatelja.at(i-1).x != -100 && dotsPrijatelja.at(i).x != -100)
            {
                painter.setPen(dotsPrijatelja.at(i-1).boja);
                painter.drawLine(QPoint(dotsPrijatelja.at(i-1).x, dotsPrijatelja.at(i-1).y), QPoint(dotsPrijatelja.at(i).x, dotsPrijatelja.at(i).y));
            }
        }else{
            if(dotsPrijatelja.at(i).x != -100)
            {
                painter.setPen(dotsPrijatelja.at(i-1).boja);
                painter.drawPoint(QPoint(dotsPrijatelja.at(i).x, dotsPrijatelja.at(i).y));
            }
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

    QDataStream out(&kordinate, QIODevice::WriteOnly);

    out << dots.size()+1-poslednjiBrojDots;
    qDebug() << "Ukupan broj tacaka spremnih za obradu je: " << dots.size()-poslednjiBrojDots+1 << endl;

    foreach(Pixel tacka, dots){
        out << tacka.x;
        out << tacka.y;
        out << tacka.boja;
        qDebug() << "Unutar foreach" << endl;
    }

    Pixel p;
    p.x = -100;
    p.y = 0;
    p.boja = Qt::black;
    dots.append(p);

    out << p.x;
    out << p.y;
    out << p.boja;
    qDebug() << "Size paketa pre samoga slanja je : " << kordinate.size();
    out.device()->reset();
    out.device()->close();

    emit crtano(kordinate);

    poslednjiBrojDots = dots.size();

    QWidget::mouseReleaseEvent(e);
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(pretisnutoDugme){
        Pixel p;
        p.x = e->pos().x();
        p.y = e->pos().y();
        p.boja = this->bojaOlovke;
        dots.append(p);
    }

    this->repaint();

    QWidget::mouseMoveEvent(e);
}

void Widget::resizeEvent(QResizeEvent *e)
{
//    this->setGeometry(0,0,e->size().width()-200, e->size().height());

    QWidget::resizeEvent(e);
}

void Widget::checkData()
{

}

void Widget::ubaciKordinate(QByteArray p)
{
    QByteArray paket(p);
    QDataStream in(&paket, QIODevice::ReadOnly);

    int brojPiksela;
    in >> brojPiksela;

    qDebug() << "Broj piksela za crtanje je: " << brojPiksela;

    for(int i=0; i < brojPiksela; i++)
    {
        Pixel p;
        in >> p.x >> p.y >> p.boja;
        qDebug() << "P.x: " << p.x << "P.y: " << p.y << "P.boja: " << p.boja << endl;
        dotsPrijatelja.append(p);
    }

    in.device()->close();

    this->repaint();
}

void Widget::postaviBoju(QColor c)
{
    this->bojaOlovke = c;
}
