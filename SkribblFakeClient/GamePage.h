#pragma once

#include <QWidget>
#include "ui_GamePage.h"
#include <cpr/cpr.h>
#include "graph.h"
#include <QStringListModel>
#include <QStandarditemmodel>
#include<QPainter>

class GamePage : public QWidget
{
	Q_OBJECT

private slots:
	void on_exitButton_pressed();
	void sendMessage();
	void on_black_button_pressed();
	void on_blue_button_pressed();
	void on_red_button_pressed();
	void on_orange_button_pressed();
	void on_pink_button_pressed();
	void on_purple_button_pressed();
	void on_green_button_pressed();
	void on_gray_button_pressed();
	void on_yellow_button_pressed();
	void on_brown_button_pressed();
	void on_white_button_pressed();
	void on_undo_button_pressed();
	void on_delete_all_pressed();
	//void updateChat();

public:
	GamePage(QWidget* parent = nullptr);
	~GamePage();
	void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void setupTabela();
	void setupChat();
	void setupCulori();

private:
	void paintEvent(QPaintEvent* event);

private:
	QStandardItemModel* messages;
	Ui::GamePageClass ui;
	QRect rectangle;
	Graph g;
	vector<Node*> line;
	bool painting = false;
	QColor currentColor;
	std::vector<std::string> m_players;
};
