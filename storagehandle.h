#ifndef STORAGEHANDLE_H
#define STORAGEHANDLE_H

#include <QStringList>

class StorageHandle
{
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

private:

    QStringList primljenePorukePrijatelja;
    QStringList primljenePorukeKorisnika;

    int brojSpremnihPorukaPrijatelja;
    int brojSpremnihPorukaKorisnika;
};

#endif // STORAGEHANDLE_H
