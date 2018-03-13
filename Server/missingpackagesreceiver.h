#ifndef MISSINGPACKAGESRECEIVER_H
#define MISSINGPACKAGESRECEIVER_H

#include <QObject>

class QUdpSocket;
class MissingPackagesReceiver : public QObject
{
    Q_OBJECT
public:
    explicit MissingPackagesReceiver(QObject *parent = nullptr);

private slots:
    void ReadPackage();

private:
    QUdpSocket* socket = nullptr;
};

#endif // MISSINGPACKAGESRECEIVER_H
