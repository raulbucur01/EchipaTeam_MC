#include "StartPage.h"
#include <QScreen>

Window::StartPage::StartPage(QWidget* parent)
	: QMainWindow(parent), loginPage(nullptr)
{
	QSize screenSize = size();
	ui.setupUi(this);
	this->setStyleSheet("QMainWindow {background: 'lightblue';}");
	QScreen* desktop = QApplication::primaryScreen();
	this->resize(desktop->size());
	QPixmap bkgnd("/cutepuppy.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
	ui.pushButton_START->setStyleSheet(QString("#%1 { background-color: lightgreen; }").arg(ui.pushButton_START->objectName()));
	ui.pushButton_START->move((this->size().width() - ui.pushButton_START->size().width()) / 2, (this->size().height() - ui.pushButton_START->size().height()) / 2);
	connect(ui.pushButton_START, &QPushButton::pressed, this, &StartPage::on_pushButton_Start_pressed);
	ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
	connect(ui.exitButton, &QPushButton::pressed, this, &StartPage::on_exitButton_pressed);

}

Window::StartPage::~StartPage()
{
	pages.destroyAllPages();
}

void Window::StartPage::on_exitButton_pressed()
{
	QCoreApplication::quit();
}

void Window::StartPage::on_pushButton_Start_pressed() {
	ui.pushButton_START->hide();
	ui.exitButton->hide();
	delete ui.pushButton_START;
	delete ui.exitButton;
	QWidget* loginpage = pages.createLoginPage(this);
	setCentralWidget(loginpage);
}