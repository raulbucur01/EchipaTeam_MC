#include "RegisterPage.h"
#include <qmessagebox.h>
#include <QScreen>
#include "LoginPage.h"
#include <cpr/cpr.h>

RegisterPage::RegisterPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QScreen* desktop = QApplication::primaryScreen();
	this->resize(desktop->size());
	ui.groupBox_Register->move((this->size().width() - ui.groupBox_Register->size().width()) / 2, (this->size().height() - ui.groupBox_Register->size().height()) / 2);
	connect(ui.pushButton_CreateAccount, &QPushButton::pressed, this, &RegisterPage::on_pushButton_CreateAccount_pressed);
	ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
	connect(ui.exitButton, &QPushButton::pressed, this, &RegisterPage::on_exitButton_pressed);
}

RegisterPage::~RegisterPage()
{}

void RegisterPage::on_exitButton_pressed()
{
	exit(0);
}

void RegisterPage::on_pushButton_CreateAccount_pressed() {
	QString username = ui.lineEdit_Username->text();
	QString password = ui.lineEdit_Password->text();
	QString password2 = ui.lineEdit_ConfirmPassword->text();

	//if (password != password2)
	//	QMessageBox::warning(this, "Login", "Ati introdus: " + username + "," + password);

	//// test
	//QMessageBox::information(this, "Login", "Ati introdus: " + username + "," + password);

	// adaugare user daca nu exista deja in BD cu ceva validari

	// dupa adaugare se trece la log in iar

	auto res = cpr::Put(cpr::Url{"http://localhost:18080/signup"});
	if (res.error.code != cpr::ErrorCode::OK)
	{
		// error
		return;
	}
	if (res.status_code == 201)
	{
		ui.groupBox_Register->hide();
		ui.exitButton->hide();
		delete ui.groupBox_Register;
		delete ui.exitButton;
		LoginPage* loginPage = new LoginPage(this);
		loginPage->show();
	}
	/*else
	{
		return error;
	}*/
	}