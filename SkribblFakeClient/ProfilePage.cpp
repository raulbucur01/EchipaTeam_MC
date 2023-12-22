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
	// se cauta de la server pt username-ul curent scorul
	// (!!! E evident ca playerul exista daca am ajuns aici. Trebuie doar cautat si returnat scorul !!!)
	QString score = "0";
	ui.label_ScoreInfo->setText(score);
}

void ProfilePage::DisplayCoins()
{
	// se cauta de la server pt username-ul curent cati bani are
	// (!!! E evident ca playerul exista daca am ajuns aici. Trebuie doar cautat si returnat cati bani are !!!)
	QString coins = "0";
	ui.label_CoinsInfo->setText(coins);
}

void ProfilePage::on_exitButton_pressed()
{
	exit(0);
}