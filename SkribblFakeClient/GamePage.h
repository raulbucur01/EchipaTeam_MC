#pragma once

#include <QWidget>
#include "ui_GamePage.h"
#include <cpr/cpr.h>
#include "graph.h"

class GamePage : public QWidget
{
	Q_OBJECT

private slots:
	void on_exitButton_pressed();

public:
	GamePage(QWidget *parent = nullptr);
	~GamePage();
	void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);

private:
	void paintEvent(QPaintEvent* event);

private:
	Ui::GamePageClass ui;
	QRect rectangle;
	Graph g;
	vector<Node*> line;
	bool painting=false;
};
