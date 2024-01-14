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
#include <ranges>

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
        case 9:
            return "./Icons/Knight.jpeg";
        case 10:
            return "./Icons/Princess.jpeg";
        case 11:
            return "./Icons/Viking.jpeg";
        case 12:
            return "./Icons/Frankenstein.jpeg";
        case 13:
            return "./Icons/Unicorn.jpeg";
        case 14:
            return "./Icons/Vampire.jpeg";
        case 15:
            return "./Icons/Robot.jpeg";
        case 16:
            return "./Icons/Ghost.jpeg";
            // Add more cases for other indexes
        default:
            // Handle the case where the index is not recognized
            return "./Icons/Troll.jpeg";
        }
}
};

class MatchHistoryDialog : public QDialog {
    Q_OBJECT

public:
    MatchHistoryDialog(QWidget* parent = nullptr);
    ~MatchHistoryDialog();

    void setMatchHistory(std::vector<int>& obtainedScores);

private:
    QVBoxLayout* m_layout;
    QScrollArea* m_scrollArea;
    QLabel* m_averageScoreLabel;
    QLabel* m_gameNumberHeaderLabel;
    QLabel* m_obtainedScoreHeaderLabel;
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
    
    void RetrieveObtainedScores();

private slots:
	void on_exitButton_pressed();
	void on_pushButton_Back_pressed();
    void showIconSelectionDialog();
    void updateCurrentIcon(int newIconIndex);

    void on_matchHistoryButton_pressed();
    void showMatchHistoryDialog();

private:
	Ui::ProfilePageClass ui;
	Player m_player;
    int m_currentIconIndex;
    PageManager pages;
    std::vector<int> m_ownedIconIndexes;
    std::vector<int> m_obtainedScores;

    MatchHistoryDialog* m_matchHistoryDialog;
};

