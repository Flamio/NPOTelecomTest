#include <iostream>
#include <QDataStream>
#include "broadcaster.h"


Broadcaster::Broadcaster(QObject* parent)
    :QObject(parent)
{
    messageId = 0;
    timer = new QTimer(this);
    udpSocket = new QUdpSocket(this);

    QObject::connect(timer, &QTimer::timeout, this, &Broadcaster::Broadcast);

    timer->start(250);
}

void Broadcaster::Broadcast()
{
    QByteArray* byteArray = new QByteArray();
    byteArray->fill(123, 256000);
    messageId ++;
    auto byteMessageId = ConvertIntToByteArray(messageId);
    byteArray->prepend(byteMessageId);

    udpSocket->writeDatagram(*byteArray, QHostAddress::Broadcast, 45454);
    std::cout << "package sended " << messageId << std::endl;
    delete byteArray;
    byteArray = nullptr;
}

QByteArray Broadcaster::ConvertIntToByteArray(int number)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);

    stream << number;
    return byteArray;
}

Broadcaster::~Broadcaster()
{
    timer->stop();
    delete timer;
    delete udpSocket;
    timer = nullptr;
    udpSocket = nullptr;
}
