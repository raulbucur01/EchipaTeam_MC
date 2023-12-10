#include "StartPage.h"
#include <QtWidgets/QApplication>
#include <cpr/cpr.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Window::StartPage b;
    b.showFullScreen();
    return a.exec();
}
