#include "storagehandle.h"

StorageHandle::StorageHandle()
{
    this->brojSpremnihPorukaPrijatelja = 0;
    this->brojSpremnihPorukaKorisnika = 0;

    this->_korisnik = "NONE";

}

bool StorageHandle::addPorukuPrijatelja(const QString p)
{
    if(!this->primljenePorukePrijatelja.contains(p))
    {
        this->primljenePorukePrijatelja.append(p);
        return true;
    }else
        return false;
}

bool StorageHandle::addPorukuKorisnika(const QString p)
{
    if(!this->primljenePorukeKorisnika.contains(p))
    {
        this->primljenePorukeKorisnika.append(p);
        return true;
    }else
        return false;
}

int StorageHandle::getBrojPrimljenihPorukaPrijatelja()
{
    return this->primljenePorukePrijatelja.count();
}

int StorageHandle::getBrojPrimljenihPorukaKorisnika()
{
    return this->primljenePorukeKorisnika.count();
}

QString StorageHandle::getPorukuPrijatelja()
{
    return this->primljenePorukePrijatelja.value(this->getBrojSpremnihPorukaPrijatelja());
}

QString StorageHandle::getPorukuKorisnika()
{
    return this->primljenePorukeKorisnika.value(this->getBrojSpremnihPorukaKorisnika());
}

void StorageHandle::incrementPorukePrijatelja()
{
    this->brojSpremnihPorukaPrijatelja++;
}

void StorageHandle::incrementPorukeKorisnika()
{
    this->brojSpremnihPorukaKorisnika++;
}

int StorageHandle::getBrojSpremnihPorukaPrijatelja()
{
    return this->brojSpremnihPorukaPrijatelja;
}

int StorageHandle::getBrojSpremnihPorukaKorisnika()
{
    return this->brojSpremnihPorukaKorisnika;
}

void StorageHandle::resetujSve()
{
    this->brojSpremnihPorukaKorisnika = 0;
    this->brojSpremnihPorukaPrijatelja = 0;
    this->primljenePorukeKorisnika.clear();
    this->primljenePorukePrijatelja.clear();
}



void StorageHandle::setKorisnickoIme(const QString k)
{
    this->_korisnik = k;
}
