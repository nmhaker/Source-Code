#ifndef SERIALIZATOR_H
#define SERIALIZATOR_H

#include <QByteArray>
#include <QString>

class Serializator
{
public:
    Serializator();

    void addData(quint32 d);
    void addData(const char* d);
    void addData(bool d);

    QString finish();

private:
    quint32 sizeOfData;
    char* data;

};

#endif // SERIALIZATOR_H
