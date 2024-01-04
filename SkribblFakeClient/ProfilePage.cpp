#include "ProfilePage.h"
#include "MenuPage.h"
#include <QScreen>

ProfilePage::ProfilePage(QWidget *parent, QString username)
	: QWidget(parent), m_username(username)
{
	ui.setupUi(this);
	QScreen* desktop = QApplication::primaryScreen();
	this->resize(desktop->size());
	ui.groupBox_Profile->move((this->size().width() - ui.groupBox_Profile->size().width()) / 2, (this->size().height() - ui.groupBox_Profile->size().height()) / 2);
	ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
	connect(ui.exitButton, &QPushButton::pressed, this, &ProfilePage::on_exitButton_pressed);
	connect(ui.pushButton_Back, &QPushButton::pressed, this, &ProfilePage::on_pushButton_Back_pressed);
	ui.label_Username->setText(m_username);
	//DisplayScore();
	//DisplayCoins();
}
void ProfilePage::DisplayScore()
{
	std::string username = m_username.toStdString();
	std::string url = "http://localhost:18080/getScoreAndCoins?username=" + username;
	cpr::Response response = cpr::Get(cpr::Url(url));

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
	std::string username = m_username.toStdString();
	std::string url = "http://localhost:18080/getScoreAndCoins?username=" + username;
	cpr::Response response = cpr::Get(cpr::Url(url));

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
ProfilePage::~ProfilePage()
{}

void ProfilePage::on_pushButton_Back_pressed()
{
	ui.groupBox_Profile->hide();
	ui.exitButton->hide();
	delete ui.groupBox_Profile;
	delete ui.exitButton;

	MenuPage* menuPage = new MenuPage(this);
	menuPage->show();
}

//void ProfilePage::DisplayScore()
//{
//	QString url = "http://localhost:18080/getScore"; 
//	QNetworkRequest request(url);
//	QNetworkReply* reply = m_networkManager.get(request);
//
//	connect(reply, &QNetworkReply::finished, [=]() {
//		if (reply->error() == QNetworkReply::NoError) {
//			QString score = reply->readAll();
//			ui.label_ScoreInfo->setText(score);
//		}
//		else {
//			qDebug() << "Error fetching score:" << reply->errorString();
//		}
//
//	reply->deleteLater();
//		});
//}

//void ProfilePage::DisplayCoins()
//{
//
//	QString url = "http://localhost:18080/getCoins";  
//	QNetworkRequest request(url);
//	QNetworkReply* reply = m_networkManager.get(request);
//
//	connect(reply, &QNetworkReply::finished, [=]() {
//		if (reply->error() == QNetworkReply::NoError) {
//			QString coins = reply->readAll();
//			ui.label_CoinsInfo->setText(coins);
//		}
//		else {
//			qDebug() << "Error fetching coins:" << reply->errorString();
//		}
//
//	reply->deleteLater();
//		});
//	
//}


void ProfilePage::on_exitButton_pressed()
{
	QCoreApplication::quit();
}