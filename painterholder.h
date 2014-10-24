#ifndef PAINTERHOLDER_H
#define PAINTERHOLDER_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

#include "widget.h"



class PainterHolder : public QWidget
{
    Q_OBJECT
public:
    explicit PainterHolder(QWidget *parent = 0, QString primaoc = "NONE");
protected:

    void resizeEvent(QResizeEvent *e);

private:
    Widget *ekranZaCrtanje;

    QString _primaoc;

    QTimer tajmerZaKoordinate;

signals:
    void saljiPaket(QByteArray paket, QString primaocPaketa);
    void zahtevZaKoordinate(QString _primaoc);

public slots:

    void primiKordinate(QByteArray paket);

};

#endif // PAINTERHOLDER_H
