#ifndef LISTVIEWZAPORUKE_H
#define LISTVIEWZAPORUKE_H

#include <QListView>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

#include "dugmad.h"

class ClearDugme : public Dugmad{

    Q_OBJECT

public:
    explicit ClearDugme(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *e);
private:

signals:

public slots:

};

class Meni : public QWidget{
    Q_OBJECT

public:
    explicit Meni(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);

private:
   ClearDugme *dugmeZaBrisanje;

signals:
   void clearClicked();
};

class ListViewZaPoruke : public QListView
{
    Q_OBJECT
public:
    explicit ListViewZaPoruke(QWidget *parent = 0);
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void leaveEvent(QEvent *e);

private:
    Meni *meni;

signals:
    void obrisiCet();

public slots:

};

#endif // LISTVIEWZAPORUKE_H
