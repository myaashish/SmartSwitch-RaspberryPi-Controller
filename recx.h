#ifndef RECX_H
#define RECX_H

#include <QString>
#include <QtNetwork>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkAddressEntry>
#include <QUdpSocket>
#include <QObject>
#include <QtCore>
#include <QObject>

class recx : public QObject
{
    Q_OBJECT

public:
    recx(QObject *parent = 0);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    char stron[50];
    char stroff[50];
    QUdpSocket *udpSocketX, *feedsend, *feedrec;
    QByteArray datagram, datagramX, requestx;
    QString ipaddr, num;
    int val, swtch[26];
    char valx[26][3];
};

#endif // RECX_H
