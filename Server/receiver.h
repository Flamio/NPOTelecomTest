#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QUdpSocket>
#include "missingpackagesreceiver.h"

class QThread;
class Receiver : public QObject
{
    Q_OBJECT

public:
    explicit Receiver(QObject *parent = nullptr);
    ~Receiver();

public slots:
    void Receive();

private:
    QUdpSocket* udpSocket;
    int errors = 0;

    QByteArray ConvertIntToByteArray(int number);
    QThread* repairThread;
    MissingPackagesReceiver* missingPackagesReceiver;
};

#endif // RECEIVER_H
