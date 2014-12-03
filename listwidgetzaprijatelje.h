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
signals:

public slots:
    void showMenu(const QPoint &pos);

};



#endif // LISTWIDGETZAPRIJATELJE_H
