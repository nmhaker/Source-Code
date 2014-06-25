#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->mode = "DEVELOPMENT";
    this->novePoruke = true;
    this->spremnoZaIzlogovanje = false;

    this->_primaoc = "NONE";

    this->brojSpremnihPorukaPrijatelja = 0;
    this->brojSpremnihPorukaKorisnika = 0;

    this->prepareConnection();

    connect(this->ui->actionUloguj_Se, SIGNAL(triggered()), this, SLOT(ulogujSe()));
    connect(this->ui->actionIzadji, SIGNAL(triggered()), this, SLOT(izadji()));
    connect(this->ui->actionIzloguj_Se, SIGNAL(triggered()), this, SLOT(izlogujSe()));
    connect(this->ui->actionRegistruj_Se, SIGNAL(triggered()), this, SLOT(registrujSe()));
    connect(this->ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(posaljiPoruku()));
    connect(this->ui->listWidget_2, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(postaviPrimaoca(QListWidgetItem*)));

    this->_korisnicko_ime = "NOT_SET";
    this->_online = false;

    this->ui->actionIzloguj_Se->setDisabled(true);

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()), this, SLOT(primiPoruku()));

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x, y);

    if(this->mode == "DEVELOPMENT")
    {
        this->loginUser("nmhaker", "comrade123");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if(this->_online)
    {
        QMessageBox::StandardButton resBtn = QMessageBox::warning( this, "Messenger", tr("Prvo se izlogujte, pre nego sto zatvorite aplikaciju"), QMessageBox::Yes);
        if (resBtn == QMessageBox::Yes) {
            e->ignore();
        }
    }else
    {
        e->accept();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_F1)
        this->ulogujSe();
    else if(e->key() == Qt::Key_F2)
        this->izlogujSe();
    else if(e->key() == Qt::Key_F3)
        this->registrujSe();
    else if(e->key() == Qt::Key_F4)
        this->izadji();
}

void MainWindow::prepareConnection()
{
    this->networkAccessManager = new QNetworkAccessManager(this);

    connect(this->networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleRequestResponse(QNetworkReply*)));

    if(this->mode == "DEVELOPMENT")
    {
        this->networkRequest = new QNetworkRequest(QUrl("http://localhost/server/Server.php"));
    }
    else if(this->mode == "DEPLOY")
        this->networkRequest = new QNetworkRequest(QUrl("http://milutinac.eu5.org/Server.php"));

    this->networkRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
}

void MainWindow::loginUser(const QString korisnicko_ime, const QString sifra)
{
    this->_korisnicko_ime = korisnicko_ime;

    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "2");
    params.addQueryItem("korisnicko_ime", korisnicko_ime);
    params.addQueryItem("sifra", sifra);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->networkAccessManager->post(*(this->networkRequest), data);
}

void MainWindow::logOutUser(const QString korisnicko_ime)
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "5");
    params.addQueryItem("korisnicko_ime", korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->networkAccessManager->post(*(this->networkRequest), data);

    this->_online = false;
}

void MainWindow::registerUser(const QString ime, const QString prezime, const QString korisnicko_ime, const QString sifra, const QString mobilni )
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

    this->networkAccessManager->post(*(this->networkRequest), data);
}

void MainWindow::sendMessage(const QString korisnicko_ime, const QString primalac, const QString poruka)
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "4");
    params.addQueryItem("korisnicko_ime", korisnicko_ime);
    params.addQueryItem("primalac", primalac);
    params.addQueryItem("poruka", poruka);


    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->networkAccessManager->post(*(this->networkRequest), data);
}

void MainWindow::checkForNewMessages(const QString korisnicko_ime)
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "3");
    params.addQueryItem("korisnicko_ime", korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->networkAccessManager->post(*(this->networkRequest), data);
}

void MainWindow::receiveMessageFrom(const QString korisnicko_ime, const QString od)
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "9");
    params.addQueryItem("korisnicko_ime", korisnicko_ime);
    params.addQueryItem("od", od);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->networkAccessManager->post(*(this->networkRequest), data);
}

void MainWindow::updateStatusPorukePrijatelja(const QString id, const QString status)
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "8");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);
    params.addQueryItem("idPoruke", id);
    params.addQueryItem("status", status);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->networkAccessManager->post(*(this->networkRequest), data);
}

