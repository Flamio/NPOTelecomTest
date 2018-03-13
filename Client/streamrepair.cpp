#include <QDataStream>
#include <iostream>
#include "packagegenerator.h"
#include "streamrepair.h"

StreamRepair::StreamRepair(QObject *parent)
    : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 5001);
    connect(socket, &QUdpSocket::readyRead, this, &StreamRepair::ReadPackage);
    packageGenerator = new PackageGenerator();
}

void StreamRepair::ReadPackage()
{
    while (socket->hasPendingDatagrams())
    {
        auto byteArray = new QByteArray();
        byteArray->resize(int(socket->pendingDatagramSize()));
        socket->readDatagram(byteArray->data(), byteArray->size());

        auto repairedPackage = packageGenerator->Generate(byteArray);

        socket->writeDatagram(*repairedPackage, QHostAddress::Broadcast, 5001);
        std::cout << " repair package sended " << packageGenerator->GetCurrentPackageId() << std::endl;

        delete byteArray;
        byteArray = nullptr;
    }
}
