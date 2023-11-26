#include "SkribblFakeClient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SkribblFakeClient w;
    w.showFullScreen();
    return a.exec();
}
