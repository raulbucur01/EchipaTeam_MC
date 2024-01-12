#pragma once

#include <QWidget>
#include "ui_ShopPage.h"
#include <QPixmap.h>
#include "Player.h"
#include <cpr/cpr.h>
#include <crow.h>
#include <qboxlayout.h>
#include "PageManager.h"

class ShopPage : public QWidget
{
	Q_OBJECT

public:
	ShopPage(QWidget *parent = nullptr, Player player = {});
	~ShopPage();
	void addIconButtonToGridLayout(const QString& iconPath, QPushButton* button, QGridLayout* layout, int row, int col);
	void ProcessPurchase(const std::string& username, int iconIndex);

private slots:
	void on_exitButton_pressed();
	void on_iconButton_pressed();
	void on_backButton_pressed();

private:
	Ui::ShopPageClass ui;
	Player m_player;
	PageManager pages;
};
