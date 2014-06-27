#ifndef STORAGEHANDLE_H
#define STORAGEHANDLE_H

#include <QStringList>

class StorageHandle
{
public:
    StorageHandle();

    QStringList primljenePorukePrijatelja;
    QStringList primljenePorukeKorisnika;

    int brojSpremnihPorukaPrijatelja;
    int brojSpremnihPorukaKorisnika;
};

#endif // STORAGEHANDLE_H
