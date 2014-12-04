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
    QTimer *timer;

private slots:
    void handle_DeleteFriend();

signals:
    void obrisiPrijatelja();

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

public slots:
    void showMenu(const QPoint &pos);
    void handleObrisiPrijatelja();
    void primiStanjeLogovanja(bool p);

};



#endif // LISTWIDGETZAPRIJATELJE_H
