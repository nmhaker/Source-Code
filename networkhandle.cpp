#include "networkhandle.h"

NetworkHandle::NetworkHandle() : QObject()
{
    this->_korisnicko_ime = "NOT_SET";
    this->_mode = "DEVELOPMENT";
    this->_online = false;


    this->_novePoruke = true;
    this->_imaViseOdJednePorukeZaPrimiti = false;

    this->prepareConnection();

}

bool NetworkHandle::isOnline()
{
    if(this->_online)
        return true;
    else
        return false;
}

QString NetworkHandle::getPrimaoca()
{
    return this->_primaoc;
}


void NetworkHandle::prepareConnection()
{
    this->_networkAccessManager = new QNetworkAccessManager(this);

    connect(this->_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleRequestResponse(QNetworkReply*)));

    if(this->_mode == "DEVELOPMENT")
    {
        this->_networkRequest = new QNetworkRequest(QUrl("http://localhost/server/Server.php"));
    }
    else if(this->_mode == "DEPLOY")
        this->_networkRequest = new QNetworkRequest(QUrl("http://milutinac.eu5.org/Server.php"));

    this->_networkRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
}

void NetworkHandle::loginUser(const QString korisnicko_ime, const QString sifra)
{
    this->_korisnicko_ime = korisnicko_ime;

    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "2");
    params.addQueryItem("korisnicko_ime", korisnicko_ime);
    params.addQueryItem("sifra", sifra);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::logOutUser()
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "5");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);

    this->_online = false;
}

void NetworkHandle::registerUser(const QString ime, const QString prezime, const QString korisnicko_ime, const QString sifra, const QString mobilni )
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "1");
    params.addQueryItem("ime", ime);
    params.addQueryItem("prezime", prezime);
    params.addQueryItem("korisnicko_ime", korisnicko_ime);
    params.addQueryItem("sifra", sifra);
    params.addQueryItem("mobilni", mobilni);


    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::sendMessage(const QString poruka)
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "4");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);
    params.addQueryItem("primalac", _primaoc);
    params.addQueryItem("poruka", poruka);


    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::checkForNewMessages()
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "3");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::receiveMessageFrom()
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "9");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);
    params.addQueryItem("od", _primaoc);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::updateStatusPorukePrijatelja(const QString id, const QString status)
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "8");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);
    params.addQueryItem("idPoruke", id);
    params.addQueryItem("status", status);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::updateStatusPorukeKorisnika(const QString id, const QString status2)
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "8");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);
    params.addQueryItem("idPoruke", id);
    params.addQueryItem("status2", status2);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::getFriends()
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "6");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::getMyFriends()
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "7");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::postaviPrimaoca(const QString p)
{
    this->_primaoc = p;
}

void NetworkHandle::poveziKreatora()
{
    if(this->_mode == "DEVELOPMENT")
    {
        emit showMessageNotificationForAdmin("Dobrodosli Kreatore", "Da li zelite da vas povezemo?");
    }
}

