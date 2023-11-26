#include "RegisterPage.h"
#include <qmessagebox.h>

RegisterPage::RegisterPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

RegisterPage::~RegisterPage()
{}

void RegisterPage::on_pushButton_CreateAccount_pressed() {
	QString username = ui.lineEdit_Username->text();
	QString password = ui.lineEdit_Password->text();
	QString password2 = ui.lineEdit_ConfirmPassword->text();

	if (password != password2)
		QMessageBox::warning(this, "Login", "Ati introdus: " + username + "," + password);

	// test
	QMessageBox::information(this, "Login", "Ati introdus: " + username + "," + password);

	// adaugare user daca nu exista deja in BD cu ceva validari

	// dupa adaugare se trece la main menu
}