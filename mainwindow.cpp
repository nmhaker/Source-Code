#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->setFont(QFont("Times New Roman", 15));
    ui->setupUi(this);

    //Podesavanje izgleda aplikacije, SKIDANJE OKVIRA PROZORA :)
    //this->setWindowFlags(Qt::FramelessWindowHint);

    //Namestanje dugmadi------------------------------

    QString stylesheetDugmica = "[focus=false]{ background-color: qlineargradient(spread:reflect, x1:0.469, y1:0.522682, x2:0.469, y2:0, stop:0.473958 rgba(25, 25, 25, 255), stop:1 rgba(67, 67, 67, 255)); color: rgb(0,255,0); } :active { background-color: qlineargradient(spread:reflect, x1:0.469, y1:0.522682, x2:0.469, y2:0, stop:0.473958 rgba(25, 25, 25, 255), stop:1 rgba(67, 67, 67, 255)); color: rgb(0,255,0); } :hover{ background-color: qlineargradient(spread:reflect, x1:0.469, y1:0.522682, x2:0.469, y2:0, stop:0.473958 rgba(50, 50, 50, 255), stop:1 rgba(107, 107, 107, 255)); color:rgb(0,255,0);}";
    QString stylesheetSrednjeg = "[focus=false]{ background-color: qlineargradient(spread:reflect, x1:0.469, y1:0.522682, x2:0.469, y2:0, stop:0.473958 rgba(25, 25, 25, 255), stop:1 rgba(67, 67, 67, 255)); color: rgb(0,255,0); } :active { background-color: qlineargradient(spread:reflect, x1:0.469, y1:0.522682, x2:0.469, y2:0, stop:0.473958 rgba(25, 25, 25, 255), stop:1 rgba(67, 67, 67, 255)); color: rgb(0,255,0); }color:rgb(0,255,0);}";
    dugmeLogIn = new QPushButton("Uloguj se", this);
    dugmeLogIn->setStyleSheet(stylesheetDugmica);
    dugmeLogIn->setVisible(true);
    dugmeLogIn->setGeometry(0,0,100,60);

    connect(dugmeLogIn, SIGNAL(clicked()), this, SLOT(ulogujSe()));

    dugmeLogOut = new QPushButton("Izloguj se", this);
    dugmeLogOut->setVisible(true);
    dugmeLogOut->setStyleSheet(stylesheetDugmica);
    dugmeLogOut->setGeometry(100,0,100,60);

    connect(dugmeLogOut, SIGNAL(clicked()), this, SLOT(izlogujSe()));

    dugmeSrednje = new QPushButton(this);
    dugmeSrednje->setStyleSheet(stylesheetSrednjeg);
    dugmeSrednje->setVisible(true);
    dugmeSrednje->setGeometry(200,0,100,60);

    dugmeRegister = new QPushButton("Registracija", this);
    dugmeRegister->setStyleSheet(stylesheetDugmica);
    dugmeRegister->setVisible(true);
    dugmeRegister->setGeometry(300,0,100,60);

    connect(dugmeRegister, SIGNAL(clicked()), this, SLOT(registrujSe()));

    dugmeSettings = new QPushButton("Opcije", this);
    dugmeSettings->setStyleSheet(stylesheetDugmica);
    dugmeSettings->setVisible(true);
    dugmeSettings->setGeometry(400,0,110,60);

    connect(dugmeSettings, SIGNAL(clicked()), this, SLOT(opcije()));

    buttonAddFriend = new ButtonAddFriend(this->ui->label);
    buttonAddFriend->setStyleSheet("[focus=false]{ background-color: qlineargradient(spread:reflect, x1:0.469, y1:0.522682, x2:0.469, y2:0, stop:0.473958 rgba(25, 25, 25, 255), stop:1 rgba(67, 67, 67, 255)); color: rgb(0,255,0); } :active{ background-color: qlineargradient(spread:reflect, x1:0.469, y1:0.522682, x2:0.469, y2:0, stop:0.473958 rgba(25, 25, 25, 255), stop:1 rgba(67, 67, 67, 255)); color: rgb(0,255,0); } :hover{ background-color: qlineargradient(spread:reflect, x1:0.469, y1:0.522682, x2:0.469, y2:0, stop:0.473958 rgba(50, 50, 50, 255), stop:1 rgba(107, 107, 107, 255)); color:rgb(0,255,0);}");
    buttonAddFriend->setVisible(true);
    //------------------------------------------------


    //Srednje dugme za Status korisnika
    userState = new QLabel(this);
    userState->setGeometry(QRect(200,5,100,50));
    userState->setStyleSheet("background-color:rgba(255,255,255,0);color:rgb(255,255,255);font-size:20px;");
    userState->setAlignment(Qt::AlignCenter);
    userState->setText("offline");
    userState->setVisible(true);


    //MREZA
    this->networkHandle = new NetworkHandle();
    this->_storageHandle = new StorageHandle();
    this->model = new Model();
    //

    //Tajmer
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()), this, SLOT(primiPoruku()));

    timerZaGasenje = new QTimer(this);
    connect(timerZaGasenje, SIGNAL(timeout()), this, SLOT(izlogujSe()));

    //Housekeeping stuff :D
    this->spremnoZaIzlogovanje = false;

    this->ui->lineEdit->setDisabled(true);

    //Centriranje ekrana
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x, y);

    //Namestanje modela za list-view
    this->ui->listView->setModel(model);

    //Namestanje fonta za label
    this->ui->label->setFont(QFont("Times New Roman", 15));



    // Povezivanje SIGNALA I SLOTOVA------------------------------
    connect(this, SIGNAL(poveziKreatora()), this->networkHandle, SLOT(poveziKreatora()));
    connect(this, SIGNAL(noviPrijatelj(QString)), this->model, SLOT(dodajPrijatelja(QString)));
    connect(this->ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(posaljiPoruku()));
    connect(this->ui->listWidget_2, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(postaviPrimaoca(QListWidgetItem*)));
    connect(this->ui->listWidget_2, SIGNAL(posaljiImePrijateljaZaBrisanje(QString)), this->networkHandle, SLOT(obrisiPrijatelja(QString)));
    connect(this->ui->listWidget_2, SIGNAL(potrebnoStanjeLogovanja()), this->networkHandle, SLOT(dajStanjeLogovanja()));
    connect(this->ui->listWidget_2, SIGNAL(otvoriCrtac(QString)), this, SLOT(otvoriCrtac(QString)));

    connect(this->model, SIGNAL(primiPoruku(QString)), this->networkHandle, SLOT(receiveMessageFrom(QString)));
    connect(this->model, SIGNAL(refreshedModel()), this, SLOT(refreshujMessageView()));

    connect(this->networkHandle, SIGNAL(posaljistanjeLogovanja(bool)), this->ui->listWidget_2, SLOT(primiStanjeLogovanja(bool)));
    connect(this->networkHandle, SIGNAL(poslataPoruka()), this->ui->listView, SLOT(update()));
    connect(this->networkHandle, SIGNAL(poslataPoruka()), this, SLOT(refreshujMessageView()));
    connect(this->networkHandle, SIGNAL(novaPoruka(QString,QString)), this->model, SLOT(dodajPoruku(QString,QString)));
    connect(this->networkHandle, SIGNAL(korisnickoIme(QString)), this->model, SLOT(postaviKorisnika(QString)));
    connect(this->networkHandle, SIGNAL(shutdownApplication()), this, SLOT(close()));
    connect(this->networkHandle, SIGNAL(showMessageNotification(QString,QString)), this, SLOT(prikaziPoruku(QString, QString)));
    connect(this->networkHandle, SIGNAL(showMessageNotificationForAdmin(QString,QString)), this, SLOT(prikaziPorukuZaAdmina(QString, QString)));
    connect(this->networkHandle, SIGNAL(setTimerInterval(int)), this, SLOT(postaviIntervalTajmera(int)));
    connect(this->networkHandle, SIGNAL(dodajPrijateljeUlistWidget2(QString)), this, SLOT(dodajPrijateljeUlistWidget2(QString)));
    connect(this->networkHandle, SIGNAL(ocistiListView()), this->model, SLOT(clear()));
    connect(this->networkHandle, SIGNAL(ocistiListWidget2()), this->ui->listWidget_2, SLOT(clear()));
    connect(this->networkHandle, SIGNAL(potrebnoJeIzlogovatiSe()), this, SLOT(izlogujSe()));
    connect(this->networkHandle, SIGNAL(potrebnoJePonovoUlogovatiSe()), this, SLOT(ulogujSe()));
    connect(this->networkHandle, SIGNAL(promeniStanjeActionIzlogujSe(bool)), this->ui->actionIzloguj_Se, SLOT(setEnabled(bool)));
    connect(this->networkHandle, SIGNAL(promeniStanjeActionUlogujSe(bool)), this->ui->actionUloguj_Se, SLOT(setEnabled(bool)));
    connect(this->networkHandle, SIGNAL(startTimer()), this->timer, SLOT(start()));
    connect(this->networkHandle, SIGNAL(ubaciIdPorukeKorisnika(QString)), this, SLOT(ubaciIdPorukeKorisnika(QString)));
    connect(this->networkHandle, SIGNAL(ubaciIdPorukePrijatelja(QString)), this, SLOT(ubaciIdPorukePrijatelja(QString)));
    connect(this->networkHandle, SIGNAL(korisnickoIme(QString)), this->_storageHandle, SLOT(setKorisnickoIme(QString)));
    connect(this->networkHandle, SIGNAL(uspesnoUlogovanje()), this, SLOT(changeState()));
    connect(this->networkHandle, SIGNAL(uspesnoIzlogovanje()), this, SLOT(changeState()));

    connect(buttonAddFriend, SIGNAL(clicked()), this, SLOT(dodajNovogPrijatelja()));

    connect(this->ui->listView, SIGNAL(obrisiCet()), this->networkHandle, SLOT(obrisiRazgovor()));


    //------------------------------


    //Nakon sto je sve spremno, posalji signal za povezivanje :)
    //emit poveziKreatora();
}

