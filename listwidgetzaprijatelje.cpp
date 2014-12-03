#include "listwidgetzaprijatelje.h"

ListWidgetZaPrijatelje::ListWidgetZaPrijatelje(QWidget *parent) :
    QListWidget(parent)
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showMenu(QPoint)));
}

void ListWidgetZaPrijatelje::showMenu(const QPoint &pos)
{
    this->popupWidget = new PopupWidgetMenu(this);
    this->popupWidget->move(this->viewport()->mapToGlobal(pos));
    //this->popupWidget->setStyleSheet("background-color:red;");
    this->popupWidget->show();

    qDebug() << "Unutar contextMenu" << endl;
}


//POPUPWIDGETMENU
PopupWidgetMenu::PopupWidgetMenu(QWidget *parent) : QDialog(parent)
{
    this->setGeometry(this->x(), this->y(), 300,300);
    this->setWindowFlags(Qt::Popup);

    //Setup UI

    this->vLay = new QVBoxLayout(this);
    this->deleteFriend_button = new QPushButton("Izbrisi Prijatelja", this);
    this->vLay->addWidget(this->deleteFriend_button);
    this->setGeometry(vLay->geometry());

    connect(this->deleteFriend_button, SIGNAL(clicked()), this, SLOT(handle_DeleteFriend()));

    timer = new QTimer(this);
    timer->setInterval(2000);
    connect(timer, SIGNAL(timeout()), this, SLOT(close()));
    timer->start();
}

void PopupWidgetMenu::handle_DeleteFriend()
{
    //Send a signal for deleting a friend
    this->close();
}
