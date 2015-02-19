#ifndef PAINTERHOLDER_H
#define PAINTERHOLDER_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QLabel>
#include <QBitmap>

#include "widget.h"

//PANELKONTROLA

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

    QWidget *colorShown;
    QLabel *label;

    QPushButton *izaberiBoju;
    QPushButton *saveImage;

    QPushButton *olovka;
    QPushButton *gumica;

public slots:
    void prikaziColorDialog();
    void postaviBoju(QColor c);
    void postaviTrenutniAlatOlovku();
    void postaviTrenutniAlatGumicu();

signals:
    void izabranaBoja(QColor);
    void zapamtiCrtez();
    void izabranAlat(Alat a);
};

//PAINTERHOLDER

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
    void mouseMoveEvent(QMouseEvent *);

private:

    QString _primaoc;

    QTimer *tajmerZaKoordinate;

    QHBoxLayout *hLay;
    PanelKontrola *panel;
    Widget *ekranZaCrtanje;

    Alat trenutniAlat = Olovka;

    QCursor *kursorOlovka;
    QCursor *kursorGumica;

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

    void postaviAlat(Alat a);

};




#endif // PAINTERHOLDER_H
