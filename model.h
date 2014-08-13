#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>
#include <QDebug>
#include <QBrush>
#include <QMapIterator>
#include <QDebug>
#include "Poruka.h"

class Model : public QAbstractListModel
{
    Q_OBJECT

public:
    Model();

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;


private:
    QMap<QString, QList<Poruka>*> mapaPoruka;

    QString _prijatelj;
    QString _korisnik;

public slots:

    void dodajPrijatelja(QString k);
    void dodajPoruku(QString p, QString k);
    void postaviPrijatelja(QString p);
    void postaviKorisnika(QString k);

    void clear();

signals:
    void primiPoruku(QString);
    void refreshedModel();
};

#endif // MODEL_H
