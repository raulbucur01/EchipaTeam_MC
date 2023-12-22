#include "ProfilePage.h"
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
	ui.label_Username->setText(m_username);
	DisplayScore();
	DisplayCoins();
}

ProfilePage::~ProfilePage()
{}

void ProfilePage::DisplayScore()
{
	QString url = "http://localhost:18080/getScore"; 
	QNetworkRequest request(url);
	QNetworkReply* reply = m_networkManager.get(request);

	connect(reply, &QNetworkReply::finished, [=]() {
		if (reply->error() == QNetworkReply::NoError) {
			QString score = reply->readAll();
			ui.label_ScoreInfo->setText(score);
		}
		else {
			qDebug() << "Error fetching score:" << reply->errorString();
		}

	reply->deleteLater();
		});
}

void ProfilePage::DisplayCoins()
{

	QString url = "http://localhost:18080/getCoins";  
	QNetworkRequest request(url);
	QNetworkReply* reply = m_networkManager.get(request);

	connect(reply, &QNetworkReply::finished, [=]() {
		if (reply->error() == QNetworkReply::NoError) {
			QString coins = reply->readAll();
			ui.label_CoinsInfo->setText(coins);
		}
		else {
			qDebug() << "Error fetching coins:" << reply->errorString();
		}

	reply->deleteLater();
		});
	
}

void ProfilePage::on_exitButton_pressed()
{
	exit(0);
}