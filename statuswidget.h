#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPainter>

//Abstraktna klasa za dugmice :)
class Dugmad : public QWidget{
    Q_OBJECT
public:
    explicit Dugmad(QWidget *parent = 0);
protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

    QLinearGradient lg;
private:

signals:
    void clicked();
};

//Dugme za paljenje crtaca
class DugmeZaCrtac : public Dugmad{
    Q_OBJECT
public:
    explicit DugmeZaCrtac(QWidget *parent = 0);
protected:

    void paintEvent(QPaintEvent *e);

private:

};

//STATUSWIDGET
class StatusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatusWidget(QWidget *parent = 0, QRect mainWindowRect = QRect());

signals:
    void dugmeZaCrtac_clicked();

public slots:
    void promeniPoziciju(QPoint p);

private:
    QRect mainWindowGeometry;
    QWidget *widgetZaFarbanjeGoregKvadrata;

    DugmeZaCrtac *dugmeZaCrtac;
};

#endif // STATUSWIDGET_H
