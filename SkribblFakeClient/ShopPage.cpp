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
    connect(ui.pushButton_Icon9, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon10, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon11, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon12, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon13, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon14, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon15, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);
    connect(ui.pushButton_Icon16, &QPushButton::clicked, this, &ShopPage::on_iconButton_pressed);

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
    addIconButtonToGridLayout("./Icons/Knight.jpeg", ui.pushButton_Icon9, gridLayout, 4, 0);
    addIconButtonToGridLayout("./Icons/Princess.jpeg", ui.pushButton_Icon10, gridLayout, 4, 1);
    addIconButtonToGridLayout("./Icons/Viking.jpeg", ui.pushButton_Icon11, gridLayout, 5, 0);
    addIconButtonToGridLayout("./Icons/Frankenstein.jpeg", ui.pushButton_Icon12, gridLayout, 5, 1);
    addIconButtonToGridLayout("./Icons/Unicorn.jpeg", ui.pushButton_Icon13, gridLayout, 6, 0);
    addIconButtonToGridLayout("./Icons/Vampire.jpeg", ui.pushButton_Icon14, gridLayout, 6, 1);
    addIconButtonToGridLayout("./Icons/Robot.jpeg", ui.pushButton_Icon15, gridLayout, 7, 0);
    addIconButtonToGridLayout("./Icons/Ghost.jpeg", ui.pushButton_Icon16, gridLayout, 7, 1);

    // Add the player's balance label below the scroll area
    //QLabel* balanceLabel = new QLabel("Balance: " + QString::number(m_player.GetCoins()));
    ui.label_Balance->setAlignment(Qt::AlignCenter);
    ui.label_Balance->setText("Balance: " + QString::number(m_player.GetCoins()));

    QVBoxLayout* groupBoxLayout = new QVBoxLayout(ui.groupBox);
    groupBoxLayout->addWidget(scrollArea);
    groupBoxLayout->addWidget(ui.label_Balance);

    connect(ui.pushButton_Back, &QPushButton::clicked, this, &ShopPage::on_backButton_pressed);
    groupBoxLayout->addWidget(ui.pushButton_Back);
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
        else if (clickedButton == ui.pushButton_Icon9) iconIndex = 9;
        else if (clickedButton == ui.pushButton_Icon10) iconIndex = 10;
        else if (clickedButton == ui.pushButton_Icon11) iconIndex = 11;
        else if (clickedButton == ui.pushButton_Icon12) iconIndex = 12;
        else if (clickedButton == ui.pushButton_Icon13) iconIndex = 13;
        else if (clickedButton == ui.pushButton_Icon14) iconIndex = 14;
        else if (clickedButton == ui.pushButton_Icon15) iconIndex = 15;
        else if (clickedButton == ui.pushButton_Icon16) iconIndex = 16;
        // ... (add more conditions for other buttons)

        // Now you have the index of the clicked button (iconIndex)
        // You can use this index to identify the button and handle the purchase logic

        std::string username = m_player.GetName();
        ProcessPurchase(username, iconIndex);
    }
}

void ShopPage::on_backButton_pressed()
{
    ui.exitButton->hide();
    ui.scrollArea->hide();
    ui.groupBox->hide();
    delete ui.groupBox;
    delete ui.exitButton;

    // faci request catre server de trimit numele (ruta sa o faci cu nume unic de ex /ReturInfoPlayer)
    // faci un handler pt ruta care sa returneze ca in loginhandler ( practic un player -> info despre el)

    std::string username = m_player.GetName();
    std::string url = "http://localhost:18080/getPlayerInformation";
    cpr::Response response = cpr::Get(cpr::Url(url), cpr::Body{ "username=" + username });
    if (response.status_code == 200)
    {
        crow::json::rvalue player = crow::json::load(response.text);
        QWidget* menuPage = pages.createMenuPage(this, player);
        menuPage->show();
    }
    else {
        auto json = crow::json::load(response.text);
        QMessageBox::warning(this, "Error!", QString::fromUtf8(response.text.data(), int(response.text.size())));
    }
}

void ShopPage::ProcessPurchase(const std::string& username, int iconIndex)
{
    // procesare purchase
   /* QString message = QString("You pressed an icon with index %1!").arg(iconIndex);
    QMessageBox::warning(this, "Purchase", message);*/

    // -se trimite la server username-ul si iconIndex reprezentand iconita pe care vrea sa o cumpere
    // -se proceseaza la nivel de server purchase-ul (se vor face verificari ca userul sa nu aiba deja iconita respectiva,
    //  sa aiba destui bani, etc)
    // -faptul ca userul exista nu mai e necesar de verificat ca s-a facut deja in login si e evident ca exista
    // -se trimite raspuns si daca purchase-ul s-a efectuat cu succes se afiseaza un mesaj, daca nu mesaj ca nu s-a putut efectua
    // (e nevoie de un error code pt cazul in care are deja acea iconita cumparata, inca unul pt cazul in care nu are suficienti bani)
    // MOMENTAN FIECARE ICONITA COSTA 20 DE BANUTI
    // cand ne intoarcem de la server cu un purchase care s-a putut efectua actualizam aici balance-ul in label si in clasa player
    std::string url = "http://localhost:18080/ProcessPurchase";
    cpr::Response response = cpr::Put(cpr::Url{ url },
    cpr::Body{ "currentIconID=" + std::to_string(iconIndex) + "&username=" + username });
   
    if (response.status_code == 200)
    {

        auto json = crow::json::load(response.text);
        if (json) {
            int coins = json["Coins"].i();
            ui.label_Balance->setText("Balance: " + QString::number(coins));
            m_player.SetCoins(coins);
        }
        QMessageBox::information(this, "Purchase complete!", "Your icon was purchased successfully!");
    }
    else {
        auto json = crow::json::load(response.text);
        QMessageBox::warning(this, "Error!", QString::fromUtf8(response.text.data(), int(response.text.size())));
    }



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
