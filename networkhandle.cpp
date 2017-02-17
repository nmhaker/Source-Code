#include "networkhandle.h"

static const char* os = "ubuntu";

NetworkHandle::NetworkHandle() : QObject()
{
    this->_korisnicko_ime = "NOT_SET";
    this->_mode = "DEPLOY";
    this->_online = false;

    this->_primaoc = "NOT_SET";

    this->_novePoruke = true;
    this->_imaViseOdJednePorukeZaPrimiti = false;

    this->_secretKey = "SIFRA";

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

QString NetworkHandle::getKorisnika()
{
    return this->_korisnicko_ime;
}

void NetworkHandle::prepareConnection()
{
    QNetworkProxy _proxy(QNetworkProxy::HttpProxy, "proxy.rcub.bg.ac.rs", 8080);

    this->_networkAccessManager = new QNetworkAccessManager(this);
//    this->_networkAccessManager->setProxy(_proxy);
    connect(this->_networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleRequestResponse(QNetworkReply*)));

    if(this->_mode == "DEVELOPMENT")
    {
        this->_networkRequest = new QNetworkRequest(QUrl("http://localhost/server/Server.php"));
    }
    else if(this->_mode == "DEPLOY")
        this->_networkRequest = new QNetworkRequest(QUrl("http://milutinac.eu5.org/Server/Server.php"));

    this->_networkRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
}

void NetworkHandle::loginUser(const QString korisnicko_ime, const QString sifra)
{
    this->_korisnicko_ime = korisnicko_ime;

    emit korisnickoIme(this->_korisnicko_ime);

    QUrlQuery params;
    params.addQueryItem("key", _secretKey);
    params.addQueryItem("action", "2");
    params.addQueryItem("korisnicko_ime", korisnicko_ime);
    params.addQueryItem("sifra", sifra);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::logOutUser()
{
    QUrlQuery params;
    params.addQueryItem("key", _secretKey);
    params.addQueryItem("action", "5");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);

    this->_online = false;
}