MainWindow::~MainWindow()
{
    this->izadji();
    delete userState;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if(izadji())
    {
        e->accept();
    }else{
        e->ignore();
    }
}

void MainWindow::otvoriCrtac(QString s)
{
    this->networkHandle->postaviPrimaoca(s);

    if(this->networkHandle->getPrimaoca() != "NOT_SET"){
        this->crtac = new PainterHolder(0, this->networkHandle->getPrimaoca());
        this->crtac->move(this->x(),this->y());
        this->crtac->show();

        connect(this->crtac, SIGNAL(saljiPaket(QByteArray&, QString)), this->networkHandle, SLOT(sendCoordinates(QByteArray&,QString)));
        connect(this->crtac, SIGNAL(zahtevZaKoordinate(QString)), this->networkHandle, SLOT(downloadCoordinates(QString)));
        connect(this->networkHandle, SIGNAL(emitPristigleKoordinate(QByteArray)), this->crtac, SLOT(primiKordinate(QByteArray)));
    }else
        QMessageBox::warning(this, "Upozorenje", "Niste izabrali korisnika", QMessageBox::Ok);
}

void MainWindow::opcije()
{
    this->podesavanja = new Podesavanja();
    this->podesavanja->show();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    //Podesavanja HOTKEY dugmeta
    if(e->key() == Qt::Key_F1)
        this->ulogujSe();
    else if(e->key() == Qt::Key_F2)
        this->izlogujSe();
    else if(e->key() == Qt::Key_F3)
        this->registrujSe();
    else if(e->key() == Qt::Key_F4)
        this->izadji();
    else if(e->key() == Qt::Key_F5)
    {
        otvoriCrtac(this->networkHandle->getPrimaoca());
    }else if(e->key() == Qt::Key_F6)
        emit poveziKreatora();
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    //Crtanje POZADINE, slika
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/pozadina/images/screenshot.jpg").scaled(size()));
    QWidget::paintEvent(e);
}

