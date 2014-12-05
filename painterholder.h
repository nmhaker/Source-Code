#ifndef PAINTERHOLDER_H
#define PAINTERHOLDER_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QPushButton>

#include "widget.h"

class FormaZaPrimaoca;

class PainterHolder : public QWidget
{
    Q_OBJECT
public:
    explicit PainterHolder(QWidget *parent = 0, QString primaoc = "NONE");
    virtual ~PainterHolder();
protected:

    void resizeEvent(QResizeEvent *e);
    void keyPressEvent(QKeyEvent *);

private:
    Widget *ekranZaCrtanje;

    QString _primaoc;

    QTimer *tajmerZaKoordinate;

    FormaZaPrimaoca *form1;

    QPushButton *zatvoriButton;

signals:
    void saljiPaket(QByteArray paket, QString primaocPaketa);
    void zahtevZaKoordinate(QString primaoc);
    void gasenjeCrtaca();


public slots:

    void primiKordinate(QByteArray paket);
    void preusmeriSignal(QByteArray s);
    void posaljiZahtevZaKoordinate();

    void postaviPrimaoca(QString p);

};


#endif // PAINTERHOLDER_H
