#ifndef BUTTONADDFRIEND_H
#define BUTTONADDFRIEND_H

#include <QPushButton>
#include <QPainter>

class ButtonAddFriend : public QPushButton
{
    Q_OBJECT
public:
    explicit ButtonAddFriend(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:

};

#endif // BUTTONADDFRIEND_H
