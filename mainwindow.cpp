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

    this->brojSpremnihPoruka = 0;

    this->prepareConnection();

    connect(this->ui->actionUloguj_Se, SIGNAL(triggered()), this, SLOT(ulogujSe()));
    connect(this->ui->actionIzadji, SIGNAL(triggered()), this, SLOT(izadji()));
    connect(this->ui->actionIzloguj_Se, SIGNAL(triggered()), this, SLOT(izlogujSe()));
    connect(this->ui->actionRegistruj_Se, SIGNAL(triggered()), this, SLOT(registrujSe()));
    connect(this->ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(posaljiPoruku()));

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
    this->_online = false;

    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "5");
    params.addQueryItem("korisnicko_ime", korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->networkAccessManager->post(*(this->networkRequest), data);

    this->timer->stop();
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

void MainWindow::receiveMessage(const QString korisnicko_ime)
{
    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "3");
    params.addQueryItem("korisnicko_ime", korisnicko_ime);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->networkAccessManager->post(*(this->networkRequest), data);
}

void MainWindow::updateStatusPoruke(const QString id, const QString status)
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
            QMessageBox::information(this, "Obavestenje", "Nemate novih poruka", QMessageBox::Ok);
            this->novePoruke = false;
            timer->setInterval(4000);
        }
    }
    else if(str.contains("RESPONSE_101"))
    {
        timer->setInterval(1000);
        if(str.contains("RESPONSE_109"))
        {
            QStringList list = str.split("\n");
            //list.removeAt(0);
            this->ui->listWidget->addItem(list.value(2));
            QString id  = list.value(1);
            primljenePoruke.append(id);
            this->updateStatusPoruke(id, "primljeno");        
        }else{
        QStringList list = str.split("\n");
        //list.removeAt(0);
        this->ui->listWidget->addItem(list.value(2));
        QString id  =list.value(1);
        primljenePoruke.append(id);
        this->updateStatusPoruke(id, "primljeno");
        }
    }else if(str.contains("RESPONSE_110"))
    {
        qDebug() << "Uspesno updateovana poruka na 'primljeno' " << endl;
    }else if(str.contains("RESPONSE_111"))
    {
        qDebug() << "Uspesno updateovana poruka na 'neprimljeno' " << endl;
        this->brojSpremnihPoruka++;
        this->izlogujSe();
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
            this->primljenePoruke.clear();
            this->brojSpremnihPoruka = 0;
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
    //this->sendMessage(this->_korisnicko_ime,   , this->ui->lineEdit->text());
}


void MainWindow::primiPoruku()
{
    this->receiveMessage(this->_korisnicko_ime);
}

void MainWindow::pripremiZaGasenje()
{
    if(this->brojSpremnihPoruka <= primljenePoruke.length())
        this->updateStatusPoruke(primljenePoruke.value(brojSpremnihPoruka), "neprimljeno");

    if(brojSpremnihPoruka == primljenePoruke.length())
        this->spremnoZaIzlogovanje = true;

    qDebug() << brojSpremnihPoruka << endl;
    qDebug() << primljenePoruke << endl;
}

