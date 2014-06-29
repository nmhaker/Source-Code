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

    QStringListModel* getModelPrijatelja(const QString p);

private:

    QStringList primljenePorukePrijatelja;
    QStringList primljenePorukeKorisnika;

    int brojSpremnihPorukaPrijatelja;
    int brojSpremnihPorukaKorisnika;

    QMap<QString, QStringList*> mapaListaZaModele;
    QMap<QString, QStringListModel*> mapaModela;

public slots:
    void kreirajModel(const QString p);
    void addMessageInModel(const QString p, const QString m);

signals:
    void getMessageForModel(const QString p);
};

#endif // STORAGEHANDLE_H
