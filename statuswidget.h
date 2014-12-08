#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QPainter>

#include "dugmad.h"

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

protected:
    void paintEvent(QPaintEvent *);
signals:
    void dugmeZaCrtac_clicked();

public slots:


private:
    QRect mainWindowGeometry;

    DugmeZaCrtac *dugmeZaCrtac;
};

#endif // STATUSWIDGET_H