void NetworkHandle::handleRequestResponse(QNetworkReply *r)
{

        QByteArray msg = r->readAll();
        QString str;

        for(int i=0;i<msg.length();i++)
            str.append(msg.at(i));

        if(str.contains("ERROR_3"))
        {
            emit showMessageNotification("Kriticna Greska", "PRAZNE POST PROMENLJIVE GASIM PROGRAM!");
        }else
        if(str.contains("ERROR_101"))
        {
            emit showMessageNotification("Kriticna Greska", "Greska u upitu u bazi podataka");
        }else
        if(str.contains("ERROR_103"))
        {
            emit showMessageNotification("Greska", "Neispravno korisnicko ime");
            emit potrebnoJePonovoUlogovatiSe();
        }else if(str.contains("ERROR_106"))
        {
            qDebug() << "Vec sam ulogovan, moram rucno da apdejtujem bazu podataka -_-";
            emit showMessageNotification("UPOZORENJE", "Greska u programu");
            emit shutdownApplication();
        }else if(str.contains("ERROR_107"))
        {
            qDebug() << "Nisam ulogovan";
            emit showMessageNotification("UPOZORENJE", "Niste ulogovani, moguca greska u programu");
            emit shutdownApplication();
        }else if(str.contains("RESPONSE_100"))
        {
            emit notification("Nemate novih poruka");
            if(this->_novePoruke)
            {
                this->_novePoruke = false;
                emit setTimerInterval(4000);
            }
        }
        else if(str.contains("RESPONSE_101"))
        {
            emit setTimerInterval(1000);
            QStringList list = str.split("\n");
            QString broj = list.value(1);
            if(broj != "")
            {
                emit notification("Imate " + broj + " novih poruka");
                emit showStatusNotification();
            }
        }else if(str.contains("RESPONSE_112"))
        {
            QStringList list = str.split("\n");
            QString id = list.value(1);
            if(id != "")
            {
                if(list.value(2) != _korisnicko_ime )
                {
                    emit novaPoruka(list.value(3), false);
                    emit ubaciIdPorukePrijatelja(id);
                    this->updateStatusPorukePrijatelja(id, "primljeno");
                }else
                {
                    emit novaPoruka(list.value(3), true);
                    emit ubaciIdPorukeKorisnika(id);
                    this->updateStatusPorukeKorisnika(id, "primljeno");
                }
            }

            if(str.contains("RESPONSE_113"))
            {
                this->_imaViseOdJednePorukeZaPrimiti = true;
            }
        }else if(str.contains("SRESPONSE_110") || str.contains("S2RESPONSE_110"))
        {
            qDebug() << "Uspesno updateovana poruka na 'primljeno' " << endl;
            if(this->_imaViseOdJednePorukeZaPrimiti)
            {
                this->receiveMessageFrom();
                this->_imaViseOdJednePorukeZaPrimiti = false;
            }
        }else if(str.contains("RESPONSE_111"))
        {
            if(str.contains("SRESPONSE_111"))
            {
                qDebug() << "Uspesno updateovana poruka na 'neprimljeno' " << endl;
                if(this->_online)
                    emit potrebnoJeIzlogovatiSe();
            }else if(str.contains("S2RESPONSE_111"))
            {
                qDebug() << "Uspesno updateovana poruka na 'neprimljeno' " << endl;
                if(this->_online)
                    emit potrebnoJeIzlogovatiSe();
            }
        }else if(str.contains("RESPONSE_102"))
        {
            emit showMessageNotification("Obavestenje", "Uspesno ste se izlogovali");

            emit promeniStanjeActionIzlogujSe(false);
            emit promeniStanjeActionUlogujSe(true);

            emit omoguciKontroluZaSlanjePoruka(false);

            emit ocistiListWidget();
            emit ocistiListWidget2();

        }else if(str.contains("RESPONSE_103"))
        {
            emit showMessageNotification("Obavestenje", "Uspesno ste se registrovali!");
            emit potrebnoJePonovoUlogovatiSe();
        }else if(str.contains("RESPONSE_104"))
        {
            emit showMessageNotification("Obavestenje",  "Uspesno ste se ulogovali");
            emit promeniStanjeActionUlogujSe(false);
            emit promeniStanjeActionIzlogujSe(true);
            this->_online = true;
            emit omoguciKontroluZaSlanjePoruka(true);

            this->getFriends();

            emit startTimer();
        }else if(str.contains("RESPONSE_105"))
        {
            qDebug() << "Poruka je uspesno poslata" << endl;
        }else if(str.contains("RESPONSE_108"))
        {
            QStringList list = str.split("\n");
            list.removeAt(0);
            foreach (QString item, list) {
                if(item != "")
                    emit dodajPrijateljeUlistWidget2(item);
                qDebug() << item;
            }
        }else
        {
            qDebug() << str << endl;
            emit showMessageNotification("UPOZORENJE" , "Prazan RESPONSE, moguc problem: \n Nemate internet konekciju \n Server trenutno nedostupan");
            emit shutdownApplication();
        }
}

