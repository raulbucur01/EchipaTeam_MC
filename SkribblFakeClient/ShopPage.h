#pragma once

#include <QWidget>
#include "ui_ShopPage.h"
#include <QPixmap.h>
#include "Player.h"

class ShopPage : public QWidget
{
	Q_OBJECT

public:
	ShopPage(QWidget *parent = nullptr, Player player = {});
	~ShopPage();

private:
	Ui::ShopPageClass ui;
};
