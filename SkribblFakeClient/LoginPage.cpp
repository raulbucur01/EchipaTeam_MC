#include "LoginPage.h"
#include "RegisterPage.h"
#include <qmessagebox.h>
#include <QScreen>
#include "MenuPage.h"
#include <cpr/cpr.h>

LoginPage::LoginPage(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QScreen* desktop = QApplication::primaryScreen();
	this->resize(desktop->size());
	ui.groupBox_Login->move((this->size().width() - ui.groupBox_Login->size().width()) / 2, (this->size().height() - ui.groupBox_Login->size().height()) / 2);
	connect(ui.commandLinkButton_Register, &QCommandLinkButton::pressed, this, &LoginPage::on_commandLinkButton_Register_pressed);
	connect(ui.pushButton_Login, &QPushButton::clicked, this, &LoginPage::on_pushButton_Login_pressed);
	ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
	connect(ui.exitButton, &QPushButton::pressed, this, &LoginPage::on_exitButton_pressed);
}

LoginPage::~LoginPage()
{}

void LoginPage::on_pushButton_Login_pressed()
{
	username = ui.lineEdit_Username->text();
	password = ui.lineEdit_Password->text();
	std::string nume = username.toUtf8().constData();
	std::string parola = password.toUtf8().constData();
	auto res = cpr::Post(cpr::Url{ "http://localhost:18080/login" },
		cpr::Body{ "username=" + nume + "&password=" + parola });

	if (res.error.code != cpr::ErrorCode::OK) {
		//afisare text
		return;
	}
	if (res.status_code == 200)
	{
		ui.groupBox_Login->hide();
		delete ui.groupBox_Login;
		MenuPage* menuPage = new MenuPage(this, username);
		menuPage->show();
	}
	else if (res.status_code == 401) {
		QMessageBox::warning(this, "Login", "Password incorrect! Please try again!");
	}
	else if (res.status_code == 404) {
		QMessageBox::warning(this, "Login", "Username not found! Please try again!");
	}
	else {
		QMessageBox::warning(this, "Login", "You didn't enter anything in one or all slots!");
	}
}

void LoginPage::on_exitButton_pressed()
{
	exit(0);
}

void LoginPage::on_commandLinkButton_Register_pressed() {
	ui.groupBox_Login->hide();
	ui.exitButton->hide();
	delete ui.groupBox_Login;
	delete ui.exitButton;
	RegisterPage* registerPage = new RegisterPage(this);
	registerPage->show();
}