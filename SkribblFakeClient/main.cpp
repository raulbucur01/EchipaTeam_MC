#include "StartPage.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartPage b;
    b.showFullScreen();
    return a.exec();
}
