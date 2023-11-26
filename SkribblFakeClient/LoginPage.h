#pragma once

#include <QWidget>
#include "ui_LoginPage.h"

class LoginPage : public QWidget
{
	Q_OBJECT

public:
	LoginPage(QWidget *parent = nullptr);
	~LoginPage();

private slots:
	void on_commandLinkButton_Register_pressed();
	void on_pushButton_Login_pressed();

private:
	Ui::LoginPageClass ui;
};
