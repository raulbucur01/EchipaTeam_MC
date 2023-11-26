#pragma once

#include <QMainWindow>
#include "ui_StartPage.h"

class StartPage : public QMainWindow
{
	Q_OBJECT

public:
	StartPage(QWidget *parent = nullptr);
	~StartPage();

private:
	Ui::StartPageClass ui;
};
