#include "PRT.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PRT w;
    w.show();
    return a.exec();
}
