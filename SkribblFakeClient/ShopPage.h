#pragma once

#include <QWidget>
#include "ui_ShopPage.h"

class ShopPage : public QWidget
{
	Q_OBJECT

public:
	ShopPage(QWidget *parent = nullptr);
	~ShopPage();

private:
	Ui::ShopPageClass ui;
};
