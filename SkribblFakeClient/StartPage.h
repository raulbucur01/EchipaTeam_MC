#pragma once

#include <QMainWindow>
#include "ui_StartPage.h"
#include "LoginPage.h"
#include "PageManager.h"

namespace Window
{
	class StartPage : public QMainWindow
	{
		Q_OBJECT

	public:
		StartPage(QWidget* parent = nullptr);
		~StartPage();


	private slots:
		void on_pushButton_Start_pressed();
		void on_exitButton_pressed();

	private:
		Ui::StartPageClass ui;
		LoginPage* loginPage;
		PageManager pages;
	};

}
