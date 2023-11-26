#pragma once

#include <QWidget>
#include "ui_LoginPage.h"

class LoginPage : public QWidget
{
	Q_OBJECT

public:
	LoginPage(QWidget *parent = nullptr);
	~LoginPage();

private:
	Ui::LoginPageClass ui;
};
