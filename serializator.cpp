#include "serializator.h"

Serializator::Serializator()
{
    sizeOfData = 0;
}

void Serializator::addData(quint32 d)
{

}

void Serializator::addData(const char *d)
{

}

void Serializator::addData(bool d)
{

}

QString Serializator::finish()
{
    return data;
}
