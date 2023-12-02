#pragma once

#include <QWidget>
#include "ui_MenuPage.h"

class MenuPage : public QWidget
{
	Q_OBJECT

public:
	MenuPage(QWidget *parent = nullptr);
	~MenuPage();

private:
	Ui::MenuPageClass ui;
};
