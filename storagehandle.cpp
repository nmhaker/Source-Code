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

QStringListModel* StorageHandle::getModelPrijatelja(const QString p)
{
    this->_zadnjeKoriscenModel = p;

    emit getMessageForModel(p);

    qDebug() << "Uzet model za prijatelja " << p << " i emitovan signal za primanje poruka" << endl;

    return this->mapaModela.value(p);
}

void StorageHandle::kreirajModel(const QString p)
{
    this->mapaModela[p] = new QStringListModel(this);
    this->mapaListaZaModele[p] = new QStringList();

    qDebug() << "Kreiran model za prijatelja " << p << endl;
}

void StorageHandle::addMessageInModel(const QString m, const QString p)
{
    this->mapaListaZaModele[this->_zadnjeKoriscenModel]->append(m);
    this->mapaModela[this->_zadnjeKoriscenModel]->setStringList(*(this->mapaListaZaModele[this->_zadnjeKoriscenModel]));
}

void StorageHandle::setKorisnickoIme(const QString k)
{
    this->_korisnik = k;
}
