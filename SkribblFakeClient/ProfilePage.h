#pragma once

#include <QWidget>
#include <QDebug>
#include "ui_ProfilePage.h"
#include <cpr/cpr.h>

class ProfilePage : public QWidget
{
	Q_OBJECT

public:
	ProfilePage(QWidget *parent = nullptr, QString username = "nimeni");
	~ProfilePage();

private slots:
	void on_exitButton_pressed();
	void DisplayScore();
	void DisplayCoins();
	void on_pushButton_Back_pressed();

private:
	Ui::ProfilePageClass ui;
	QString m_username;
	//QNetworkAccessManager m_networkManager;
};
