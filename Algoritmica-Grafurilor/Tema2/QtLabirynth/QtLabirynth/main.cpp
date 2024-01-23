#include "QtLabirynth.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtLabirynth w;
    w.show();
    return a.exec();
}
