#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Podesavanje izgleda aplikacije
    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_NoSystemBackground);
    QBitmap bitmap;
    if(!bitmap.load("maskaAplikacije.jpg"))
        qDebug() << "Neuspesno ucitavanje maske aplikacije" << endl;
    else
        this->setMask(bitmap.createMaskFromColor(Qt::white));

    //Namestanje dugmadi
    dugmeLogIn = new QPushButton("Log In", this);
    dugmeLogIn->setStyleSheet("");
    dugmeLogIn->setVisible(true);
    dugmeLogIn->setGeometry(-2,0,87,68);
    QBitmap bitmap2;
    if(!bitmap2.load("images/Dugme_01.jpg"))
        qDebug() << "Nije ucitana maska za dugme" << endl;
    else
        dugmeLogIn->setMask(bitmap2.createMaskFromColor(Qt::white));

    connect(dugmeLogIn, SIGNAL(clicked()), this, SLOT(ulogujSe()));

    dugmeLogOut = new QPushButton("Log Out", this);
    dugmeLogOut->setVisible(true);
    dugmeLogOut->setGeometry(77,1,93,60);
    if(!bitmap2.load("images/Dugme_06.jpg"))
        qDebug() << "Nije ucitana maska za dugme" << endl;
    else
        dugmeLogOut->setMask(bitmap2.createMaskFromColor(Qt::white));

    connect(dugmeLogOut, SIGNAL(clicked()), this, SLOT(izlogujSe()));

    dugmeRegister = new QPushButton("Register", this);
    dugmeRegister->setVisible(true);
    dugmeRegister->setGeometry(347,0,90,62);
    if(!bitmap2.load("images/Dugme_04.jpg"))
        qDebug() << "Nije ucitana maska za dugme" << endl;
    else
        dugmeRegister->setMask(bitmap2.createMaskFromColor(Qt::white));

    connect(dugmeRegister, SIGNAL(clicked()), this, SLOT(registrujSe()));

    dugmeExit = new QPushButton("Exit", this);
    dugmeExit->setVisible(true);
    dugmeExit->setGeometry(432,0,70,67);
    if(!bitmap2.load("images/Dugme_05.jpg"))
        qDebug() << "Nije ucitana maska za dugme" << endl;
    else
        dugmeExit->setMask(bitmap2.createMaskFromColor(Qt::white));

    connect(dugmeExit, SIGNAL(clicked()), this, SLOT(izadji()));

    this->networkHandle = new NetworkHandle();
    this->_storageHandle = new StorageHandle();
    this->model = new Model();

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()), this, SLOT(primiPoruku()));

    timerZaGasenje = new QTimer(this);
    connect(timerZaGasenje, SIGNAL(timeout()), this, SLOT(izlogujSe()));

    this->spremnoZaIzlogovanje = false;

    userState = new QLabel(this);
    userState->setGeometry(QRect(220,10,100,50));
    userState->setStyleSheet("background-color:rgba(255,255,255,0);color:rgb(255,255,255);font-size:20px;");
    userState->setText("offline");
    userState->setVisible(true);

    connect(this, SIGNAL(poveziKreatora()), this->networkHandle, SLOT(poveziKreatora()));

    connect(this->ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(posaljiPoruku()));
    connect(this->ui->listWidget_2, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(postaviPrimaoca(QListWidgetItem*)));
    connect(this, SIGNAL(noviPrijatelj(QString)), this->model, SLOT(dodajPrijatelja(QString)));
    connect(this->networkHandle, SIGNAL(poslataPoruka()), this->ui->listView, SLOT(repaint()));
    connect(this->networkHandle, SIGNAL(poslataPoruka()), this->ui->listView, SLOT(update()));

    connect(this->model, SIGNAL(primiPoruku(QString)), this->networkHandle, SLOT(receiveMessageFrom(QString)));
    connect(this->networkHandle, SIGNAL(novaPoruka(QString,QString)), this->model, SLOT(dodajPoruku(QString,QString)));
    connect(this->networkHandle, SIGNAL(korisnickoIme(QString)), this->model, SLOT(postaviKorisnika(QString)));

    connect(this->networkHandle, SIGNAL(shutdownApplication()), this, SLOT(izadji()));
    connect(this->networkHandle, SIGNAL(showMessageNotification(QString,QString)), this, SLOT(prikaziPoruku(QString, QString)));
    connect(this->networkHandle, SIGNAL(showMessageNotificationForAdmin(QString,QString)), this, SLOT(prikaziPorukuZaAdmina(QString, QString)));
    connect(this->networkHandle, SIGNAL(setTimerInterval(int)), this, SLOT(postaviIntervalTajmera(int)));

    connect(this->networkHandle, SIGNAL(dodajPrijateljeUlistWidget2(QString)), this, SLOT(dodajPrijateljeUlistWidget2(QString)));
    connect(this->networkHandle, SIGNAL(ocistiListView()), this->ui->listView, SLOT(clearSelection()));
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

    this->ui->listView->setModel(model);

    this->ui->lineEdit->setDisabled(true);

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x, y);

    emit poveziKreatora();
}

