#include <QByteArray>
#include <QDataStream>
#include "packagegenerator.h"


PackageGenerator::PackageGenerator()
{

}

QByteArray* PackageGenerator::Generate(QByteArray* customPackageId)
{
    QByteArray* byteArray = new QByteArray();
    byteArray->fill('a', 10240);
    QByteArray bytePackageId;
    if (customPackageId == nullptr)
    {
        packageId ++;
        bytePackageId = ConvertIntToByteArray(packageId);
    }
    else
    {
        packageId = ConvertByteArrayToInt(*customPackageId);
        bytePackageId = *customPackageId;
    }
    byteArray->prepend(bytePackageId);

    return byteArray;
}

int PackageGenerator::GetCurrentPackageId()
{
    return packageId;
}

int PackageGenerator::ConvertByteArrayToInt(QByteArray &array)
{
    QDataStream ds(array);
    int number = 0;
    ds >> number;
    return number;
}

QByteArray PackageGenerator::ConvertIntToByteArray(int number)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);

    stream << number;
    return byteArray;
}
