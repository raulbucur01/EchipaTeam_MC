#include "GamePage.h"

GamePage::GamePage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
	connect(ui.exitButton, &QPushButton::pressed, this, &GamePage::on_exitButton_pressed);
}

void GamePage::on_exitButton_pressed()
{
	exit(0);
}

GamePage::~GamePage()
{}
