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
                painter.setPen(dotsPrijatelja.at(i).boja);
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
    out.setVersion(QDataStream::Qt_5_3);

//    out << dots.size()+1-poslednjiBrojDots;

//    for(int i=poslednjiBrojDots; i < dots.size() - poslednjiBrojDots; i++)
//    {
//        out << dots.at(i).x << dots.at(i).y << dots.at(i).boja;
//    }

    Pixel p;
    p.x = -100;
    p.y = 0;
    p.boja = Qt::black;
    dots.append(p);

    QVector<Pixel> novoDodavanje;

    for(int i=poslednjiBrojDots; i < dots.size(); i++)
    {
        novoDodavanje.append(dots.at(i));
    }

    out << novoDodavanje;

    qDebug() << "Poslato pixela: " << dots.size() << endl;

    emit crtano(kordinate);

    out.device()->close();

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

        qDebug() << p.x << " , " << p.y << " , " << p.boja << endl;
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

QDataStream& operator<<(QDataStream& s, const QVector<Pixel>& v)
{
    s << quint32(v.size());

    for (int i = 0; i < v.size(); i++)
    {
        s << v.at(i).x;
        s << v.at(i).y;
        s << v.at(i).boja;
    }
    return s;
}

QDataStream& operator>>(QDataStream& s, QVector<Pixel>& v)
{
    v.clear();
    quint32 c;
    s >> c;
    v.resize(c);
    for(int i = 0; i < c; i++) {
        s >> v[i].x;
        s >> v[i].y;
        s >> v[i].boja;
    }
    return s;
}

void Widget::ubaciKordinate(QByteArray p)
{
    QByteArray decoded(QByteArray::fromHex(p));

    QDataStream in(decoded);
    in.setVersion(QDataStream::Qt_5_3);

    qDebug() << "Pristigao paket" << endl;

    QVector<Pixel> vektorPiksela;

    in >> vektorPiksela;

    qDebug() << "Broj piksela za obradu je: " << vektorPiksela.size() << endl;

    for(int i=0; i < vektorPiksela.size(); i++)
    {
        dotsPrijatelja.append(vektorPiksela.at(i));
        qDebug() << vektorPiksela.at(i).x << " , " << vektorPiksela.at(i).y << " , " << vektorPiksela.at(i).boja;
    }

    in.device()->close();

    this->repaint();
}

void Widget::postaviBoju(QColor c)
{
    this->bojaOlovke = c;
}
