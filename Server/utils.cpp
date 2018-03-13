#include "utils.h"
#include <QDataStream>

Utils::Utils()
{

}

int Utils::GetPackageNumber(QByteArray *array)
{
    auto numberBytes = array->mid(0, 4);

    QDataStream ds(numberBytes);
    int packageNumber = 0;
    ds >> packageNumber;
    return packageNumber;
}
