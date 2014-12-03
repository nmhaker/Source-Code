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

    QString _secretKey;

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

    void sendCoordinates(QByteArray paket, QString primaocPaketa);
    void downloadCoordinates(QString posiljaoc);

    void fixDatabase();

    void postaviPrimaoca(const QString p);
    void poveziKreatora();

    void dodajNovogPrijatelja(QString i_p);
    void proveriDostupnostImenaKorisnika(QString i_p);

private slots:

    void handle_empty(QString str);
    //Error handles
    void handle_error_3(QString str);
    void handle_error_101(QString str);
    void handle_error_103(QString str);
    void handle_error_104(QString str);
    void handle_error_106(QString str);
    void handle_error_107(QString str);
    //Response handles
    void handle_response_100(QString str);
    void handle_response_101(QString str);
    void handle_response_102(QString str);
    void handle_response_103(QString str);
    void handle_response_104(QString str);
    void handle_response_105(QString str);
    void handle_response_106(QString str);
    void handle_response_107(QString str);
    void handle_response_108(QString str);
    void handle_response_110(QString str);
    void handle_response_111(QString str);
    void handle_response_112(QString str);
    void handle_response_114(QString str);
    void handle_response_115(QString str);
    void handle_response_116(QString str);
    void handle_response_117(QString str);
    void handle_response_118(QString str);
    void handle_response_119(QString str);
    void handle_response_120(QString str);
    void handle_response_121(QString str);
    void handle_response_122(QString str);


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

    void postojiKorisnik(bool);

    void emitPristigleKoordinate(QByteArray data);
};

#endif // NETWORKHANDLE_H
