#include "ProfilePage.h"
#include "MenuPage.h"
#include <QScreen>

ProfilePage::ProfilePage(QWidget *parent, Player player)
	: QWidget(parent), m_player(player)
{
	ui.setupUi(this);
	QScreen* desktop = QApplication::primaryScreen();
	this->resize(desktop->size());
	ui.groupBox_Profile->move((this->size().width() - ui.groupBox_Profile->size().width()) / 2, (this->size().height() - ui.groupBox_Profile->size().height()) / 2);
	ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
	connect(ui.exitButton, &QPushButton::pressed, this, &ProfilePage::on_exitButton_pressed);
	connect(ui.pushButton_Back, &QPushButton::pressed, this, &ProfilePage::on_pushButton_Back_pressed);
	
	std::string str = m_player.GetName();
	QString qs = QString::fromLocal8Bit(str.c_str());
	ui.label_Username->setText(qs);
	DisplayScore();
	DisplayCoins();
}

ProfilePage::~ProfilePage()
{
	cpr::Response response = cpr::Put(cpr::Url{ "http://localhost:18080/game/removePlayer" },
		cpr::Body{ "username=" + m_player.GetName() });
}

void ProfilePage::on_pushButton_Back_pressed()
{
	ui.groupBox_Profile->hide();
	ui.exitButton->hide();
	delete ui.groupBox_Profile;
	delete ui.exitButton;

	// Cum facem intoarcerea din profil inapoi la meniu?
}

void ProfilePage::DisplayScore()
{
	std::string username = m_player.GetName();
	std::string url = "http://localhost:18080/getScore?username=" + username;
	cpr::Response response = cpr::Get(cpr::Url(url), cpr::Body{ "username=" + username});

	if (response.status_code == 200) {
		auto json = crow::json::load(response.text);
		if (json) {
			int score = json["Score"].i();
			ui.label_Score->setText("Score: " + QString::number(score));
		}
	}
	else {

		std::cerr << "Failed to get player's score from the server." << std::endl;
	}
}

void ProfilePage::DisplayCoins()
{
	std::string username = m_player.GetName();
	std::string url = "http://localhost:18080/getCoins?username=";
	cpr::Response response = cpr::Get(cpr::Url(url), cpr::Body{ "username=" + username });

	if (response.status_code == 200) {
		auto json = crow::json::load(response.text);
		if (json) {
			int coins = json["Coins"].i();
			ui.label_Coins->setText("Coins: " + QString::number(coins));
		}
	}
	else {

		std::cerr << "Failed to get player's coins from the server." << std::endl;
	}
}


void ProfilePage::on_exitButton_pressed()
{
	QCoreApplication::quit();
}