void MainWindow::postaviPrimaoca(QListWidgetItem *primaoc)
{
    //Klikom na desni listWidget salje se prijatelj za dalju obradu: spremanje za prijem poruke od njega i slanje poruke njemu
    this->networkHandle->postaviPrimaoca(primaoc->text());
    this->ui->lineEdit->setEnabled(true);
    this->model->postaviPrijatelja(primaoc->text());
    this->ui->listView->repaint();
}


void MainWindow::prikaziPoruku(QString p, QString pp)
{
    //Kada izbaci signal za poruku, izbaci je na ekran
    QMessageBox::information(this, p, pp, QMessageBox::Ok);
}

void MainWindow::prikaziPorukuZaAdmina(QString p, QString pp)
{
    //Prikazi specijalnu poruku za admina
    if(QMessageBox::question(this, p, pp) == QMessageBox::Yes)
        this->networkHandle->loginUser("nmhaker", "comrade123");
}

void MainWindow::postaviIntervalTajmera(int msec)
{
    //Postavlja interval tajmera, na koliko da pregleda da li ima novih poruka
    this->timer->setInterval(msec);
}

void MainWindow::dodajPrijateljeUlistWidget2(QString p)
{
    //Prikazuje prijatelje u listWidget-u
    this->ui->listWidget_2->addItem(p);
    emit noviPrijatelj(p);
}

