/*
Author: Aashish Parmar (parmaraashish3@gmail.com)

Raspberry Pi application to control switches based on client side communication for home automation project.
*/

#include <QCoreApplication>
#include "recx.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    recx receiver;
    return a.exec();
}
