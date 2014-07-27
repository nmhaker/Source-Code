#ifndef NETWORKHANDLE_H
#define NETWORKHANDLE_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QMainWindow>


class NetworkHandle : public QObject
{
    Q_OBJECT

public:
    NetworkHandle();

    bool isOnline();
    QString getPrimaoca();
    QString getKorisnika();

private:

    QNetworkAccessManager   *_networkAccessManager;
    QNetworkRequest         *_networkRequest;

    QString _korisnicko_ime;
    QString _primaoc;
    QString _mode;
    bool _online;
    bool _novePoruke;
    bool _imaViseOdJednePorukeZaPrimiti;

    void prepareConnection();



public slots:

    void handleRequestResponse(QNetworkReply *r);
    void loginUser(const QString korisnicko_ime, const QString sifra);
    void registerUser(const QString ime, const QString prezime, const QString korisnicko_ime,const QString sifra, const QString mobilni);
    void logOutUser();
    void sendMessage(const QString poruka);
    void checkForNewMessages();
    void receiveMessageFrom(const QString p);
    void updateStatusPorukePrijatelja(const QString id, const QString status);
    void updateStatusPorukeKorisnika(const QString id, const QString status2);
    void getFriends();
    void getMyFriends();

    void fixDatabase();

    void postaviPrimaoca(const QString p);
    void poveziKreatora();

signals:
    void poslataPoruka();
    void uspesnoUlogovanje();
    void uspesnoIzlogovanje();
    void shutdownApplication();
    void potrebnoJePonovoUlogovatiSe();
    void potrebnoJeIzlogovatiSe();
    void notification(const QString s);
    void showStatusNotification();
    void showMessageNotification(const QString, const QString);
    void setTimerInterval(int msec);
    void novaPoruka(const QString, const QString);
    void ubaciIdPorukePrijatelja(QString);
    void ubaciIdPorukeKorisnika(QString);
    void promeniStanjeActionIzlogujSe(bool);
    void promeniStanjeActionUlogujSe(bool);
    void ocistiListView();
    void ocistiListWidget2();
    void startTimer();
    void dodajPrijateljeUlistWidget2(QString);

    void showMessageNotificationForAdmin(const QString, const QString);
    void omoguciKontroluZaSlanjePoruka(bool);

    void korisnickoIme(QString);
};

#endif // NETWORKHANDLE_H
