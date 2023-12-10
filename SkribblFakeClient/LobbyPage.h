#pragma once

#include <QWidget>
#include "ui_LobbyPage.h"

class LobbyPage : public QWidget
{
	Q_OBJECT


private slots:
	void on_exitButton_pressed();

public:
	LobbyPage(QWidget *parent = nullptr);
	~LobbyPage();

private:
	Ui::LobbyPageClass ui;
};