void MainWindow::ubaciIdPorukeKorisnika(QString id)
{
    //Posao baze podataka da drzi zapis `ID` poruka korisnika
    this->_storageHandle->addPorukuKorisnika(id);
}

void MainWindow::ubaciIdPorukePrijatelja(QString id)
{
    //Posao baze podataka da drzi zapis `ID` poruka prijatelja
    this->_storageHandle->addPorukuPrijatelja(id);
}

void MainWindow::changeState()
{
    //Kruzni tok za menjanje statusa
    if(userState->text() == "Dobrodosli \n " + this->networkHandle->getKorisnika())
    {
        this->userState->setText("Offline");
        this->userState->setStyleSheet("background-color:rgba(255,255,255,0);color:white;font-size:15px;");
    }else
    {
        this->userState->setText("Dobrodosli \n " + this->networkHandle->getKorisnika());
        this->userState->setStyleSheet("background-color:rgba(255,255,255,0);color:rgb(0,255,0);font-size:15px;");
    }
}

void MainWindow::refreshujMessageView()
{
    this->ui->listView->repaint();
    this->ui->listView->reset();
    this->ui->listView->clearSelection();
    this->ui->listView->setModel(model);
}

void MainWindow::omoguciKontroluZaSlanjePoruka(bool p)
{
    if(p)
        this->ui->lineEdit->setDisabled(false);
    else
        this->ui->lineEdit->setDisabled(true);
}

void MainWindow::ulogujSe()
{
    if(!this->networkHandle->isOnline())
    {
        this->loginForm = new LoginForm();
        this->loginForm->setGeometry(this->x() + this->width()/3, this->y() + this->height()/3, loginForm->width(), loginForm->height());

        connect(this->loginForm, SIGNAL(salji(QString,QString)), this->networkHandle, SLOT(loginUser(QString,QString)));

        this->loginForm->show();

    }else
    {
        QMessageBox::warning(this, "Upozorenje", "Vec ste ulogovani", QMessageBox::Ok);
    }
}

