#include "listwidgetzaprijatelje.h"


//POPUPWIDGETMENU
PopupWidgetMenu::PopupWidgetMenu(QWidget *parent) : QDialog(parent)
{
    this->setWindowFlags(Qt::Popup);

    //Setup UI

    this->setGeometry(0,0, 100, 50);

    this->deleteFriend_button = new QPushButton("Izbrisi Prijatelja", this);
    this->deleteFriend_button->setGeometry(QRect(0,0,100,25));
    connect(this->deleteFriend_button, SIGNAL(clicked()), this, SLOT(handle_DeleteFriend()));

    this->pokreniCrtanje_button = new QPushButton("Otvori Crtac", this);
    this->pokreniCrtanje_button->setGeometry(QRect(0,25,100,25));
    connect(this->pokreniCrtanje_button, SIGNAL(clicked()), this, SLOT(handle_PokreniCrtanje()));

    timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(close()));
    timer->start();
}

void PopupWidgetMenu::handle_DeleteFriend()
{
    emit obrisiPrijatelja();
    this->close();
}

void PopupWidgetMenu::handle_PokreniCrtanje()
{
    emit pokreniCrtac();
    this->close();
}

//LISTWIDGETZAPRIJATELJE
ListWidgetZaPrijatelje::ListWidgetZaPrijatelje(QWidget *parent) :
    QListWidget(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showMenu(QPoint)));

    emit potrebnoStanjeLogovanja();
}

void ListWidgetZaPrijatelje::showMenu(const QPoint &pos)
{
    emit potrebnoStanjeLogovanja();
    if(online)
    {
        this->popupWidget = new PopupWidgetMenu(this);
        this->popupWidget->move(this->viewport()->mapToGlobal(pos));
        this->popupWidget->show();

        connect(this->popupWidget, SIGNAL(obrisiPrijatelja()), this, SLOT(handleObrisiPrijatelja()));
        connect(this->popupWidget, SIGNAL(pokreniCrtac()), this, SLOT(handlePokreniCrtac()));

        lastPoint = pos;

        qDebug() << "Pozicija indexa je: " << lastPoint << endl;
    }else
        qDebug() << "Niste ulogovani" << endl;
}

void ListWidgetZaPrijatelje::handleObrisiPrijatelja()
{
    emit posaljiImePrijateljaZaBrisanje(this->itemAt(lastPoint)->text());
    qDebug() << "Saljem ime primaoca za brisanje: " << this->itemAt(lastPoint)->text() << endl;
}

void ListWidgetZaPrijatelje::handlePokreniCrtac()
{
    emit otvoriCrtac(this->itemAt(lastPoint)->text());
    qDebug() << "Otvaram crtac za prijatelja: " << this->itemAt(lastPoint)->text();
}

void ListWidgetZaPrijatelje::primiStanjeLogovanja(bool p)
{
    this->online = p;
}

