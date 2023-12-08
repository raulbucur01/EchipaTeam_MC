#pragma once

#include <QWidget>
#include "ui_RegisterPage.h"

class RegisterPage : public QWidget
{
	Q_OBJECT

public:
	RegisterPage(QWidget *parent = nullptr);
	~RegisterPage();

private slots:
	void on_pushButton_CreateAccount_pressed();
	void on_exitButton_pressed();

private:
	Ui::RegisterPageClass ui;
};
