#pragma once

#include <QWidget>
#include "ui_ProfilePage.h"

class ProfilePage : public QWidget
{
	Q_OBJECT

public:
	ProfilePage(QWidget *parent = nullptr);
	~ProfilePage();

private:
	Ui::ProfilePageClass ui;
};
