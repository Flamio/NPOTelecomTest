#include "missingpackagesreceiver.h"
#include "utils.h"

#include<QUdpSocket>
#include<iostream>

MissingPackagesReceiver::MissingPackagesReceiver(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 5002);
    connect(socket, &QUdpSocket::readyRead, this, &MissingPackagesReceiver::ReadPackage);
}

void MissingPackagesReceiver::ReadPackage()
{
    while (socket->hasPendingDatagrams())
    {
        auto byteArray = new QByteArray();
        byteArray->resize(int(socket->pendingDatagramSize()));
        socket->readDatagram(byteArray->data(), byteArray->size());

        auto packageNumber = Utils::GetPackageNumber(byteArray);
        std::cout << "repair package received " << packageNumber << std::endl<<std::endl;

        delete byteArray;
        byteArray = nullptr;
    }
}
