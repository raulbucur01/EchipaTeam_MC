#pragma once

#include <QWidget>
#include "ui_LobbyPage.h"

class LobbyPage : public QWidget
{
	Q_OBJECT

public:
	LobbyPage(QWidget *parent = nullptr);
	~LobbyPage();

private:
	Ui::LobbyPageClass ui;
};
