#include "StartPage.h"
#include <QScreen>

Window::StartPage::StartPage(QWidget* parent)
	: QMainWindow(parent), loginPage(nullptr)
{
	ui.setupUi(this);
	this->setFixedSize(1000, 750);
	this->setStyleSheet("QMainWindow {background: 'lightblue';}");

	// Add label for the square-shaped logo
	QLabel* logoLabel = new QLabel(this);
	ui.logoLabel->setAlignment(Qt::AlignCenter);

	int logoSize = 300; // Adjust the size of the square-shaped logo
	int logoX = (this->width() - logoSize) / 2; // Center horizontally
	int logoY = (this->height() - logoSize - 100) / 2; // Center vertically above the start button
	ui.logoLabel->setGeometry(logoX, logoY, logoSize, logoSize);

	// Load and set the logo image
	QPixmap logoPixmap("./Icons/Logo.jpeg"); // Adjust the path to your logo image
	ui.logoLabel->setPixmap(logoPixmap.scaled(ui.logoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

	ui.pushButton_START->setStyleSheet(QString("#%1 { background-color: lightgreen; }").arg(ui.pushButton_START->objectName()));
	ui.pushButton_START->move((this->width() - ui.pushButton_START->width()) / 2, logoY + logoSize + 70); // Adjust the vertical position

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
	ui.logoLabel->hide();
	delete ui.logoLabel;
	delete ui.pushButton_START;
	delete ui.exitButton;
	QWidget* loginpage = pages.createLoginPage(this);
	setCentralWidget(loginpage);
}