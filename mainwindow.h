#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QByteArray>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTimer>
#include <QDesktopWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QBitmap>
#include <QPainter>
#include <QPushButton>
#include <QPalette>

#include "networkhandle.h"
#include "storagehandle.h"
#include "loginform.h"
#include "registerform.h"
#include "model.h"
#include "buttonaddfriend.h"
#include "dialogzadodavanjeprijatelja.h"
#include "painterholder.h"
#include "statuswidget.h"
#include "podesavanja.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:

    void closeEvent(QCloseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void paintEvent(QPaintEvent *e);

private:

    Ui::MainWindow *ui;

    QPushButton *dugmeLogIn;
    QPushButton *dugmeLogOut;
    QPushButton *dugmeSrednje;
    QPushButton *dugmeRegister;
    QPushButton *dugmeSettings;
    QPushButton *buttonAddFriend;

    NetworkHandle *networkHandle;
    StorageHandle *_storageHandle;
    Model *model;

    LoginForm *loginForm;
    RegisterForm *registerForm;
    DialogZaDodavanjePrijatelja *addFriendForm;

    QTimer *timer;
    QTimer *timerZaGasenje;

    QLabel *userState;

    bool spremnoZaIzlogovanje;

    PainterHolder *crtac;

    StatusWidget *statusWidget;

    Podesavanja *podesavanja;


public slots:

    void ulogujSe();
    void izlogujSe();
    void registrujSe();
    bool izadji();
    void posaljiPoruku();
    void primiPoruku();
    void pripremiZaGasenje();
    void dodajNovogPrijatelja();

    void postaviPrimaoca(QListWidgetItem *primaoc);
    void prikaziPoruku(QString p, QString pp);
    void prikaziPorukuZaAdmina(QString p, QString pp);
    void postaviIntervalTajmera(int msec);
    void dodajPrijateljeUlistWidget2(QString p);
    void ubaciIdPorukeKorisnika(QString id);
    void ubaciIdPorukePrijatelja(QString id);

    void changeState();
    void refreshujMessageView();

    void omoguciKontroluZaSlanjePoruka(bool p);
    void otvoriCrtac(QString);

    void opcije();


signals:
    void poveziKreatora();
    void noviPrijatelj(const QString p);

};

#endif // MAINWINDOW_H
