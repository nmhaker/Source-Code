#ifndef POMERAC_H
#define POMERAC_H

#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QBitmap>
#include <QLabel>

class Pomerac : public QWidget
{
    Q_OBJECT
public:
    explicit Pomerac(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    QPoint offset;

    QLabel text;

signals:
    void pozicijaPromenjena();

public slots:

};

#endif // POMERAC_H