void MainWindow::updateStatusPorukeKorisnika(const QString id, const QString status2)
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "8");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);
    params.addQueryItem("idPoruke", id);
    params.addQueryItem("status2", status2);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->networkAccessManager->post(*(this->networkRequest), data);
}

void MainWindow::getFriends()
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "6");
    params.addQueryItem("korisnicko_ime", _korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->networkAccessManager->post(*(this->networkRequest), data);
}

void MainWindow::getMyFriends(const QString korisnicko_ime)
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "7");
    params.addQueryItem("korisnicko_ime", korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->networkAccessManager->post(*(this->networkRequest), data);
}

void MainWindow::handleRequestResponse(QNetworkReply *r)
{

        QByteArray msg = r->readAll();
        QString str;

        for(int i=0;i<msg.length();i++)
            str.append(msg.at(i));

        if(str.contains("ERROR_3"))
        {
            QMessageBox::warning(this, "Kriticna Greska", "PRAZNE POST PROMENLJIVE GASIM PROGRAM!", QMessageBox::Ok);
        }else
        if(str.contains("ERROR_101"))
        {
            QMessageBox::warning(this, "Kriticna Greska", "Greska u upitu u bazi podataka, GASIM PROGRAM!", QMessageBox::Ok);
        }else
        if(str.contains("ERROR_103"))
        {
            QMessageBox::warning(this, "Greska", "Neispravno korisnicko ime", QMessageBox::Ok);
            this->ulogujSe();
        }else if(str.contains("ERROR_106"))
        {
            qDebug() << "Vec sam ulogovan, moram rucno da apdejtujem bazu podataka -_-";
            QMessageBox::warning(this, "UPOZORENJE" , "Greska u programu", QMessageBox::Ok);
            this->close();
        }else if(str.contains("ERROR_107"))
        {
            qDebug() << "Nisam ulogovan";
            QMessageBox::warning(this, "UPOZORENJE" , "Niste ulogovani, moguca greska u programu", QMessageBox::Ok);
            this->close();
        }else if(str.contains("RESPONSE_100"))
        {
            if(this->novePoruke)
            {
                this->novePoruke = false;
                timer->setInterval(4000);
            }
        }
        else if(str.contains("RESPONSE_101"))
        {
            timer->setInterval(1000);
            QStringList list = str.split("\n");
            //this->ui->listWidget->addItem(list.value(2));
            QString id = list.value(1);
            if(id != "")
            {
                if(list.value(2) != _korisnicko_ime)
                {
                    primljenePorukePrijatelja.append(id);
                    this->updateStatusPorukePrijatelja(id, "primljeno");
                }
                else{
                    primljenePorukeKorisnika.append(id);
                    this->updateStatusPorukeKorisnika(id, "primljeno");
                }
            }
        }else if(str.contains("SRESPONSE_110") || str.contains("S2RESPONSE_110"))
        {
            qDebug() << "Uspesno updateovana poruka na 'primljeno' " << endl;
        }else if(str.contains("RESPONSE_111"))
        {
            if(str.contains("SRESPONSE_111"))
            {
                qDebug() << "Uspesno updateovana poruka na 'neprimljeno' " << endl;
                if(this->_online)
                    this->izlogujSe();
            }else if(str.contains("S2RESPONSE_111"))
            {
                qDebug() << "Uspesno updateovana poruka na 'neprimljeno' " << endl;
                if(this->_online)
                    this->izlogujSe();
            }
        }else if(str.contains("RESPONSE_102"))
        {
            QMessageBox::information(this, "Obavestenje", "Uspesno ste se izlogovali", QMessageBox::Ok);

            this->ui->actionIzloguj_Se->setDisabled(true);
            this->ui->actionUloguj_Se->setDisabled(false);

            this->ui->listWidget->clear();
            this->ui->listWidget_2->clear();

        }else if(str.contains("RESPONSE_103"))
        {
            QMessageBox::information(this, "Obavestenje", "Uspesno ste se registrovali!", QMessageBox::Ok);
            this->ulogujSe();
        }else if(str.contains("RESPONSE_104"))
        {
            QMessageBox::information(this,"Obavestenje",  "Uspesno ste se ulogovali", QMessageBox::Ok);
            this->ui->actionUloguj_Se->setDisabled(true);
            this->ui->actionIzloguj_Se->setDisabled(false);
            this->_online = true;

            this->getFriends();

            timer->start();
        }else if(str.contains("RESPONSE_105"))
        {
            qDebug() << "Poruka je uspesno poslata" << endl;
        }else if(str.contains("RESPONSE_108"))
        {
            QStringList list = str.split("\n");
            list.removeAt(0);
            foreach (QString item, list) {
                if(item != "")
                    this->ui->listWidget_2->addItem(item);
                qDebug() << item;
            }
        }else
        {
            qDebug() << str << endl;
            QMessageBox::warning(this, "UPOZORENJE" , "Greska u programu", QMessageBox::Ok);
            this->close();
        }

}

