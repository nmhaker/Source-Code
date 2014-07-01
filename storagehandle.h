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

    QMap<QString, QStringList*> mapaListaZaModele;
    QStringListModel* model;

public slots:
    void kreirajModel(const QString p);
    void addMessageInModel(const QString m, const QString p);
    void setKorisnickoIme(const QString k);

    void postaviListuZaModel(const QString p);

signals:
    void getMessageForModel(const QString p);
};

#endif // STORAGEHANDLE_H
