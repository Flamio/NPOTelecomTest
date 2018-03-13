#ifndef PACKAGEGENERATOR_H
#define PACKAGEGENERATOR_H

class QByteArray;
class PackageGenerator
{
public:
    explicit PackageGenerator();
    QByteArray* Generate(QByteArray* packageId = nullptr);

    int GetCurrentPackageId();
    int GetPackageId(QByteArray* array);

private:
    int packageId = 0;

    int ConvertByteArrayToInt(QByteArray& array);
    QByteArray ConvertIntToByteArray(int number);
};

#endif // PACKAGEGENERATOR_H
