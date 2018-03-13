#include <iostream>
#include <QDataStream>
#include "receiver.h"

Receiver::Receiver(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, 5000);
    udpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 256000);

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &Receiver::Receive);
}

Receiver::~Receiver()
{
    delete udpSocket;
    udpSocket = nullptr;
}

void Receiver::Receive()
{
    QByteArray* byteArray = nullptr;
    while (udpSocket->hasPendingDatagrams())
    {
        byteArray = new QByteArray();
        byteArray->resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(byteArray->data(), byteArray->size());

        auto numberBytes = byteArray->mid(0, 4);

        QDataStream ds(numberBytes);
        int packageNumber = 0;
        ds >> packageNumber;

        std::cout<<"received package " << packageNumber << std::endl;

        delete byteArray;
        byteArray = nullptr;
    }
}
