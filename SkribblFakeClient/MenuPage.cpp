#include "MenuPage.h"

MenuPage::MenuPage(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_CreateLobby, &QPushButton::pressed, this, &MenuPage::on_pushButton_CreateLobby_pressed);
	connect(ui.pushButton_JoinLobby, &QPushButton::pressed, this, &MenuPage::on_pushButton_JoinLobby_pressed);
	connect(ui.pushButton_Logout, &QPushButton::pressed, this, &MenuPage::on_pushButton_Logout_pressed);
}

void MenuPage::on_pushButton_CreateLobby_pressed() {

}

void MenuPage::on_pushButton_JoinLobby_pressed() {

}

void MenuPage::on_pushButton_Logout_pressed() {

}

MenuPage::~MenuPage()
{}
