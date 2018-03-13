#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <QTimer>
#include <QUdpSocket>

class QByteArray;

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
    int messageId;

    QByteArray ConvertIntToByteArray(int number);
};
#endif // BROADCASTER_H