void NetworkHandle::registerUser(const QString ime, const QString prezime, const QString korisnicko_ime, const QString sifra, const QString mobilni )
{
    QUrlQuery params;
    params.addQueryItem("key", _secretKey);
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
    params.addQueryItem("key", _secretKey);
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
    params.addQueryItem("key", _secretKey);
    params.addQueryItem("action", "3");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::receiveMessageFrom(const QString p)
{
    this->_primaoc = p;

    QUrlQuery params;
    params.addQueryItem("key", _secretKey);
    params.addQueryItem("action", "9");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);
    params.addQueryItem("od", p);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::updateStatusPorukePrijatelja(const QString id, const QString status)
{
    QUrlQuery params;
    params.addQueryItem("key", _secretKey);
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
    params.addQueryItem("key", _secretKey);
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
    params.addQueryItem("key", _secretKey);
    params.addQueryItem("action", "6");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::getMyFriends()
{
    QUrlQuery params;
    params.addQueryItem("key", _secretKey);
    params.addQueryItem("action", "7");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::sendCoordinates(QByteArray &paket, QString primaocPaketa)
{

    qDebug() << paket.toHex() << endl;

    QUrlQuery params;
    params.addQueryItem("key", _secretKey);
    params.addQueryItem("action", "13");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);
    params.addQueryItem("data", paket.toHex());
    params.addQueryItem("primaoc", primaocPaketa);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::downloadCoordinates(QString posiljaoc)
{
    QUrlQuery params;
    params.addQueryItem("key", _secretKey);
    params.addQueryItem("action", "14");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);
    params.addQueryItem("posiljaoc", posiljaoc);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::fixDatabase()
{
    QUrlQuery params;
    params.addQueryItem("key", _secretKey);
    params.addQueryItem("action", "10");

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
        //this->fixDatabase();
        emit showMessageNotificationForAdmin("Dobrodosli Kreatore", "Da li zelite da vas povezemo?");
    }
}

void NetworkHandle::dodajNovogPrijatelja(QString i_p)
{
    if(this->_online)
    {
        QUrlQuery params;
        params.addQueryItem("key", _secretKey);
        params.addQueryItem("action", "12");
        params.addQueryItem("korisnicko_ime", _korisnicko_ime);
        params.addQueryItem("ime_prijatelja", i_p);

        QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

        this->_networkAccessManager->post(*(this->_networkRequest), data);
    }else{
        qDebug() << "Niste ulogovani" << endl;
    }
}

void NetworkHandle::obrisiPrijatelja(const QString &ime_prijatelja)
{
    QUrlQuery params;
    params.addQueryItem("key", _secretKey);
    params.addQueryItem("action", "15");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);
    params.addQueryItem("ime_prijatelja", ime_prijatelja);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::proveriDostupnostImenaKorisnika(QString i_p)
{
    QUrlQuery params;
    params.addQueryItem("key", _secretKey);
    params.addQueryItem("action", "11");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);
    params.addQueryItem("ime_prijatelja", i_p);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->_networkAccessManager->post(*(this->_networkRequest), data);
}

void NetworkHandle::obrisiRazgovor()
{
    if(this->_online)
        {
        QUrlQuery params;
        params.addQueryItem("key", _secretKey);
        params.addQueryItem("action", "16");
        params.addQueryItem("korisnicko_ime", _korisnicko_ime);
        params.addQueryItem("ime_prijatelja", _primaoc);

        QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

        this->_networkAccessManager->post(*(this->_networkRequest), data);
    }else{
        qDebug() << "Niste ulogovani" << endl;
    }
}

void NetworkHandle::dajStanjeLogovanja()
{
    emit posaljistanjeLogovanja(this->_online);
}

void NetworkHandle::handle_empty(QString str)
{
    qDebug() << "UPOZORENJE" <<  "Prazan RESPONSE, moguc problem: \n Nemate internet konekciju \n Server trenutno nedostupan" << endl << str << endl;
    emit showMessageNotification("UPOZORENJE" , "Greska u serveru, proverite internet konekciju, ili kontaktirajte administratora");
    //emit shutdownApplication();
}

void NetworkHandle::handle_error_3(QString str)
{
    emit showMessageNotification("Kriticna Greska", "PRAZNE POST PROMENLJIVE GASIM PROGRAM!");
    emit shutdownApplication();
}

void NetworkHandle::handle_error_101(QString str)
{
    qDebug() << "Neka greska u bazi podataka: " << str << endl;
    emit showMessageNotification("Kriticna Greska", "Greska u upitu u bazi podataka: " + str.remove(0,9) + " poslednja radnja nije odradjena kako treba, molimo ponovite radnju ponovo");
    //emit shutdownApplication();
}

void NetworkHandle::handle_error_103(QString str)
{
    emit showMessageNotification("Greska", "Neispravno korisnicko ime");
    emit potrebnoJePonovoUlogovatiSe();
}

void NetworkHandle::handle_error_104(QString str)
{
    qDebug() << "Neispravna sifra" << endl;
    emit showMessageNotification("Upozorenje", "Neispravna Sifra");
    emit potrebnoJePonovoUlogovatiSe();
}

void NetworkHandle::handle_error_106(QString str)
{
    qDebug() << "Vec sam ulogovan, moram rucno da apdejtujem bazu podataka -_-";
    emit showMessageNotification("UPOZORENJE", "Greska u programu");
}

void NetworkHandle::handle_error_107(QString str)
{
    qDebug() << "Nisam ulogovan";
    emit showMessageNotification("UPOZORENJE", "Niste ulogovani, moguca greska u programu");
}

void NetworkHandle::handle_response_100(QString str)
{
    emit notification("Nemate novih poruka");
    if(this->_novePoruke)
    {
        this->_novePoruke = false;
        emit setTimerInterval(4000);
    }
}

void NetworkHandle::handle_response_101(QString str)
{
    emit setTimerInterval(1000);
    QStringList list = str.split("\n");
    QString broj = list.value(1);
    if(broj != "")
    {
//                emit notification("Imate " + broj + " novih poruka");
//                emit showStatusNotification();
          if(this->_primaoc != "NONE")
              this->receiveMessageFrom(this->_primaoc);
    }
}

void NetworkHandle::handle_response_102(QString str)
{
    emit showMessageNotification("Obavestenje", "Uspesno ste se izlogovali");

    emit uspesnoIzlogovanje();

    emit promeniStanjeActionIzlogujSe(false);
    emit promeniStanjeActionUlogujSe(true);

    emit omoguciKontroluZaSlanjePoruka(false);

    emit ocistiListView();
    emit ocistiListWidget2();
}

void NetworkHandle::handle_response_103(QString str)
{
    emit showMessageNotification("Obavestenje", "Uspesno ste se registrovali!");
    emit potrebnoJePonovoUlogovatiSe();
}

void NetworkHandle::handle_response_104(QString str)
{
    if(str.contains("RESPONSE_104_FIXED_DB"))
        qDebug() << "Uspesno popravljena baza poruka, niste se lepo izlogovali proslog puta" << endl;
    emit showMessageNotification("Obavestenje",  "Uspesno ste se ulogovali");
    emit uspesnoUlogovanje();
    emit promeniStanjeActionUlogujSe(false);
    emit promeniStanjeActionIzlogujSe(true);
    this->_online = true;
    emit omoguciKontroluZaSlanjePoruka(true);

    this->getMyFriends();

    emit startTimer();
}

void NetworkHandle::handle_response_105(QString str)
{
    qDebug() << "Poruka je uspesno poslata" << endl;
    emit poslataPoruka();
    this->receiveMessageFrom(this->_primaoc);
}

void NetworkHandle::handle_response_106(QString str)
{
    qDebug() << "Ne postoji nijedan drugi korisnik sem tebe" << endl;
}

void NetworkHandle::handle_response_107(QString str)
{
    qDebug() << "Nemate nijednog prijatelja" << endl;
    emit showMessageNotification("Obavestenje", "Nemate nijednog prijatelja. Idite na + dugme i dodajte jednog :)");
}

void NetworkHandle::handle_response_108(QString str)
{
    QStringList list = str.split("\n");
    list.removeAt(0);
    foreach (QString item, list) {
        if(item != "")
            emit dodajPrijateljeUlistWidget2(item);
        qDebug() << item;
    }
}

void NetworkHandle::handle_response_110(QString str)
{
    qDebug() << "Uspesno updateovana poruka na 'primljeno' " << endl;
    if(this->_imaViseOdJednePorukeZaPrimiti)
    {
        this->receiveMessageFrom(this->_primaoc);
        this->_imaViseOdJednePorukeZaPrimiti = false;
    }
}

void NetworkHandle::handle_response_111(QString str)
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
}

