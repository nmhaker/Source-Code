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
#include <QPushButton>

#include "networkhandle.h"
#include "storagehandle.h"
#include "mtabwidget.h"
#include "loginform.h"
#include "registerform.h"
#include "model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;

    NetworkHandle *networkHandle;
    StorageHandle *_storageHandle;
    Model *model;

    LoginForm *loginForm;
    RegisterForm *registerForm;

    QTimer *timer;
    QTimer *timerZaGasenje;

    QLabel *obavestenje ;

    bool spremnoZaIzlogovanje;

protected:

    void closeEvent(QCloseEvent *e);
    void keyPressEvent(QKeyEvent *e);

private:
    QPushButton *dugmeLogIn;
    QPushButton *dugmeLogOut;
    QPushButton *dugmeRegister;
    QPushButton *dugmeExit;

public slots:

    void ulogujSe();
    void izlogujSe();
    void registrujSe();
    void izadji();
    void posaljiPoruku();
    void primiPoruku();
    void pripremiZaGasenje();

    void postaviPrimaoca(QListWidgetItem *primaoc);
    void izbaciObavestenje(const QString s);
    void prikaziObavestenje();
    void prikaziPoruku(QString p, QString pp);
    void prikaziPorukuZaAdmina(QString p, QString pp);
    void postaviIntervalTajmera(int msec);
    void dodajPrijateljeUlistWidget2(QString p);
    void ubaciIdPorukeKorisnika(QString id);
    void ubaciIdPorukePrijatelja(QString id);

    void omoguciKontroluZaSlanjePoruka(bool p);

signals:
    void poveziKreatora();
    void noviPrijatelj(const QString p);
};

#endif // MAINWINDOW_H
