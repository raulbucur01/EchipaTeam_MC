#pragma once

#include <QWidget>
#include "ui_GamePage.h"
#include <cpr/cpr.h>
class GamePage : public QWidget
{
	Q_OBJECT

private slots:
	void on_exitButton_pressed();

public:
	GamePage(QWidget *parent = nullptr);
	~GamePage();

private:
	void paintEvent(QPaintEvent* event);

private:
	Ui::GamePageClass ui;
	QRect rectangle;
};
