#include <iostream>
#include <QDataStream>
#include <QThread>
#include "receiver.h"
#include "utils.h"

Receiver::Receiver(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::Any, 5000);
    repairThread = new QThread(this);
    missingPackagesReceiver = new MissingPackagesReceiver();
    repairThread->start();
    missingPackagesReceiver->moveToThread(repairThread);

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

        auto packageNumber = Utils::GetPackageNumber(byteArray);

        auto pendingPackageNumber = currentPackageNumber+1;
        if (packageNumber != pendingPackageNumber && currentPackageNumber !=0)
        {
            std::cout<<"lost package " << pendingPackageNumber << std::endl;
            errors++;
            std::cout<<"errors: " << errors<< std::endl;

            udpSocket->writeDatagram(ConvertIntToByteArray(pendingPackageNumber), QHostAddress::Broadcast, 5001);
        }

        currentPackageNumber = packageNumber;

        delete byteArray;
        byteArray = nullptr;
    }
}