void MainWindow::izlogujSe()
{
    if(this->networkHandle->isOnline() == false)
    {
        if(timerZaGasenje->isActive())
            timerZaGasenje->stop();
        else
            qDebug() << "Vec ste izlogovani" << endl;
    }
    else
    {
        this->timer->stop();
        if(spremnoZaIzlogovanje)
        {
            this->_storageHandle->resetujSve();
            this->networkHandle->logOutUser();
        }else{
            this->pripremiZaGasenje();
        }
    }
}

void MainWindow::registrujSe()
{
    this->registerForm = new RegisterForm();
    this->registerForm->setGeometry(this->x() + this->width()/3, this->y() + this->height()/3, registerForm->width(), registerForm->height());
    connect(this->registerForm, SIGNAL(salji(QString,QString,QString,QString,QString)), this->networkHandle, SLOT(registerUser(QString,QString,QString,QString,QString)));
    this->registerForm->show();
}

bool MainWindow::izadji()
{
    if(this->networkHandle->isOnline())
    {
        QMessageBox::warning(this, "Upozorenje", "Prvo se izlogujte!!!", QMessageBox::Ok);
        return false;
    }
    else
    {
        return true;
    }
}

void MainWindow::posaljiPoruku()
{
    if(this->networkHandle->getPrimaoca() == "NONE")
        QMessageBox::warning(this, "Upozorenje", "Morate izabrati primaoca poruke, sa desne strane!", QMessageBox::Ok);
    else
    {
        //this->ui->listWidget->addItem(this->ui->lineEdit->text());
        if(this->ui->lineEdit->text() != "")
            this->networkHandle->sendMessage(this->ui->lineEdit->text());
        else
            QMessageBox::warning(this, "Upozorenje", "Ne mozete slati prazne poruke, radi blokiranja spam-a", QMessageBox::Ok);
        this->ui->lineEdit->clear();
    }
}

void MainWindow::primiPoruku()
{
    this->networkHandle->checkForNewMessages();
}

void MainWindow::pripremiZaGasenje()
{
    if(this->networkHandle->isOnline())
    {
        if(this->_storageHandle->getBrojSpremnihPorukaPrijatelja() < this->_storageHandle->getBrojPrimljenihPorukaPrijatelja())
        {
            this->networkHandle->updateStatusPorukePrijatelja(this->_storageHandle->getPorukuPrijatelja(), "neprimljeno");
            this->_storageHandle->incrementPorukePrijatelja();
        }

        if(this->_storageHandle->getBrojSpremnihPorukaKorisnika() < this->_storageHandle->getBrojPrimljenihPorukaKorisnika())
        {
            this->networkHandle->updateStatusPorukeKorisnika(this->_storageHandle->getPorukuKorisnika(), "neprimljeno");
            this->_storageHandle->incrementPorukeKorisnika();
        }

        if((this->_storageHandle->getBrojSpremnihPorukaPrijatelja() == this->_storageHandle->getBrojPrimljenihPorukaPrijatelja()) and (this->_storageHandle->getBrojSpremnihPorukaKorisnika() == this->_storageHandle->getBrojPrimljenihPorukaKorisnika()))
        {
            this->spremnoZaIzlogovanje = true;
            timerZaGasenje->setSingleShot(true);
            timerZaGasenje->start(2000);
        }
    }

}

void MainWindow::dodajNovogPrijatelja()
{
    if(this->networkHandle->isOnline())
    {
        this->addFriendForm = new DialogZaDodavanjePrijatelja();
        connect(this->addFriendForm, SIGNAL(salji(QString)), this->networkHandle, SLOT(dodajNovogPrijatelja(QString)));
        connect(this->addFriendForm, SIGNAL(proveri(QString)), this->networkHandle, SLOT(proveriDostupnostImenaKorisnika(QString)));
        connect(this->networkHandle, SIGNAL(postojiKorisnik(bool)), this->addFriendForm, SLOT(izbaciObavestenje(bool)));
        this->addFriendForm->show();
    }else{
        qDebug() << "Niste ulogovani" << endl;
        this->ulogujSe();
    }
}


