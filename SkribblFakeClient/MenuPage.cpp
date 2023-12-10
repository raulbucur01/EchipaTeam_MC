#include "MenuPage.h"
#include "LoginPage.h"
#include "GamePage.h"
#include <QScreen>

MenuPage::MenuPage(QWidget* parent,QString username)
	: QWidget(parent),m_username(username)
{
	ui.setupUi(this);
	QScreen* desktop = QApplication::primaryScreen();
	this->resize(desktop->size());
	ui.groupBox_GameMenu->move((this->size().width() - ui.groupBox_GameMenu->size().width()) / 2, (this->size().height() - ui.groupBox_GameMenu->size().height()) / 2);
	connect(ui.pushButton_CreateLobby, &QPushButton::pressed, this, &MenuPage::on_pushButton_CreateLobby_pressed);
	connect(ui.pushButton_JoinLobby, &QPushButton::pressed, this, &MenuPage::on_pushButton_JoinLobby_pressed);
	connect(ui.pushButton_Logout, &QPushButton::pressed, this, &MenuPage::on_pushButton_Logout_pressed);
	ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
	connect(ui.exitButton, &QPushButton::pressed, this, &MenuPage::on_exitButton_pressed);
	ui.usernameLabel->setText(m_username);
}

void MenuPage::on_pushButton_CreateLobby_pressed() {
	ui.groupBox_GameMenu->hide();
	ui.exitButton->hide();
	delete ui.groupBox_GameMenu;
	delete ui.exitButton;
	GamePage* gamePage = new GamePage(this);
	gamePage->show();
}

void MenuPage::on_pushButton_JoinLobby_pressed() {
	ui.groupBox_GameMenu->hide();
	ui.exitButton->hide();
	delete ui.groupBox_GameMenu;
	delete ui.exitButton;
	GamePage* gamePage = new GamePage(this);
	gamePage->show();
}

void MenuPage::on_pushButton_Logout_pressed() {
	ui.groupBox_GameMenu->hide();
	ui.exitButton->hide();
	delete ui.groupBox_GameMenu;
	delete ui.exitButton;
	LoginPage* loginPage = new LoginPage(this);
	loginPage->show();
}

void MenuPage::on_exitButton_pressed()
{
	exit(0);
}

MenuPage::~MenuPage()
{}
