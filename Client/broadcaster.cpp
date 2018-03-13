#include <iostream>
#include <QDataStream>
#include <QTime>
#include "broadcaster.h"
#include "streamrepair.h"
#include "packagegenerator.h"


Broadcaster::Broadcaster(QObject* parent)
    :QObject(parent)
{
    timer = new QTimer(this);
    udpSocket = new QUdpSocket(this);

    repairThread = new QThread(this);
    auto streamrepair = new StreamRepair();
    repairThread->start();
    streamrepair->moveToThread(repairThread);

    udpSocket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 256000);

    QObject::connect(timer, &QTimer::timeout, this, &Broadcaster::Broadcast);

    timer->start(1);

    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    packageGenerator = new PackageGenerator();
}

void Broadcaster::Broadcast()
{
    auto byteArray = packageGenerator->Generate();

    if (qrand() % 1000 != 6)
    {
        udpSocket->writeDatagram(*byteArray, QHostAddress::Broadcast, 5000);
        std::cout << "package sended " << packageGenerator->GetCurrentPackageId() << std::endl;
    }

    delete byteArray;
    byteArray = nullptr;
}

Broadcaster::~Broadcaster()
{
    timer->stop();
    delete timer;
    delete udpSocket;
    timer = nullptr;
    udpSocket = nullptr;
}
