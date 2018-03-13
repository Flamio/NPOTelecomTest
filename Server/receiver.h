#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QUdpSocket>

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
};

#endif // RECEIVER_H
