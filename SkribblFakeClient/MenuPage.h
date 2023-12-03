#pragma once

#include <QWidget>
#include "ui_MenuPage.h"

class MenuPage : public QWidget
{
	Q_OBJECT

public:
	MenuPage(QWidget *parent = nullptr);
	~MenuPage();

private slots:
	void on_pushButton_CreateLobby_pressed();
	void on_pushButton_JoinLobby_pressed();
	void on_pushButton_Logout_pressed();

private:
	Ui::MenuPageClass ui;
};
