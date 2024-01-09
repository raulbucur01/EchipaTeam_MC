#include "ShopPage.h"
#include <QScreen>
#include <QMessagebox.h>

ShopPage::ShopPage(QWidget* parent, Player player)
    : QWidget(parent), m_player{ player }
{
    ui.setupUi(this);
    setFixedSize(1000, 750);

    // Double the size of QGroupBox
    int newGroupBoxWidth = ui.groupBox->width() * 2;
    int newGroupBoxHeight = ui.groupBox->height() * 2;
    ui.groupBox->resize(newGroupBoxWidth, newGroupBoxHeight);

    // Center the QGroupBox
    ui.groupBox->move((this->size().width() - ui.groupBox->width()) / 2, (this->size().height() - ui.groupBox->height()) / 2);

    ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
    connect(ui.exitButton, &QPushButton::pressed, this, &ShopPage::on_exitButton_pressed);
    connect(ui.pushButton_Icon1, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon2, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon3, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon4, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon5, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon6, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon7, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon8, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);

    QScrollArea* scrollArea = new QScrollArea(ui.groupBox);
    QWidget* scrollWidget = new QWidget;
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);

    QGridLayout* gridLayout = new QGridLayout(scrollWidget);
    gridLayout->setAlignment(Qt::AlignTop);

    // Add your buttons to the gridLayout
    addIconButtonToGridLayout("./Icons/Siren.jpeg", ui.pushButton_Icon1, gridLayout, 0, 0);
    addIconButtonToGridLayout("./Icons/Gladiator.jpeg", ui.pushButton_Icon2, gridLayout, 0, 1);
    addIconButtonToGridLayout("./Icons/Pig.jpeg", ui.pushButton_Icon3, gridLayout, 1, 0);
    addIconButtonToGridLayout("./Icons/Wizard.jpeg", ui.pushButton_Icon4, gridLayout, 1, 1);
    addIconButtonToGridLayout("./Icons/Alien.jpeg", ui.pushButton_Icon5, gridLayout, 2, 0);
    addIconButtonToGridLayout("./Icons/Leprechaun.jpeg", ui.pushButton_Icon6, gridLayout, 2, 1);
    addIconButtonToGridLayout("./Icons/Snake.jpeg", ui.pushButton_Icon7, gridLayout, 3, 0);
    addIconButtonToGridLayout("./Icons/Panda.jpeg", ui.pushButton_Icon8, gridLayout, 3, 1);

    // Add the player's balance label below the scroll area
    QLabel* balanceLabel = new QLabel("Balance: " + QString::number(m_player.GetCoins()));
    balanceLabel->setObjectName("balanceLabel"); // Set an object name for later retrieval
    balanceLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout* groupBoxLayout = new QVBoxLayout(ui.groupBox);
    groupBoxLayout->addWidget(scrollArea);
    groupBoxLayout->addWidget(balanceLabel);
}

void ShopPage::addIconButtonToGridLayout(const QString& iconPath, QPushButton* button, QGridLayout* layout, int row, int col)
{
    QPixmap pix(iconPath);

    // Set the custom size for the icon
    QSize customIconSize(150, 150);  // Adjust the width and height as needed

    // Scale the pixmap to the custom size
    QPixmap scaledPixmap = pix.scaled(customIconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Set the scaled pixmap as the button's icon
    button->setIcon(QIcon(scaledPixmap));

    // Set the size of the icon to cover the entire button
    QSize iconSize(customIconSize);
    button->setIconSize(iconSize);

    // Set the height of the button
    button->setFixedHeight(150);

    // Add the button to the grid layout
    layout->addWidget(button, row, col);
}

void ShopPage::on_iconButton_pressed()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    if (clickedButton)
    {
        // Determine which icon button was clicked based on its properties
        int iconIndex = -1;
        if (clickedButton == ui.pushButton_Icon1) iconIndex = 1;
        else if (clickedButton == ui.pushButton_Icon2) iconIndex = 2;
        else if (clickedButton == ui.pushButton_Icon3) iconIndex = 3;
        else if (clickedButton == ui.pushButton_Icon4) iconIndex = 4;
        else if (clickedButton == ui.pushButton_Icon5) iconIndex = 5;
        else if (clickedButton == ui.pushButton_Icon6) iconIndex = 6;
        else if (clickedButton == ui.pushButton_Icon7) iconIndex = 7;
        else if (clickedButton == ui.pushButton_Icon8) iconIndex = 8;
        // ... (add more conditions for other buttons)

        // Now you have the index of the clicked button (iconIndex)
        // You can use this index to identify the button and handle the purchase logic

        std::string username = m_player.GetName();
        ProcessPurchase(username, iconIndex);
    }
}

void ShopPage::ProcessPurchase(const std::string& username, int iconIndex)
{
    // procesare purchase
    QString message = QString("You pressed an icon with index %1!").arg(iconIndex);
    QMessageBox::warning(this, "Purchase", message);

    // -se trimite la server username-ul si indexul pozei pe care vrea sa o cumpere
    // -se vor face verificari ca userul sa nu aiba deja iconita respectiva
    // -faptul ca userul exista nu mai e necesar de verificat ca s-a facut deja in login si e evident ca exista
    // -daca totul e in regula se fac modificarile necesare in baza de date si se trimite raspuns aici dupa care vom afisa un mesaj de confirmare
    // a tranzactiei
    // MOMENTAN FIECARE ICONITA COSTA 20 DE BANUTI

    // cand se ajunge cu raspunsul aici se trimit noile valori ca sa putem da update la label-ul balance si la m_player
}


ShopPage::~ShopPage()
{
	cpr::Response response = cpr::Put(cpr::Url{ "http://localhost:18080/game/removePlayer" },
		cpr::Body{ "username=" + m_player.GetName() });
}

void ShopPage::on_exitButton_pressed()
{
	QCoreApplication::quit();
}
