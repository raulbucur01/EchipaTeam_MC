#include "StartPage.h"

StartPage::StartPage(QWidget* parent)
	: QMainWindow(parent), loginPage(nullptr)
{
	ui.setupUi(this);
	connect(ui.pushButton_START, &QPushButton::pressed, this, &StartPage::on_pushButton_Start_pressed);
}

StartPage::~StartPage()
{
}

void StartPage::on_pushButton_Start_pressed() {
	ui.pushButton_START->hide();
    LoginPage* loginPage = new LoginPage(this); // Assuming MainWindow is the parent
    loginPage->show();
}