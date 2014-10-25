#ifndef PAINTERHOLDER_H
#define PAINTERHOLDER_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

#include "widget.h"

class FormaZaPrimaoca;

class PainterHolder : public QWidget
{
    Q_OBJECT
public:
    explicit PainterHolder(QWidget *parent = 0, QString primaoc = "NONE");
    ~PainterHolder();
protected:

    void resizeEvent(QResizeEvent *e);

private:
    Widget *ekranZaCrtanje;

    QString _primaoc;

    QTimer tajmerZaKoordinate;

    FormaZaPrimaoca *form1;

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

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class FormaZaPrimaoca : public QWidget
{
    Q_OBJECT
public:
    explicit FormaZaPrimaoca(QWidget *parent = 0);
    ~FormaZaPrimaoca();

    QLabel *label1;
    QLineEdit *line_edit1;
    QPushButton *push_button1;

signals:
    void emitujImePrimaoca(QString d);
private slots:
    void posaljiImePrimaoca();
};

#endif // PAINTERHOLDER_H
