/*
Author: Aashish Parmar (parmaraashish3@gmail.com)

Raspberry Pi application to control switches based on client side communication for home automation project.
*/

#include "recx.h"
#include <QHttp>
#include <QFile>
#include <QUrl>
#include <QTcpSocket>
#include <QHostAddress>

/*
Initializes all switches to OFF state and registers the micro-controller to server for internet based communication
*/
recx::recx(QObject *parent) :
    QObject(parent)
{
    system("gpio mode 2 out");
    system("gpio mode 3 out");
    system("gpio mode 4 out");
    system("gpio mode 14 out");
    system("gpio mode 15 out");
    system("gpio mode 17 out");
    system("gpio mode 18 out");
    system("gpio mode 27 out");
    system("gpio mode 22 out");
    system("gpio mode 23 out");
    system("gpio mode 10 out");
    system("gpio mode 9 out");
    system("gpio mode 11 out");
    system("gpio mode 5 out");
    system("gpio mode 6 out");
    system("gpio mode 13 out");
    system("gpio mode 19 out");
    system("gpio mode 26 out");
    system("gpio mode 24 out");
    system("gpio mode 25 out");
    system("gpio mode 8 out");
    system("gpio mode 7 out");
    system("gpio mode 12 out");
    system("gpio mode 16 out");
    system("gpio mode 20 out");
    system("gpio mode 21 out");

    swtch[0] = 0;
    swtch[1] = 0;
    swtch[2] = 0;
    swtch[3] = 0;
    swtch[4] = 0;
    swtch[5] = 0;
    swtch[6] = 0;
    swtch[7] = 0;
    swtch[8] = 0;
    swtch[9] = 0;
    swtch[10] = 0;
    swtch[11] = 0;
    swtch[12] = 0;
    swtch[13] = 0;
    swtch[14] = 0;
    swtch[15] = 0;
    swtch[16] = 0;
    swtch[17] = 0;
    swtch[18] = 0;
    swtch[19] = 0;
    swtch[20] = 0;
    swtch[21] = 0;
    swtch[22] = 0;
    swtch[23] = 0;
    swtch[24] = 0;
    swtch[25] = 0;
    
    strcpy(valx[0],"2");    
    strcpy(valx[1],"3");
    strcpy(valx[2],"4");
    strcpy(valx[3],"14");
    strcpy(valx[4],"15");
    strcpy(valx[5],"17");
    strcpy(valx[6],"18");
    strcpy(valx[7],"27");
    strcpy(valx[8],"22");
    strcpy(valx[9],"23");
    strcpy(valx[10],"10");
    strcpy(valx[11],"9");
    strcpy(valx[12],"11");
    strcpy(valx[13],"5");
    strcpy(valx[14],"6");
    strcpy(valx[15],"13");
    strcpy(valx[16],"19");
    strcpy(valx[17],"26");
    strcpy(valx[18],"24");
    strcpy(valx[19],"25");
    strcpy(valx[20],"8");
    strcpy(valx[21],"7");
    strcpy(valx[22],"12");
    strcpy(valx[23],"16");
    strcpy(valx[24],"20");
    strcpy(valx[25],"21");

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress)

    feedsend = new QUdpSocket;

    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));

    QFile file("val.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    while(!file.atEnd())
    {
        num = file.readLine();
    }

    char a[50];
    strcpy(a,"wget website/dbxyz.php?pinum=");
    strcat(a,num.toLatin1().data());
    system(a);
    strcpy(a,"rm dbxyz.php?pinum=");
    strcat(a,num.toLatin1().data());
    system(a);
}

/*
Receives data from client and processes the switch accordingly.
*/
void recx::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
    }

    if(datagram != "0")
    {
        val = datagram.toInt();
        if(swtch[val-1] == 0)
        {
            swtch[val-1] = 1;
            strcpy(stron,"gpio -g write ");
            strcat(stron, valx[val-1]);
            strcat(stron, " 1");
            system(stron);
        }
        else
        {
            swtch[val-1] = 0;
            strcpy(stroff,"gpio -g write " );
            strcat(stroff,valx[val-1]);
            strcat(stroff," 0");
            system(stroff);
        }
    }
    else {
        for(int i = 0; i < 25; i++)
        {
            if(swtch[i]!=0){
                strcpy(stroff,"gpio -g write " );
                strcat(stroff,valx[val-1]);
                strcat(stroff," 0");
                system(stroff);
            }
        }
    }
}
