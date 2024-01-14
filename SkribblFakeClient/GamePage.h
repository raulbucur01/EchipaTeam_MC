#pragma once

#include <QWidget>
#include "ui_GamePage.h"
#include <cpr/cpr.h>
#include "graph.h"
#include <QStringListModel>
#include <QStandarditemmodel>
#include<QPainter>
#include "Player.h"
#include "MenuPage.h"
#include "Word.h"
#include <array>
#include <QtConcurrent>
#include "PageManager.h"
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
	void createThread();
	void updateChat();
	void updateTable();
	void updateDrawing();
	void on_word1Button_pressed();
	void on_word2Button_pressed();
	void on_word3Button_pressed();
	void on_startButton_pressed();
	void on_exitCurrentGame_pressed();
	

public:
	GamePage(QWidget* parent = nullptr, Player player = {});
	virtual ~GamePage();
	void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void setupTabela();
	void setupChat();
	void setupCulori();
	void wordChoosingSequence();
	void randomWordsFromDB();
	void updateTimer();

private:
	void paintEvent(QPaintEvent* event);

private:
	QStandardItemModel* messages;
	Ui::GamePageClass ui;
	QRect* rectangle;
	Graph g;
	vector<Node*> line;
	bool painting = false;
	QColor currentColor;
	std::vector<Player> m_players;
	Player m_playerCurrent;
	Word word;
	bool canPaint = false;
	std::array<std::string, 3>words;
	bool isPainter=true;
	QTimer* gameTimer;
	int seconds;
	QMutex lineMutex;
	QMutex gMutex;
	PageManager pages;
};
