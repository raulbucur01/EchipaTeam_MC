#include "LoginPage.h"
#include "RegisterPage.h"
#include <qmessagebox.h>

LoginPage::LoginPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.commandLinkButton_Register, &QCommandLinkButton::pressed, this, &LoginPage::on_commandLinkButton_Register_pressed);
	connect(ui.pushButton_Login, &QPushButton::pressed, this, &LoginPage::on_pushButton_Login_pressed);
}

LoginPage::~LoginPage()
{}

void LoginPage::on_pushButton_Login_pressed()
{
	QString username = ui.lineEdit_Username->text();
	QString password = ui.lineEdit_Password->text();

	// test
	QMessageBox::information(this, "Login", "Ati introdus: " + username + "," + password);
	
	// verificare daca exista in BD player-ul
	

	// dupa verificare vom intra in o pagina noua cu un main menu
}

void LoginPage::on_commandLinkButton_Register_pressed() {
	ui.groupBox->hide();
	RegisterPage* registerPage = new RegisterPage(this);
	registerPage->show();
}