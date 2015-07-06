#ifndef PODESAVANJA_H
#define PODESAVANJA_H

#include <QWidget>

namespace Ui{
class Podesavanja;
}

class Podesavanja : public QWidget
{
    Q_OBJECT
public:
    explicit Podesavanja(QWidget *parent = 0);
    ~Podesavanja();

private:
    Ui::Podesavanja *ui;

    QString ime, prezime, staraSifra, novaSifra;
    QImage profilnaSlika;


signals:
    void podaci(QString ime, QString prezime, QString staraSifra, QString novaSifra, QImage profilnaSlika);
public slots:

private slots:
    void saljiPodatke();
};

#endif // PODESAVANJA_H
