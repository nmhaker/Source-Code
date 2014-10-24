#ifndef PAINTERSCREEN_H
#define PAINTERSCREEN_H

#include <QWidget>
#include <QDebug>
#include <QVector>
#include <QPoint>
#include <QMouseEvent>

class PainterScreen : public QWidget
{
    Q_OBJECT
public:
    explicit PainterScreen(QWidget *parent = 0);

protected:

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);


private:

    QVector<QPoint> tacke, tackePrijatelja;


    bool pretisnutoDugme;

signals:

public slots:

};

#endif // PAINTERSCREEN_H
