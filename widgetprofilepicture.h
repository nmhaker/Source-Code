#ifndef WIDGETPROFILEPICTURE_H
#define WIDGETPROFILEPICTURE_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QFileDialog>
#include <QDebug>

class WidgetProfilePicture : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetProfilePicture(QWidget *parent = 0);
    QImage profileImage;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

private:


signals:

public slots:
};

#endif // WIDGETPROFILEPICTURE_H