void NetworkHandle::handle_response_112(QString str)
{
    QStringList list = str.split("\n");
    QString id = list.value(1);
    if(id != "")
    {
        if(list.value(2) != _korisnicko_ime )
        {
            emit novaPoruka(list.value(3), list.value(2));
            emit ubaciIdPorukePrijatelja(id);
            this->updateStatusPorukePrijatelja(id, "primljeno");
        }else
        {
            emit novaPoruka(list.value(3), list.value(2));
            emit ubaciIdPorukeKorisnika(id);
            this->updateStatusPorukeKorisnika(id, "primljeno");
        }
    }
    if(str.contains("RESPONSE_113"))
    {
        this->_imaViseOdJednePorukeZaPrimiti = true;
    }
}

void NetworkHandle::handle_response_114(QString str)
{
    qDebug() << "Uspesno je popravljena baza podataka" << endl;
}

void NetworkHandle::handle_response_115(QString str)
{
    qDebug() << "Postoji takav korisnik" << endl;
    emit postojiKorisnik(true);
}

void NetworkHandle::handle_response_116(QString str)
{
    qDebug() << "Ne postoji takav korisnik" << endl;
    emit postojiKorisnik(false);
}

void NetworkHandle::handle_response_117(QString str)
{
    qDebug() << "Uspesno ste poslali zahtev za prijateljstvo" << endl;
    emit ocistiListWidget2();
    this->getMyFriends();
}

void NetworkHandle::handle_response_118(QString str)
{
    qDebug() << "Vec imate takvog prijatelja" << endl;
    emit showMessageNotification("Upozorenje",  "Nije moguce dodati prijatelja, jer ga vec imate");
}

