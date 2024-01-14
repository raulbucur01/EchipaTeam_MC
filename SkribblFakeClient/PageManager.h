#pragma once
#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <QList>
#include "Player.h"
#include "crow.h"
class QWidget;

class PageManager
{
public:
    PageManager()=default;
    ~PageManager();

    QWidget* createGamePage(QWidget* parrent,Player player,bool leader);
    QWidget* createLoginPage(QWidget* parrent);
    QWidget* createRegisterPage(QWidget* parrent);
    QWidget* createMenuPage(QWidget* parrent,crow::json::rvalue player);
    QWidget* createProfilePage(QWidget* parrent,Player player);
    QWidget* createShopPage(QWidget* parrent, Player player);


    void destroyAllPages();

private:
    QList<QWidget*> pages;
};

#endif // PAGEMANAGER_H

