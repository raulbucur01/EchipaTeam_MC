#include "SkribblFakeClient.h"
#include "RegisterPage.h"
#include <qmessagebox.h>

SkribblFakeClient::SkribblFakeClient(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_Login, &QPushButton::pressed, this, &SkribblFakeClient::on_pushButton_Login_clicked);
	connect(ui.commandLinkButton, &QCommandLinkButton::pressed, this, &SkribblFakeClient::on_commandLinkButton_pressed);
}

SkribblFakeClient::~SkribblFakeClient()
{}

void SkribblFakeClient::on_commandLinkButton_pressed()
{
	RegisterPage w;
	w.showFullScreen();
}

void SkribblFakeClient::on_pushButton_Login_clicked()
{
	QString username = ui.lineEdit_username->text();
	QString password = ui.lineEdit_password->text();

	// aici testare existenta cont cu serverul

	if (username == "test" && password == "test")
		QMessageBox::information(this, "Login", "Username and password tested and correct!");
	else
		QMessageBox::warning(this, "Login", "Username and password tested and NOT correct");
}
