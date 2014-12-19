#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>

#include <QDebug>
#include <QColor>

namespace Ui {
class Widget;
}

struct Pixel{
    quint32 x;
    quint32 y;
    QColor boja;
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
    void resizeEvent(QResizeEvent *);

private:
    Ui::Widget *ui;

    QVector<Pixel> dots;
    QVector<Pixel> dotsPrijatelja;

    int poslednjiBrojDots;

    bool pretisnutoDugme;

    void checkData();

    QColor bojaOlovke;

    QByteArray kordinate;

signals:
    void crtano(QByteArray &paket);

public slots:

    void ubaciKordinate(QByteArray p);
    void postaviBoju(QColor c);
};

QDataStream& operator<<(QDataStream& s, const QVector<Pixel>& v);
QDataStream& operator>>(QDataStream& s, QVector<Pixel>& v);

#endif // WIDGET_H

