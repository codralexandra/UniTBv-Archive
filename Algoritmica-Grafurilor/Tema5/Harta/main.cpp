#include "Harta.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Harta w;
    w.show();
    return a.exec();
}
