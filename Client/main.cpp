#include <QCoreApplication>
#include "broadcaster.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Broadcaster broadcaster(&a);
    return a.exec();
}
