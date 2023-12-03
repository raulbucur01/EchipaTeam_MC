#include "StartPage.h"
#include <QtWidgets/QApplication>
#include <cpr/cpr.h>
#include <crow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    StartPage b;
    b.showFullScreen();
    return a.exec();
}
