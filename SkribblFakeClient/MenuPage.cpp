#include "MenuPage.h"
#include "LoginPage.h"
#include "GamePage.h"
#include "ShopPage.h"
#include "ProfilePage.h"
#include <QScreen>

MenuPage::MenuPage(QWidget* parent,crow::json::rvalue player)
	: QWidget(parent)
{
	ui.setupUi(this);
	SetPlayer(player);
	m_username = QString::fromUtf8(m_player.GetName().data(),int( m_player.GetName().size()));
	setFixedSize(1000, 750);
	ui.groupBox_GameMenu->move((this->size().width() - ui.groupBox_GameMenu->size().width()) / 2, (this->size().height() - ui.groupBox_GameMenu->size().height()) / 2);
	ui.groupBox_GameMenu->show();
	connect(ui.pushButton_Profile, &QPushButton::pressed, this, &MenuPage::on_pushButton_Profile_pressed);
	connect(ui.pushButton_Shop, &QPushButton::pressed, this, &MenuPage::on_pushButton_Shop_pressed);
	connect(ui.pushButton_CreateLobby, &QPushButton::pressed, this, &MenuPage::on_pushButton_CreateLobby_pressed);
	connect(ui.pushButton_JoinLobby, &QPushButton::pressed, this, &MenuPage::on_pushButton_JoinLobby_pressed);
	connect(ui.pushButton_Logout, &QPushButton::pressed, this, &MenuPage::on_pushButton_Logout_pressed);
	ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
	connect(ui.exitButton, &QPushButton::pressed, this, &MenuPage::on_exitButton_pressed);
	ui.usernameLabel->setText(m_username);
}

void MenuPage::on_pushButton_Profile_pressed()
{
	ui.groupBox_GameMenu->hide();
	ui.exitButton->hide();
	delete ui.groupBox_GameMenu;
	delete ui.exitButton;

	QWidget* profilePage =pages.createProfilePage(this, m_player);
	profilePage->show();
}

void MenuPage::on_pushButton_Shop_pressed()
{
	ui.groupBox_GameMenu->hide();
	ui.exitButton->hide();
	delete ui.groupBox_GameMenu;
	delete ui.exitButton;

	QWidget* shopPage = pages.createShopPage(this, m_player);
	shopPage->show();
}

void MenuPage::on_pushButton_CreateLobby_pressed() {
	ui.groupBox_GameMenu->hide();
	ui.exitButton->hide();
	delete ui.groupBox_GameMenu;
	delete ui.exitButton;
	std::string username = m_username.toUtf8().constData();
	QWidget* gamePage = pages.createGamePage(this,m_player,true);
	cpr::Response res = cpr::Put(cpr::Url{ "http://localhost:18080/game/addPlayer" },
		cpr::Body{ "username=" + username });
	gamePage->show();
}

void MenuPage::on_pushButton_JoinLobby_pressed() {
	ui.groupBox_GameMenu->hide();
	ui.exitButton->hide();
	delete ui.groupBox_GameMenu;
	delete ui.exitButton;
	std::string username= m_username.toUtf8().constData();
	QWidget* gamePage = pages.createGamePage(this,m_player,false);
	cpr::Response res = cpr::Put(cpr::Url{ "http://localhost:18080/game/addPlayer" },
		cpr::Body{ "username=" + username });

	gamePage->show();
}

void MenuPage::on_pushButton_Logout_pressed() {
	ui.groupBox_GameMenu->hide();
	ui.exitButton->hide();
	delete ui.groupBox_GameMenu;
	delete ui.exitButton;
	cpr::Response response = cpr::Put(cpr::Url{ "http://localhost:18080/game/removePlayer" },
		cpr::Body{ "username=" + m_player.GetName() });
	QWidget* loginPage = pages.createLoginPage(this);
	loginPage->show();
}

void MenuPage::on_exitButton_pressed()
{
	QCoreApplication::quit();
}

Player MenuPage::GetPlayer(const Player& player)
{
	return m_player;
}

void MenuPage::SetPlayer(const crow::json::rvalue& player)
{
	m_player.SetName(player["Name"].s());
	m_player.SetPassword(player["Password"].s());
	m_player.SetScore(player["Score"].d());
	m_player.SetCoins(player["Coins"].d());
	m_player.SetCurrentIconId(player["CurrentIconId"].d());
}

MenuPage::~MenuPage()
{
	pages.destroyAllPages();
}
