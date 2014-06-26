#ifndef NETWORKHANDLE_H
#define NETWORKHANDLE_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

class NetworkHandle
{
public:
    NetworkHandle();

private:

    QNetworkAccessManager   *networkAccessManager;
    QNetworkRequest         *networkRequest;


};

#endif // NETWORKHANDLE_H
