#include "StartPage.h"
#include <QScreen>

Window::StartPage::StartPage(QWidget* parent)
	: QMainWindow(parent), loginPage(nullptr)
{
	ui.setupUi(this);
	this->setFixedSize(1000, 750);
	this->setStyleSheet("QMainWindow {background: 'lightblue';}");
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