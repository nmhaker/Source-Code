#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->mode = "DEPLOY";

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
    timer->setInterval(4000);
    connect(timer,SIGNAL(timeout()), this, SLOT(primiPoruku()));

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x, y);
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

void MainWindow::prepareConnection()
{
    this->networkAccessManager = new QNetworkAccessManager(this);

    connect(this->networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleRequestResponse(QNetworkReply*)));

    if(this->mode == "DEVELOPMENT")
        this->networkRequest = new QNetworkRequest(QUrl("http://localhost/milutinac/Server.php"));
    else if(this->mode == "DEPLOY")
        this->networkRequest = new QNetworkRequest(QUrl("http://milutinac.eu5.org/Server.php"));

    this->networkRequest->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
}

void MainWindow::loginUser(const QString korisnicko_ime, const QString sifra)
{
    this->_korisnicko_ime = korisnicko_ime;
    this->_online = true;

    QUrlQuery params;
    params.addQueryItem("key", "SIFRA");
    params.addQueryItem("action", "2");
    params.addQueryItem("korisnicko_ime", korisnicko_ime);
    params.addQueryItem("sifra", sifra);

    QByteArray data = params.query(QUrl::FullyEncoded).toUtf8();

    this->networkAccessManager->post(*(this->networkRequest), data);

    this->ui->actionUloguj_Se->setDisabled(true);
    this->ui->actionIzloguj_Se->setDisabled(false);

    timer->start();
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

    this->ui->actionIzloguj_Se->setDisabled(true);
    this->ui->actionUloguj_Se->setDisabled(false);

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

void MainWindow::handleRequestResponse(QNetworkReply *r)
{
    QByteArray msg = r->readAll();
    QString str;

    for(int i=0;i<msg.length();i++)
        str.append(msg.at(i));

    //Handling response
    //if(str.contains())


    this->ui->listWidget->addItem(str);
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
        this->logOutUser(this->_korisnicko_ime);
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
        this->izlogujSe();
        this->close();
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

