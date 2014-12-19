#ifndef PAINTERHOLDER_H
#define PAINTERHOLDER_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QHBoxLayout>
#include <QColorDialog>

#include "widget.h"

class PanelKontrola : public QWidget
{
    Q_OBJECT

public:
    explicit PanelKontrola(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);

private:
    QColorDialog *colorDialog;
    QPushButton *izaberiBoju;

    QPushButton *saveImage;

public slots:
    void prikaziColorDialog();

signals:
    void izabranaBoja(QColor);
    void zapamtiCrtez();
};

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

    QString _primaoc;

    QTimer *tajmerZaKoordinate;

    QPushButton *zatvoriButton;

    QHBoxLayout *hLay;
    PanelKontrola *panel;
    Widget *ekranZaCrtanje;

signals:
    void saljiPaket(QByteArray &paket, QString primaocPaketa);
    void zahtevZaKoordinate(QString primaoc);
    void gasenjeCrtaca();


public slots:

    void primiKordinate(QByteArray paket);
    void preusmeriSignal(QByteArray &s);
    void posaljiZahtevZaKoordinate();

    void postaviPrimaoca(QString p);
    void primiBojuOlovke(QColor);

};




#endif // PAINTERHOLDER_H
