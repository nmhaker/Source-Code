#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>

#include <QDebug>
#include <QColor>
#include <QDateTime>
#include <QFileDialog>
#include "debugprozor.h"


namespace Ui {
class Widget;
}

struct Pixel{
    quint32 x;
    quint32 y;
    QColor boja;
};

struct PixeliGumice{
    quint32 x;
    quint32 y;
    quint32 w;
    quint32 h;
};


enum Alat{
    Olovka,
    Gumica
};

using namespace std;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    Ui::Widget *ui;

    QVector<Pixel> dots;
    QVector<Pixel> dotsPrijatelja;

    QVector<PixeliGumice> zaBrisanje;

    int poslednjiBrojDots;

    bool pretisnutoDugme;

    QColor bojaOlovke;

    QByteArray kordinate;

    Alat trenutniAlat = Olovka;

    DebugProzor *dbg;

signals:
    void crtano(QByteArray &paket);

public slots:

    void ubaciKordinate(QByteArray p);
    void postaviBoju(QColor c);
    void zapamtiCrtez();
//    void brisiKordinate();
    void postaviAlat(Alat a);
};

QDataStream& operator<<(QDataStream& s, const QVector<Pixel>& v);
QDataStream& operator>>(QDataStream& s, QVector<Pixel>& v);

QDataStream& operator<<(QDataStream& s, const QVector<PixeliGumice>& v);
QDataStream& operator>>(QDataStream& s, QVector<PixeliGumice>& v);

#endif // WIDGET_H

