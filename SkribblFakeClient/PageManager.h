#pragma once
#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H

#include <QList>

class QWidget;

class PageManager
{
public:
    PageManager()=default;
    ~PageManager();

    QWidget* createGamePage(QWidget* parrent);
    QWidget* createLoginPage(QWidget* parrent);
    QWidget* createRegisterPage(QWidget* parrent);
    QWidget* createMenuPage(QWidget* parrent, QString username);
    QWidget* createProfilePage(QWidget* parrent,QString username);
    QWidget* createShopPage(QWidget* parrent);


    void destroyAllPages();

private:
    QList<QWidget*> pages;
};

#endif // PAGEMANAGER_H

