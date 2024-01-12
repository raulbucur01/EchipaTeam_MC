#pragma once

#include <QWidget>
#include <QDebug>
#include "ui_ProfilePage.h"
#include <cpr/cpr.h>
#include "Player.h"
#include <QString>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollarea.h>
#include <qmessagebox.h>
#include "PageManager.h"

class IconSelectionDialog : public QDialog {
    Q_OBJECT

public:
    IconSelectionDialog(const std::vector<int>& ownedIconIndexes, QWidget* parent = nullptr)
        : QDialog(parent), m_ownedIconIndexes(ownedIconIndexes) {
        setWindowTitle("Select Icon");

        QVBoxLayout* layout = new QVBoxLayout(this);

        // Create a scroll area for the icons
        QScrollArea* scrollArea = new QScrollArea(this);
        QWidget* scrollWidget = new QWidget;
        QVBoxLayout* scrollLayout = new QVBoxLayout(scrollWidget);
        scrollArea->setWidget(scrollWidget);
        scrollArea->setWidgetResizable(true);
        layout->addWidget(scrollArea);

        for (int iconIndex : m_ownedIconIndexes) {
            QPushButton* iconButton = new QPushButton(this);
            iconButton->setFixedSize(100, 100); // Square shape
            setIconButtonIcon(iconButton, iconIndex); // Set the icon for the button

            connect(iconButton, &QPushButton::clicked, [this, iconIndex]() {
                emit iconSelected(iconIndex);
                close();
                });

            // Add the icon button to the scroll layout
            scrollLayout->addWidget(iconButton);
        }
    }

signals:
    void iconSelected(int iconIndex);

private:
    std::vector<int> m_ownedIconIndexes;

    void setIconButtonIcon(QPushButton* button, int iconIndex) {
        QString iconPath = getIconPath(iconIndex);

        QPixmap pix(iconPath);
        QSize customIconSize(150, 150);  // Adjust the width and height as needed
        QPixmap scaledPixmap = pix.scaled(customIconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        button->setIcon(QIcon(scaledPixmap));
        button->setIconSize(customIconSize);
    }

    QString getIconPath(int iconIndex) {
        switch (iconIndex) {
        case 0:
            return "./Icons/Troll.jpeg";
        case 1:
            return "./Icons/Siren.jpeg";
        case 2:
            return "./Icons/Gladiator.jpeg";
        case 3:
            return "./Icons/Pig.jpeg";
        case 4:
            return "./Icons/Wizard.jpeg";
        case 5:
            return "./Icons/Alien.jpeg";
        case 6:
            return "./Icons/Leprechaun.jpeg";
        case 7:
            return "./Icons/Snake.jpeg";
        case 8:
            return "./Icons/Panda.jpeg";
            // Add more cases for other indexes
        default:
            // Handle the case where the index is not recognized
            return "./Icons/default_icon.jpeg";
        }
}
};

class ProfilePage : public QWidget
{
	Q_OBJECT

public:
	ProfilePage(QWidget* parent = nullptr, Player player = {});
	~ProfilePage();
	void RetrieveOwnedIcons();
	void DisplayScore();
	void DisplayCoins();
    void UpdateCurrentPlayerIconOnServer();
    QString getIconPath(int iconIndex);

private slots:
	void on_exitButton_pressed();
	void on_pushButton_Back_pressed();
    void showIconSelectionDialog();
    void updateCurrentIcon(int newIconIndex);

private:
	Ui::ProfilePageClass ui;
	Player m_player;
    int m_currentIconIndex;
    PageManager pages;
    std::vector<int> m_ownedIconIndexes;
};

