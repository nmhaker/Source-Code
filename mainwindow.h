#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QDebug>
#include <QByteArray>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTimer>
#include <QDesktopWidget>

#include "loginform.h"
#include "registerform.h"

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

private:
    Ui::MainWindow *ui;

    void prepareConnection();


    QNetworkAccessManager *networkAccessManager;
    QNetworkRequest *networkRequest;

    LoginForm *loginForm;
    RegisterForm *registerForm;

    QString _korisnicko_ime;
    bool _online;

    QTimer *timer;

    QString mode;


public slots:
    void handleRequestResponse(QNetworkReply *r);

    void ulogujSe();
    void izlogujSe();
    void registrujSe();
    void izadji();
    void posaljiPoruku();
    void primiPoruku();

    void loginUser(const QString korisnicko_ime, const QString sifra);
    void registerUser(const QString ime, const QString prezime, const QString korisnicko_ime,const QString sifra, const QString mobilni);
    void logOutUser(const QString korisnicko_ime);
    void sendMessage(const QString korisnicko_ime, const QString primalac, const QString poruka);
    void receiveMessage(const QString korisnicko_ime);

};

#endif // MAINWINDOW_H
