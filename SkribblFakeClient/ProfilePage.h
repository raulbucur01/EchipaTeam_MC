#pragma once

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include "ui_ProfilePage.h"

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

private:
	Ui::ProfilePageClass ui;
	QString m_username;
	QNetworkAccessManager m_networkManager;
};
