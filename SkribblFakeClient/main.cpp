#include "StartPage.h"
#include <QtWidgets/QApplication>
#include <cpr/cpr.h>


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	a.setWindowIcon(QIcon("./Icons/Logo.jpeg"));
	Window::StartPage b;
	b.show();
	return a.exec();
}
