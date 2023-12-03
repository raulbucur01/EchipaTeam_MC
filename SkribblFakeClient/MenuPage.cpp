#include "MenuPage.h"
#include "LoginPage.h"
#include <QScreen>

MenuPage::MenuPage(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QScreen* desktop = QApplication::primaryScreen();
	this->resize(desktop->size());
	ui.groupBox_GameMenu->move((this->size().width() - ui.groupBox_GameMenu->size().width()) / 2, (this->size().height() - ui.groupBox_GameMenu->size().height()) / 2);
	connect(ui.pushButton_CreateLobby, &QPushButton::pressed, this, &MenuPage::on_pushButton_CreateLobby_pressed);
	connect(ui.pushButton_JoinLobby, &QPushButton::pressed, this, &MenuPage::on_pushButton_JoinLobby_pressed);
	connect(ui.pushButton_Logout, &QPushButton::pressed, this, &MenuPage::on_pushButton_Logout_pressed);
}

void MenuPage::on_pushButton_CreateLobby_pressed() {
	ui.groupBox_GameMenu->hide();
	delete ui.groupBox_GameMenu;
}

void MenuPage::on_pushButton_JoinLobby_pressed() {
	ui.groupBox_GameMenu->hide();
	delete ui.groupBox_GameMenu;
}

void MenuPage::on_pushButton_Logout_pressed() {
	ui.groupBox_GameMenu->hide();
	delete ui.groupBox_GameMenu;
	LoginPage* loginPage = new LoginPage(this);
	loginPage->show();
}

MenuPage::~MenuPage()
{}
