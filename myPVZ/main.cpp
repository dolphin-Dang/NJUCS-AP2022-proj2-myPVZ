#include "beginWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    beginWindow w;
    w.show();
    return a.exec();
}
