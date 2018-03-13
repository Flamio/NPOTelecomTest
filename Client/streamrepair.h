#ifndef STREAMREPAIR_H
#define STREAMREPAIR_H

#include <QObject>
#include <QUdpSocket>

class PackageGenerator;
class StreamRepair : public QObject
{
    Q_OBJECT
public:
    explicit StreamRepair(QObject *parent = nullptr);

signals:

private slots:
    void ReadPackage();

private:
    QUdpSocket* socket = nullptr;
    PackageGenerator* packageGenerator = nullptr;

};

#endif // STREAMREPAIR_H
