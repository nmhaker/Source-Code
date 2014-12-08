#ifndef DUGMAD_H
#define DUGMAD_H

#include <QWidget>

class Dugmad : public QWidget{
    Q_OBJECT
public:
    explicit Dugmad(QWidget *parent = 0);
protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

    QLinearGradient lg;
private:

signals:
    void clicked();
};



#endif // DUGMAD_H
