#ifndef LISTWIDGETZAPRIJATELJE_H
#define LISTWIDGETZAPRIJATELJE_H


#include <QDialog>
#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>

class PopupWidgetMenu : public QDialog
{
    Q_OBJECT
public:
    explicit PopupWidgetMenu(QWidget *parent = 0);

protected:

private:
    QVBoxLayout *vLay;
    QPushButton *deleteFriend_button;
    QPushButton *pokreniCrtanje_button;
    QTimer *timer;

private slots:
    void handle_DeleteFriend();
    void handle_PokreniCrtanje();

signals:
    void obrisiPrijatelja();
    void pokreniCrtac();

};

#include <QListWidget>

class ListWidgetZaPrijatelje : public QListWidget
{
    Q_OBJECT
public:
    explicit ListWidgetZaPrijatelje(QWidget *parent = 0);

protected:

private:
    PopupWidgetMenu *popupWidget;

    QPoint lastPoint;

    bool online;
signals:
    void posaljiImePrijateljaZaBrisanje(const QString & ime_prijatelja);
    void potrebnoStanjeLogovanja();
    void otvoriCrtac(const QString & ime_prijatelja);

public slots:
    void showMenu(const QPoint &pos);
    void handleObrisiPrijatelja();
    void handlePokreniCrtac();
    void primiStanjeLogovanja(bool p);

};



#endif // LISTWIDGETZAPRIJATELJE_H
