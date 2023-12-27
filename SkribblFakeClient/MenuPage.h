#pragma once

#include <QWidget>
#include "ui_MenuPage.h"
#include "PageManager.h"

class MenuPage : public QWidget
{
	Q_OBJECT

public:
	MenuPage(QWidget* parent = nullptr, QString username = "nimeni");
	~MenuPage();

private slots:
	void on_pushButton_Profile_pressed();
	void on_pushButton_Shop_pressed();
	void on_pushButton_CreateLobby_pressed();
	void on_pushButton_JoinLobby_pressed();
	void on_pushButton_Logout_pressed();
	void on_exitButton_pressed();

private:
	Ui::MenuPageClass ui;
	QString m_username;
	PageManager pages;
};
