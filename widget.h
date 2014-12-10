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
    int x;
    int y;
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

    QByteArray kordinate;

    bool pretisnutoDugme;

    void checkData();

    QColor bojaOlovke;

signals:
    void crtano(QByteArray paket);

public slots:

    void ubaciKordinate(QByteArray p);
    void postaviBoju(QColor c);
};

#endif // WIDGET_H
