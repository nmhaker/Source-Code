#include "model.h"

Model::Model()
{
    this->_prijatelj = "NONE";
}

void Model::clear()
{
    QMapIterator<QString, QList<Poruka>*> i(this->mapaPoruka);
    qDebug() << "Unutar Clear() funkcije" << endl;
    while (i.hasNext()) {
        i.next();
        qDebug() << i.key() << ": " << i.value() << endl;
        i.value()->clear();
        qDebug() << "i.value()->clear()" << endl;
    }
}

void Model::dodajPrijatelja(QString k)
{
    this->mapaPoruka[k] = new QList<Poruka>;
    emit refreshedModel();
}

void Model::dodajPoruku(QString p, QString k)
{
    Poruka poruka;
    poruka.korisnik = k;
    poruka.poruka = p;

    QModelIndex index;

    if(k == this->_korisnik)
    {
        this->mapaPoruka[this->_prijatelj]->append(poruka);
        index = createIndex(this->mapaPoruka[this->_prijatelj]->count(), 0);
    }
    else
    {
        this->mapaPoruka[k]->append(poruka);
        index = createIndex(this->mapaPoruka[k]->count(), 0);
    }

    emit dataChanged(index, index);
    emit refreshedModel();
}

void Model::postaviPrijatelja(QString p)
{
    this->_prijatelj = p;
    for(int i=0;i<this->mapaPoruka[p]->count(); i++)
    {
        QModelIndex index = createIndex(i, 0);
        emit dataChanged(index, index);
    }
    emit primiPoruku(p);
}

void Model::postaviKorisnika(QString k)
{
    this->_korisnik = k;
}

int Model::rowCount(const QModelIndex &parent) const
{
    if(this->_prijatelj == "NONE")
    {
        //qDebug() << "Nije postavljen _prijatelj, greska u rowCount()" << endl;
        return 0;
    }
    else
        return this->mapaPoruka[this->_prijatelj]->count();
}

int Model::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
        case Qt::DisplayRole:
            return this->mapaPoruka[this->_prijatelj]->value(index.row()).poruka;
//        case Qt::BackgroundRole:
//            if(this->mapaPoruka[this->_prijatelj]->value(index.row()).korisnik == this->_korisnik)
//                return QBrush(QColor(255,70,70,255));
//            else
//                return QBrush(QColor(100,100,255,255));
        case Qt::TextColorRole:
            if(this->mapaPoruka[this->_prijatelj]->value(index.row()).korisnik == this->_korisnik)
                return QBrush(QColor(255,10,10));
            else
                return QBrush(QColor(100,100,255));
        case Qt::TextAlignmentRole:
            if(this->mapaPoruka[this->_prijatelj]->value(index.row()).korisnik == this->_korisnik)
                return Qt::AlignLeft;
            else
                return Qt::AlignRight;
        break;
    }
    return QVariant();
}