void NetworkHandle::handle_response_119(QString str)
{
    qDebug() << "Ne postoji takav prijatelj" << endl;
    emit showMessageNotification("Upozorenje", "Poslali ste zahtev za prijatelja koji ne postoji, proverite jos jednom");
}

void NetworkHandle::handle_response_120(QString str)
{
    qDebug() << "Uspesno poslata koordinata" << endl;
}

void NetworkHandle::handle_response_121(QByteArray msg)
{
    QByteArray temp(msg);
    qDebug() << "Primam kordinate, pre trimovanja: " << temp;
    temp.remove(0, 12);
    qDebug() << "Primam kordinate, posle trimovanja: " << temp;

    emit emitPristigleKoordinate(temp);
}

void NetworkHandle::handle_response_122(QString str)
{
    qDebug() << "Prazan upit" << endl;
}

void NetworkHandle::handle_response_123(QString str)
{
    emit ocistiListView();
    emit ocistiListWidget2();
    emit getMyFriends();
    qDebug() << "Uspesno izbrisan prijatelja " << endl;
}

void NetworkHandle::handle_response_124(QString str)
{
    emit ocistiListView();
    qDebug() << "Uspesno ociscen razgovor" << endl;
}

void NetworkHandle::handleRequestResponse(QNetworkReply *r)
{

        QByteArray msg = r->readAll();
        QString str;

        for(int i=0;i<msg.length();i++)
            str.append(msg.at(i));

        if(str.contains("ERROR_3"))
        {
             handle_error_3(str);
        }
        else if(str.contains("ERROR_101"))
        {
             handle_error_101(str);
        }
        else if(str.contains("ERROR_103"))
        {
             handle_error_103(str);
        }
        else if(str.contains("ERROR_104"))
        {
             handle_error_104(str);
        }
        else if(str.contains("ERROR_106"))
        {
             handle_error_106(str);
        }
        else if(str.contains("ERROR_107"))
        {
             handle_error_107(str);
        }
        else if(str.contains("RESPONSE_100"))
        {
             handle_response_100(str);
        }
        else if(str.contains("RESPONSE_101"))
        {
             handle_response_101(str);
        }
        else if(str.contains("RESPONSE_112"))
        {
             handle_response_112(str);
        }
        else if(str.contains("SRESPONSE_110") || str.contains("S2RESPONSE_110"))
        {
             handle_response_110(str);
        }
        else if(str.contains("RESPONSE_111"))
        {
             handle_response_111(str);
        }
        else if(str.contains("RESPONSE_102"))
        {
             handle_response_102(str);
        }
        else if(str.contains("RESPONSE_103"))
        {
             handle_response_103(str);
        }
        else if(str.contains("RESPONSE_104"))
        {
             handle_response_104(str);
        }
        else if(str.contains("RESPONSE_105"))
        {
             handle_response_105(str);
        }
        else if(str.contains("RESPONSE_106"))
        {
             handle_response_106(str);
        }
        else if(str.contains("RESPONSE_107"))
        {
             handle_response_107(str);
        }
        else if(str.contains("RESPONSE_108"))
        {
             handle_response_108(str);
        }
        else if(str.contains("RESPONSE_114"))
        {
             handle_response_114(str);
        }
        else if(str.contains("RESPONSE_115"))
        {
             handle_response_115(str);
        }
        else if(str.contains("RESPONSE_116"))
        {
             handle_response_116(str);
        }
        else if(str.contains("RESPONSE_117"))
        {
             handle_response_117(str);
        }
        else if(str.contains("RESPONSE_118"))
        {
             handle_response_118(str);
        }
        else if(str.contains("RESPONSE_119"))
        {
             handle_response_119(str);
        }
        else if(str.contains("RESPONSE_120"))
        {
             handle_response_120(str);
        }
        else if(str.contains("RESPONSE_121"))
        {
             handle_response_121(msg);
        }
        else if(str.contains("RESPONSE_122"))
        {
             handle_response_122(str);
        }
        else if(str.contains("RESPONSE_123"))
        {
             handle_response_123(str);
        }
        else if(str.contains("RESPONSE_124"))
        {
             handle_response_124(str);
        }
        else
        {
             handle_empty(str);
        }
}

