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
#include <QListWidgetItem>

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
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::MainWindow *ui;

    void prepareConnection();


    QNetworkAccessManager *networkAccessManager;
    QNetworkRequest *networkRequest;

    LoginForm *loginForm;
    RegisterForm *registerForm;

    QString _korisnicko_ime;

    QString _primaoc;

    bool _online;

    QTimer *timer;

    QString mode;

    QLabel *obavestenje ;

    bool novePoruke;
    bool imaViseOdJednePorukeZaPrimiti;

    bool spremnoZaIzlogovanje;

    QStringList primljenePorukePrijatelja;
    QStringList primljenePorukeKorisnika;

    int brojSpremnihPorukaPrijatelja;
    int brojSpremnihPorukaKorisnika;




public slots:
    void handleRequestResponse(QNetworkReply *r);

    void ulogujSe();
    void izlogujSe();
    void registrujSe();
    void izadji();
    void posaljiPoruku();
    void primiPoruku();
    void pripremiZaGasenje();

    void postaviPrimaoca(QListWidgetItem *primaoc);

    void loginUser(const QString korisnicko_ime, const QString sifra);
    void registerUser(const QString ime, const QString prezime, const QString korisnicko_ime,const QString sifra, const QString mobilni);
    void logOutUser(const QString korisnicko_ime);
    void sendMessage(const QString korisnicko_ime, const QString primalac, const QString poruka);
    void checkForNewMessages(const QString korisnicko_ime);
    void receiveMessageFrom(const QString korisnicko_ime, const QString od);
    void updateStatusPorukePrijatelja(const QString id, const QString status);
    void updateStatusPorukeKorisnika(const QString id, const QString status2);
    void getFriends();
    void getMyFriends(const QString korisnicko_ime);

};

#endif // MAINWINDOW_H
