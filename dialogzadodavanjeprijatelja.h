#ifndef DIALOGZADODAVANJEPRIJATELJA_H
#define DIALOGZADODAVANJEPRIJATELJA_H

#include <QDialog>
#include <QDesktopWidget>
#include <QLabel>

namespace Ui {
class DialogZaDodavanjePrijatelja;
}

class DialogZaDodavanjePrijatelja : public QDialog
{
    Q_OBJECT

public:
    explicit DialogZaDodavanjePrijatelja(QWidget *parent = 0);
    ~DialogZaDodavanjePrijatelja();

private:
    Ui::DialogZaDodavanjePrijatelja *ui;

    QLabel status;

public slots:
    void posaljiInformaciju();
    void izbaciObavestenje(bool s);

signals:
    void salji(QString);
    void proveri(QString);
};

#endif // DIALOGZADODAVANJEPRIJATELJA_H
