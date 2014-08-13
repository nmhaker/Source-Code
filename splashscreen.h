#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QLayout>
#include <QGridLayout>

#include "mainwindow.h"

class SplashScreen : public QWidget
{
    Q_OBJECT
public:
    explicit SplashScreen(QWidget *parent = 0);

    QMainWindow *mainWindow;

protected:
    void paintEvent(QPaintEvent *);

private:
    QTimer tajmer;

signals:

public slots:

protected slots:
    void zatvoriSplashScreen();

};

#endif // SPLASHSCREEN_H
