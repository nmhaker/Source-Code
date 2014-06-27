#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->networkHandle = new NetworkHandle();
    this->_storageHandle = new StorageHandle();

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()), this, SLOT(primiPoruku()));

    this->spremnoZaIzlogovanje = false;

    obavestenje = new QLabel(this);
    obavestenje->setGeometry(QRect(349, 0, 489, 20));
    obavestenje->setStyleSheet("background-color:red;text:black;");
    obavestenje->setVisible(false);

    connect(this->ui->actionUloguj_Se, SIGNAL(triggered()), this, SLOT(ulogujSe()));
    connect(this->ui->actionIzadji, SIGNAL(triggered()), this, SLOT(izadji()));
    connect(this->ui->actionIzloguj_Se, SIGNAL(triggered()), this, SLOT(izlogujSe()));
    connect(this->ui->actionRegistruj_Se, SIGNAL(triggered()), this, SLOT(registrujSe()));
    connect(this->ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(posaljiPoruku()));
    connect(this->ui->listWidget_2, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(postaviPrimaoca(QListWidgetItem*)));

    connect(this->networkHandle, SIGNAL(shutdownApplication()), this, SLOT(izadji()));
    connect(this->networkHandle, SIGNAL(notification(QString)), this, SLOT(izbaciObavestenje(QString)));
    connect(this->networkHandle, SIGNAL(showStatusNotification()), this, SLOT(prikaziObavestenje()));
    connect(this->networkHandle, SIGNAL(showMessageNotification(QString,QString)), this, SLOT(prikaziPoruku(QString, QString)));
    connect(this->networkHandle, SIGNAL(setTimerInterval(int)), this, SLOT(postaviIntervalTajmera(int)));
    connect(this->networkHandle, SIGNAL(novaPoruka(QString)), this, SLOT(dodajNovuPorukuUlistWidget(QString)));
    connect(this->networkHandle, SIGNAL(dodajPrijateljeUlistWidget2(QString)), this, SLOT(dodajPrijateljeUlistWidget2(QString)));
    connect(this->networkHandle, SIGNAL(ocistiListWidget()), this->ui->listWidget, SLOT(clear()));
    connect(this->networkHandle, SIGNAL(ocistiListWidget2()), this->ui->listWidget_2, SLOT(clear()));
    connect(this->networkHandle, SIGNAL(potrebnoJeIzlogovatiSe()), this, SLOT(izlogujSe()));
    connect(this->networkHandle, SIGNAL(potrebnoJePonovoUlogovatiSe()), this, SLOT(ulogujSe()));
    connect(this->networkHandle, SIGNAL(promeniStanjeActionIzlogujSe(bool)), this->ui->actionIzloguj_Se, SLOT(setEnabled(bool)));
    connect(this->networkHandle, SIGNAL(promeniStanjeActionUlogujSe(bool)), this->ui->actionUloguj_Se, SLOT(setEnabled(bool)));
    connect(this->networkHandle, SIGNAL(startTimer()), this->timer, SLOT(start()));
    connect(this->networkHandle, SIGNAL(ubaciIdPorukeKorisnika(QString)), this, SLOT(ubaciIdPorukeKorisnika(QString)));
    connect(this->networkHandle, SIGNAL(ubaciIdPorukePrijatelja(QString)), this, SLOT(ubaciIdPorukePrijatelja(QString)));

    this->ui->actionIzloguj_Se->setDisabled(true);

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x, y);

    qDebug() << "Izlazim iz mainwindow konstruktora" << endl;
}

MainWindow::~MainWindow()
{
    delete obavestenje;
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
    this->networkHandle->receiveMessageFrom();
}

void MainWindow::izbaciObavestenje(const QString s)
{
    this->obavestenje->setText(s);
}

void MainWindow::prikaziObavestenje()
{
    this->obavestenje->show();
}

void MainWindow::prikaziPoruku(QString p, QString pp)
{
    QMessageBox::information(this, p, pp, QMessageBox::Ok);
}

void MainWindow::postaviIntervalTajmera(int msec)
{
    this->timer->setInterval(msec);
}

void MainWindow::dodajNovuPorukuUlistWidget(QString p)
{
    this->ui->listWidget->addItem(p);
}

void MainWindow::dodajPrijateljeUlistWidget2(QString p)
{
    this->ui->listWidget_2->addItem(p);
}

void MainWindow::ubaciIdPorukeKorisnika(QString id)
{
    this->_storageHandle->primljenePorukeKorisnika.append(id);
}

void MainWindow::ubaciIdPorukePrijatelja(QString id)
{
    this->_storageHandle->primljenePorukePrijatelja.append(id);
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
       QMessageBox::warning(this, "Upozorenje" ,"Vec ste izlogovani", QMessageBox::Ok);
    else
    {
        this->timer->stop();
        if(spremnoZaIzlogovanje)
        {
            this->_storageHandle->primljenePorukePrijatelja.clear();
            this->_storageHandle->primljenePorukeKorisnika.clear();
            this->_storageHandle->brojSpremnihPorukaPrijatelja = 0;
            this->_storageHandle->brojSpremnihPorukaKorisnika = 0;
            this->spremnoZaIzlogovanje = false;
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
        this->ui->listWidget->addItem(this->ui->lineEdit->text());
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
        if(this->_storageHandle->brojSpremnihPorukaPrijatelja < this->_storageHandle->primljenePorukePrijatelja.count())
        {
            this->networkHandle->updateStatusPorukePrijatelja(this->_storageHandle->primljenePorukePrijatelja.value(this->_storageHandle->brojSpremnihPorukaPrijatelja), "neprimljeno");
            this->_storageHandle->brojSpremnihPorukaPrijatelja++;
        }

        if(this->_storageHandle->brojSpremnihPorukaKorisnika < this->_storageHandle->primljenePorukeKorisnika.count())
        {
            this->networkHandle->updateStatusPorukeKorisnika(this->_storageHandle->primljenePorukeKorisnika.value(this->_storageHandle->brojSpremnihPorukaKorisnika), "neprimljeno");
            this->_storageHandle->brojSpremnihPorukaKorisnika++;
        }

        if((this->_storageHandle->brojSpremnihPorukaPrijatelja == this->_storageHandle->primljenePorukePrijatelja.count()) and (this->_storageHandle->brojSpremnihPorukaKorisnika == this->_storageHandle->primljenePorukeKorisnika.count()))
            this->spremnoZaIzlogovanje = true;
    }

}


