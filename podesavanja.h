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
signals:

public slots:
};

#endif // PODESAVANJA_H
