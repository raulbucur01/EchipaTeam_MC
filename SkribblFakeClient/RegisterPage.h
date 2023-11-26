#pragma once

#include <QWidget>
#include "ui_RegisterPage.h"

class RegisterPage : public QWidget
{
	Q_OBJECT

public:
	RegisterPage(QWidget *parent = nullptr);
	~RegisterPage();

private:
	Ui::RegisterPageClass ui;
};
