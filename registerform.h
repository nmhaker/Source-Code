#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QWidget>

namespace Ui {
class RegisterForm;
}

class RegisterForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterForm(QWidget *parent = 0);
    ~RegisterForm();

private:
    Ui::RegisterForm *ui;

public slots:
    void posaljiPodatke();

signals:
    void salji(const QString ime, const QString prezime, const QString korisnicko_ime, const QString sifra, const QString mobilni);
};

#endif // REGISTERFORM_H
