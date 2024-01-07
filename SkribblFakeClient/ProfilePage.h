#pragma once

#include <QWidget>
#include <QDebug>
#include "ui_ProfilePage.h"
#include <cpr/cpr.h>
#include "Player.h"
#include <QString>

class ProfilePage : public QWidget
{
	Q_OBJECT

public:
	ProfilePage(QWidget* parent = nullptr, Player player = {});
	~ProfilePage();

private slots:
	void on_exitButton_pressed();
	void DisplayScore();
	void DisplayCoins();
	void on_pushButton_Back_pressed();

private:
	Ui::ProfilePageClass ui;
	Player m_player;
	//QNetworkAccessManager m_networkManager;
};

