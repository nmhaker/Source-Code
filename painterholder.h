#ifndef PAINTERHOLDER_H
#define PAINTERHOLDER_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QLabel>

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
    QColor boja;
    QColorDialog *colorDialog;
    QPushButton *izaberiBoju;
    QWidget *colorShown;
    QLabel *label;

    QPushButton *saveImage;

public slots:
    void prikaziColorDialog();
    void postaviBoju(QColor c);

signals:
    void izabranaBoja(QColor);
    void zapamtiCrtez();
};

class PainterHolder : public QWidget
{
    Q_OBJECT
public:
    explicit PainterHolder(QWidget *parent = 0, QString primaoc = "NONE");
    ~PainterHolder();
protected:

    void resizeEvent(QResizeEvent *e);
    void keyPressEvent(QKeyEvent *);
    void closeEvent(QCloseEvent *e);

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
