#include <iostream>
#include <QDataStream>
#include <QTime>
#include "broadcaster.h"


Broadcaster::Broadcaster(QObject* parent)
    :QObject(parent)
{
    messageId = 0;
    timer = new QTimer(this);
    udpSocket = new QUdpSocket(this);

    udpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 256000);

    QObject::connect(timer, &QTimer::timeout, this, &Broadcaster::Broadcast);

    timer->start(1);

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
}

void Broadcaster::Broadcast()
{
    QByteArray* byteArray = new QByteArray();
    byteArray->fill('a', 10240);
    messageId ++;
    auto byteMessageId = ConvertIntToByteArray(messageId);
    byteArray->prepend(byteMessageId);

    if (qrand() % 1000 != 6)
    {
        udpSocket->writeDatagram(*byteArray, QHostAddress::Broadcast, 5000);
        std::cout << "package sended " << messageId << std::endl;
    }

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