void MainWindow::ulogujSe()
{
    if(!this->_online)
    {
        this->loginForm = new LoginForm();
        this->loginForm->setGeometry(this->x() + this->width()/3, this->y() + this->height()/3, loginForm->width(), loginForm->height());

        connect(this->loginForm, SIGNAL(salji(QString,QString)), this, SLOT(loginUser(QString,QString)));

        this->loginForm->show();

    }else
    {
        QMessageBox::warning(this, "Upozorenje", "Vec ste ulogovani", QMessageBox::Ok);
    }
}

void MainWindow::izlogujSe()
{
    if(this->_online == false)
       QMessageBox::warning(this, "Upozorenje" ,"Vec ste izlogovani", QMessageBox::Ok);
    else
    {
        this->timer->stop();
        if(spremnoZaIzlogovanje)
        {
            this->primljenePorukePrijatelja.clear();
            this->primljenePorukeKorisnika.clear();
            this->brojSpremnihPorukaPrijatelja = 0;
            this->brojSpremnihPorukaKorisnika = 0;
            this->spremnoZaIzlogovanje = false;
            this->logOutUser(this->_korisnicko_ime);
        }else{
            pripremiZaGasenje();
        }
    }
}

void MainWindow::registrujSe()
{
    this->registerForm = new RegisterForm();
    connect(this->registerForm, SIGNAL(salji(QString,QString,QString,QString,QString)), this, SLOT(registerUser(QString,QString,QString,QString,QString)));
    this->registerForm->show();
}

void MainWindow::izadji()
{
    if(this->_online)
    {
        QMessageBox::warning(this, "Upozorenje", "Prvo se izlogujte!!!", QMessageBox::Ok);
    }
    else
        this->close();
}

void MainWindow::posaljiPoruku()
{
    if(this->_primaoc == "NONE")
        QMessageBox::warning(this, "Upozorenje", "Morate izabrati primaoca poruke, sa desne strane!", QMessageBox::Ok);
    else
        this->sendMessage(this->_korisnicko_ime, this->_primaoc, this->ui->lineEdit->text());
}

void MainWindow::primiPoruku()
{
    this->checkForNewMessages(this->_korisnicko_ime);
}

void MainWindow::pripremiZaGasenje()
{
    if(this->_online)
    {
        if(this->brojSpremnihPorukaPrijatelja < primljenePorukePrijatelja.count())
        {
            this->updateStatusPorukePrijatelja(primljenePorukePrijatelja.value(brojSpremnihPorukaPrijatelja), "neprimljeno");
            this->brojSpremnihPorukaPrijatelja++;
        }

        if(this->brojSpremnihPorukaKorisnika < primljenePorukeKorisnika.count())
        {
            this->updateStatusPorukeKorisnika(primljenePorukeKorisnika.value(brojSpremnihPorukaKorisnika), "neprimljeno");
            this->brojSpremnihPorukaKorisnika++;
        }

        if((brojSpremnihPorukaPrijatelja == primljenePorukePrijatelja.count()) and (brojSpremnihPorukaKorisnika == primljenePorukeKorisnika.count()))
            this->spremnoZaIzlogovanje = true;
    }

}

void MainWindow::postaviPrimaoca(QListWidgetItem *primaoc)
{
    this->_primaoc = primaoc->text();
}

