#include "RegisterPage.h"
#include <qmessagebox.h>
#include <QScreen>
#include "LoginPage.h"
#include <cpr/cpr.h>
#include <QResizeEvent>

RegisterPage::RegisterPage(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(1000, 750);
	ui.groupBox_Register->move((size().width() - ui.groupBox_Register->size().width()) / 2, (size().height() - ui.groupBox_Register->size().height()) / 2);
	connect(ui.pushButton_CreateAccount, &QPushButton::toggled, this, &RegisterPage::on_pushButton_CreateAccount_pressed);
	ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
	connect(ui.exitButton, &QPushButton::pressed, this, &RegisterPage::on_exitButton_pressed);
	ui.lineEdit_Password->setEchoMode(QLineEdit::Password);
	ui.lineEdit_ConfirmPassword->setEchoMode(QLineEdit::Password);
}

RegisterPage::~RegisterPage()
{}

void RegisterPage::on_exitButton_pressed()
{
	QCoreApplication::quit();
}

void RegisterPage::on_backButton_pressed()
{
	ui.groupBox_Register->hide();
	ui.exitButton->hide();
	delete ui.exitButton;
	delete ui.groupBox_Register;

	QWidget* loginPage = pages.createLoginPage(this);
	loginPage->show();
}

void RegisterPage::on_pushButton_CreateAccount_pressed() {
	QString username = ui.lineEdit_Username->text();
	QString password = ui.lineEdit_Password->text();
	QString confirmPassword = ui.lineEdit_ConfirmPassword->text();
	std::string usernameToString = username.toUtf8().constData();
	std::string passwordToString = password.toUtf8().constData();
	std::string password1ToString = confirmPassword.toUtf8().constData();

	if (password != confirmPassword) {
		QMessageBox::warning(this, "Register", "Passwords not matching! Please try again!");
	}
	else {
		auto res = cpr::Put(cpr::Url{ "http://localhost:18080/registration" },
			cpr::Body{ "username=",usernameToString,"&password=",passwordToString,"&confirmPassword=",password1ToString });
		if (res.error.code != cpr::ErrorCode::OK)
		{
			// error
			return;
		}
		if (res.status_code == 201)
		{
			QMessageBox::information(this, "Register", QString::fromUtf8(res.text.data(), int(res.text.size())));
			ui.groupBox_Register->hide();
			ui.exitButton->hide();
			delete ui.groupBox_Register;
			delete ui.exitButton;
			LoginPage* loginPage = new LoginPage(this);
			loginPage->show();
		}
		else 
			QMessageBox::warning(this, "Register", QString::fromUtf8(res.text.data(), int(res.text.size())));
	}
}