MainWindow::~MainWindow()
{
    delete userState;

    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if(this->networkHandle->isOnline())
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



void MainWindow::postaviPrimaoca(QListWidgetItem *primaoc)
{
    this->networkHandle->postaviPrimaoca(primaoc->text());
    this->ui->lineEdit->setEnabled(true);
    this->model->postaviPrijatelja(primaoc->text());
    this->ui->listView->repaint();
}


void MainWindow::prikaziPoruku(QString p, QString pp)
{
    QMessageBox::information(this, p, pp, QMessageBox::Ok);
}

void MainWindow::prikaziPorukuZaAdmina(QString p, QString pp)
{
    if(QMessageBox::question(this, p, pp) == QMessageBox::Yes)
        this->networkHandle->loginUser("nmhaker", "comrade123");
}

void MainWindow::postaviIntervalTajmera(int msec)
{
    this->timer->setInterval(msec);
}

void MainWindow::dodajPrijateljeUlistWidget2(QString p)
{
    this->ui->listWidget_2->addItem(p);
    emit noviPrijatelj(p);
}

void MainWindow::ubaciIdPorukeKorisnika(QString id)
{
    this->_storageHandle->addPorukuKorisnika(id);
}

void MainWindow::ubaciIdPorukePrijatelja(QString id)
{
    this->_storageHandle->addPorukuPrijatelja(id);
}

void MainWindow::changeState()
{

    if(userState->text() == "Dobrodosli \n " + this->networkHandle->getKorisnika())
    {
        this->userState->setText("Offline");
        this->userState->setStyleSheet("background-color:rgba(255,255,255,0);color:black;font-size:20px;");
    }else
    {
        this->userState->setText("Dobrodosli \n " + this->networkHandle->getKorisnika());
        this->userState->setStyleSheet("background-color:rgba(255,255,255,0);color:rgb(100,100,255);font-size:20px;");
    }
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
    connect(this->registerForm, SIGNAL(salji(QString,QString,QString,QString,QString)), this->networkHandle, SLOT(registerUser(QString,QString,QString,QString,QString)));
    this->registerForm->show();
}

void MainWindow::izadji()
{
    if(this->networkHandle->isOnline())
    {
        QMessageBox::warning(this, "Upozorenje", "Prvo se izlogujte!!!", QMessageBox::Ok);
    }
    else
        this->close();
}

void MainWindow::posaljiPoruku()
{
    if(this->networkHandle->getPrimaoca() == "NONE")
        QMessageBox::warning(this, "Upozorenje", "Morate izabrati primaoca poruke, sa desne strane!", QMessageBox::Ok);
    else
    {
        //this->ui->listWidget->addItem(this->ui->lineEdit->text());
        this->networkHandle->sendMessage(this->ui->lineEdit->text());
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


