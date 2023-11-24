#include "SkribblFakeClient.h"
#include <qmessagebox.h>

SkribblFakeClient::SkribblFakeClient(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_Login, &QPushButton::clicked, this, &SkribblFakeClient::on_pushButton_Login_clicked);
}

SkribblFakeClient::~SkribblFakeClient()
{}

void SkribblFakeClient::on_pushButton_Login_clicked()
{
	QString username = ui.lineEdit_username->text();
	QString password = ui.lineEdit_password->text();

	if (username == "test" && password == "test")
		QMessageBox::information(this, "Login", "Username and password tested and correct!");
	else
		QMessageBox::warning(this, "Login", "Username and password tested and NOT correct");
}
