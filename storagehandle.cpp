#include "storagehandle.h"

StorageHandle::StorageHandle()
{
    this->brojSpremnihPorukaPrijatelja = 0;
    this->brojSpremnihPorukaKorisnika = 0;
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

QStringListModel* StorageHandle::getModelPrijatelja(const QString p)
{
    return this->mapaModela.value(p);
}

void StorageHandle::kreirajModel(const QString p)
{
    this->mapaModela[p] = new QStringListModel(this);
    this->mapaListaZaModele[p] = new QStringList();
    emit getMessageForModel(p);

    qDebug() << "Kreiran model za prijatelja " << p << endl;
}

void StorageHandle::addMessageInModel(const QString p, const QString m)
{
    this->mapaListaZaModele[p]->append(m);
    this->mapaModela[p]->setStringList(*(this->mapaListaZaModele[p]));
}
