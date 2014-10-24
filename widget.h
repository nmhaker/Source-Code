#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>

#include <QDebug>

namespace Ui {
class Widget;
}

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
    void keyPressEvent(QKeyEvent *);
private:
    Ui::Widget *ui;

    QVector<QPoint> dots;
    QVector<QPoint> dotsPrijatelja;

    QByteArray kordinate;

    bool pretisnutoDugme;

    void checkData();

signals:
    void crtano(QByteArray paket);

public slots:

    void readDataFromSocket();
    void ubaciKordinate(QByteArray paket);
};

#endif // WIDGET_H
