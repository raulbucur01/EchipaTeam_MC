#include "LobbyPage.h"

LobbyPage::LobbyPage(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
	connect(ui.exitButton, &QPushButton::pressed, this, &LobbyPage::on_exitButton_pressed);
}

void LobbyPage::on_exitButton_pressed()
{
	exit(0);
}

LobbyPage::~LobbyPage()
{}
