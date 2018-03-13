#ifndef UTILS_H
#define UTILS_H

class QByteArray;
class Utils
{
public:
    Utils();
    static int GetPackageNumber(QByteArray* array);
};

#endif // UTILS_H
