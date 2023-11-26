#include "LoginPage1.h"
#include "RegisterPage.h"
#include <qmessagebox.h>

LoginPage::LoginPage(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_Login, &QPushButton::pressed, this, &LoginPage::on_pushButton_Login_clicked);
	connect(ui.commandLinkButton, &QCommandLinkButton::pressed, this, &LoginPage::on_commandLinkButton_pressed);
}

LoginPage::~LoginPage()
{}

void LoginPage::on_commandLinkButton_pressed()
{
	RegisterPage w;
	w.showFullScreen();
}

void LoginPage::on_pushButton_Login_clicked()
{
	QString username = ui.lineEdit_username->text();
	QString password = ui.lineEdit_password->text();

	// aici testare existenta cont cu serverul

	if (username == "test" && password == "test")
		QMessageBox::information(this, "Login", "Username and password tested and correct!");
	else
		QMessageBox::warning(this, "Login", "Username and password tested and NOT correct");
}
