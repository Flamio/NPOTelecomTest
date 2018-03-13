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

QByteArray Receiver::ConvertIntToByteArray(int number)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);

    stream << number;
    return byteArray;
}

void Receiver::Receive()
{
    static int currentPackageNumber = 0;

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

        if (packageNumber != currentPackageNumber+1 && currentPackageNumber !=0)
        {
            std::cout<<"lost package " << currentPackageNumber+1 << std::endl;
            errors++;
            std::cout<<"errors: " << errors<< std::endl;

            udpSocket->writeDatagram(ConvertIntToByteArray(packageNumber), QHostAddress::Broadcast, 5000);
        }

        currentPackageNumber = packageNumber;

        //std::cout<<"received package " << packageNumber << std::endl;

        delete byteArray;
        byteArray = nullptr;
    }
}
