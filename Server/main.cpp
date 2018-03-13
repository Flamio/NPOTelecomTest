#include <QCoreApplication>
#include "receiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Receiver receiver(&a);
    return a.exec();
}
