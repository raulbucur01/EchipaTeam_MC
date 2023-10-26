#include "SkribblFake.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SkribblFake w;
    w.show();
    return a.exec();
}
