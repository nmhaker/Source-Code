#ifndef STORAGEHANDLE_H
#define STORAGEHANDLE_H

#include <QStringList>
#include <QStringListModel>
#include <QMap>
#include <QObject>
#include <QDebug>


class StorageHandle : public QObject
{
    Q_OBJECT

public:
    StorageHandle();

    bool addPorukuPrijatelja(const QString p);
    bool addPorukuKorisnika(const QString p);

    int getBrojPrimljenihPorukaPrijatelja();
    int getBrojPrimljenihPorukaKorisnika();

    QString getPorukuPrijatelja();
    QString getPorukuKorisnika();

    void incrementPorukePrijatelja();
    void incrementPorukeKorisnika();

    int getBrojSpremnihPorukaPrijatelja();
    int getBrojSpremnihPorukaKorisnika();

    void resetujSve();

    QStringListModel* getModel();

private:

    QString _korisnik;

    QString _zadnjeKoriscenModel;

    QStringList primljenePorukePrijatelja;
    QStringList primljenePorukeKorisnika;

    int brojSpremnihPorukaPrijatelja;
    int brojSpremnihPorukaKorisnika;

public slots:

    void setKorisnickoIme(const QString k);

};

#endif // STORAGEHANDLE_H
