#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

private:
    Ui::LoginForm *ui;

public slots:
    void posaljiPodatke();

signals:
    void salji(const QString korisnicko_ime, const QString sifra);
};

#endif // LOGINFORM_H
