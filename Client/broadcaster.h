#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <QTimer>
#include <QUdpSocket>
#include <QThread>

class QByteArray;
class PackageGenerator;

class Broadcaster : public QObject
{
    Q_OBJECT

public:
    explicit Broadcaster(QObject* parent);
    ~Broadcaster();

private slots:
    void Broadcast();

private:
    QTimer* timer;
    QUdpSocket* udpSocket;
    PackageGenerator* packageGenerator;
    QThread* repairThread;
};
#endif // BROADCASTER_H
