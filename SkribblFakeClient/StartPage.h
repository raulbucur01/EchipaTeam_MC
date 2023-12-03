#pragma once

#include <QMainWindow>
#include "ui_StartPage.h"
#include "LoginPage.h"

class StartPage : public QMainWindow
{
	Q_OBJECT

public:
	StartPage(QWidget *parent = nullptr);
	~StartPage();

private slots:
	void on_pushButton_Start_pressed();

private:
	Ui::StartPageClass ui;
	LoginPage* loginPage;
};
