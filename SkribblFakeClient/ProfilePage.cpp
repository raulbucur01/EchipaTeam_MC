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
	DisplayScore();
	/*DisplayCoins();*/
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



void ProfilePage::on_exitButton_pressed()
{
	QCoreApplication::quit();
}