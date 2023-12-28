#include "PageManager.h"
#include "GamePage.h"
#include "LoginPage.h"
#include "RegisterPage.h"
#include "ShopPage.h"
#include "ProfilePage.h"
#include "MenuPage.h"

PageManager::~PageManager()
{
	destroyAllPages();
}

QWidget* PageManager::createGamePage(QWidget* parrent,Player player)
{
	QWidget* newGamePage = new GamePage(parrent,player);
	pages.append(newGamePage);
	return newGamePage;
}

QWidget* PageManager::createLoginPage(QWidget* parrent)
{
	QWidget* newLoginPage = new LoginPage(parrent);
	pages.append(newLoginPage);
	return newLoginPage;
}

QWidget* PageManager::createRegisterPage(QWidget* parrent)
{
	QWidget* newRegisterPage = new RegisterPage(parrent);
	pages.append(newRegisterPage);
	return newRegisterPage;
}

QWidget* PageManager::createMenuPage(QWidget* parrent,crow::json::rvalue player)//QString username)
{
	QWidget* newMenuPage = new MenuPage(parrent,player);
	pages.append(newMenuPage);
	return newMenuPage;
}

QWidget* PageManager::createProfilePage(QWidget* parrent,QString username)
{
	QWidget* newProfilePage = new ProfilePage(parrent, username);
	pages.append(newProfilePage);
	return newProfilePage;
}

QWidget* PageManager::createShopPage(QWidget* parrent)
{
	QWidget* newShopPage = new MenuPage(parrent);
	pages.append(newShopPage);
	return newShopPage;
}

void PageManager::destroyAllPages()
{
	qDeleteAll(pages);
	pages.clear();
}


