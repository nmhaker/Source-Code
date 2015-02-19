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

    if(trenutniAlat == Olovka)
    {
        QDataStream out(&kordinate, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);

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
    }else if(trenutniAlat == Gumica){
        QDataStream out(&kordinate, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << zaBrisanje;
        emit crtano(kordinate);
        qDebug() << "Poslat paket" << endl;
        qDebug() << kordinate << endl;
        out.device()->close();
        this->zaBrisanje.clear();
    }

    QWidget::mouseReleaseEvent(e);
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(pretisnutoDugme && trenutniAlat == Olovka){
        Pixel p;
        p.x = e->pos().x();
        p.y = e->pos().y();
        p.boja = this->bojaOlovke;
        dots.append(p);

        qDebug() << p.x << " , " << p.y << " , " << p.boja << endl;

    }else if(pretisnutoDugme && trenutniAlat == Gumica){

        qDebug() << "BRISEEM!" << endl;
        PixeliGumice p;
        p.x = e->pos().x() - 25;
        p.y = e->pos().y() - 25;
        p.w = 50;
        p.h = 50;

        zaBrisanje.append(p);

        //this->dbg->updateCoordinates(p.x,p.y,p.w,p.h);

        for(int i = 0; i < dots.count(); i++)
        {
            if((dots.at(i).x >= p.x && dots.at(i).x <=p.w+p.x) && (dots.at(i).y >= p.y && dots.at(i).y <= p.h+p.y))
            {
                dots.remove(i);
            }
        }
        for(int i = 0; i < dotsPrijatelja.count(); i++)
        {
            if((dotsPrijatelja.at(i).x >= p.x && dotsPrijatelja.at(i).x <=p.w+p.x) && (dotsPrijatelja.at(i).y >= p.y && dotsPrijatelja.at(i).y <= p.h+p.y))
            {
                dotsPrijatelja.remove(i);
            }
        }
    }

    this->repaint();

    QWidget::mouseMoveEvent(e);
}


void Widget::ubaciKordinate(QByteArray p)
{
    qDebug() << "Pristigao paket: " << endl;
    qDebug() << p << endl;

    QByteArray decoded(QByteArray::fromHex(p));

    QDataStream in(decoded);
    in.setVersion(QDataStream::Qt_5_3);

    int a;
    in >> a;

    if(a == Gumica)
    {
        QVector<PixeliGumice> pg;
        in >> pg;


        for(int ii = 0; ii < pg.count();ii++)
        {
            for(int i = 0; i < dots.count(); i++)
            {
                if((dots.at(i).x >= pg.at(ii).x && dots.at(i).x <=pg.at(ii).w+pg.at(ii).x) && (dots.at(i).y >= pg.at(ii).y && dots.at(i).y <= pg.at(ii).h+pg.at(ii).y))
                {
                    dots.remove(i);
                }
            }
        }
        for(int ii=0; ii < pg.count(); ii++)
        {
            for(int i = 0; i < dotsPrijatelja.count(); i++)
            {
                if((dotsPrijatelja.at(i).x >= pg.at(ii).x && dotsPrijatelja.at(i).x <=pg.at(ii).w+pg.at(ii).x) && (dotsPrijatelja.at(i).y >= pg.at(ii).y && dotsPrijatelja.at(i).y <= pg.at(ii).h+pg.at(ii).y))
                {
                    dotsPrijatelja.remove(i);
                }
            }
        }
        in.device()->close();
    }else if(a == Olovka)
    {
        QVector<Pixel> vektorPiksela;
        in >> vektorPiksela;

        for(int i=0; i < vektorPiksela.size(); i++)
        {
            dotsPrijatelja.append(vektorPiksela.at(i));
        }
        in.device()->close();
    }

    this->repaint();
}

void Widget::postaviBoju(QColor c)
{
    this->bojaOlovke = c;
}

void Widget::zapamtiCrtez()
{
    QPixmap pixmap(this->size());
    this->render(&pixmap);
    QDateTime d;
    QString dest = QFileDialog::getExistingDirectory();
    pixmap.save(dest + "/crtez_" + d.toString() + ".png");
    qDebug() << "Cuvam sliku u: " << dest + "/crtez_" + d.toString() + ".png";
}

void Widget::postaviAlat(Alat a)
{
    this->trenutniAlat = a;
}

QDataStream& operator<<(QDataStream& s, const QVector<Pixel>& v)
{
    s << Olovka;
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

QDataStream &operator<<(QDataStream &s, const QVector<PixeliGumice> &v)
{
    s << Gumica;
    s << quint32(v.size());

    for(int i=0;i < v.size();i++)
    {
        s << v.at(i).x;
        s << v.at(i).y;
        s << v.at(i).w;
        s << v.at(i).h;
    }
    return s;
}


QDataStream &operator>>(QDataStream &s, QVector<PixeliGumice> &v)
{

    v.clear();
    quint32 c;
    s >> c;
    v.resize(c);
    for(int i = 0; i < c;i++)
    {
        s >> v[i].x;
        s >> v[i].y;
        s >> v[i].w;
        s >> v[i].h;
    }

    return s;
}

