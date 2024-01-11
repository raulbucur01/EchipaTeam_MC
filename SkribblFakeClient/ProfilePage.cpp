#include "ProfilePage.h"
#include "MenuPage.h"
#include <QScreen>

ProfilePage::ProfilePage(QWidget* parent, Player player)
	: QWidget(parent), m_player(player), m_currentIconIndex(0)
{
	ui.setupUi(this);
	setFixedSize(1000, 750);
	ui.groupBox_Profile->move((this->size().width() - ui.groupBox_Profile->size().width()) / 2, (this->size().height() - ui.groupBox_Profile->size().height()) / 2);
	ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
	connect(ui.exitButton, &QPushButton::pressed, this, &ProfilePage::on_exitButton_pressed);
	connect(ui.pushButton_Back, &QPushButton::pressed, this, &ProfilePage::on_pushButton_Back_pressed);
	connect(ui.iconButton, &QPushButton::clicked, this, &ProfilePage::showIconSelectionDialog);

	// Set the initial icon based on currentIconId
	m_currentIconIndex = m_player.GetCurrentIconId();
	QString iconPath = getIconPath(m_currentIconIndex);

	QPixmap pix(iconPath);
	QSize customIconSize(100, 100);  // Adjust the width and height as needed
	QPixmap scaledPixmap = pix.scaled(customIconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

	ui.iconButton->setIcon(QIcon(scaledPixmap));
	ui.iconButton->setIconSize(customIconSize);

	std::string str = m_player.GetName();
	QString qs = QString::fromLocal8Bit(str.c_str());
	ui.label_Username->setText(qs);
	DisplayScore();
	DisplayCoins();
	RetrieveOwnedIcons();
}

ProfilePage::~ProfilePage()
{
	cpr::Response response = cpr::Put(cpr::Url{ "http://localhost:18080/game/removePlayer" },
		cpr::Body{ "username=" + m_player.GetName() });
}

void ProfilePage::on_pushButton_Back_pressed()
{
	ui.groupBox_Profile->hide();
	ui.exitButton->hide();
	delete ui.groupBox_Profile;
	delete ui.exitButton;

	// Cum facem intoarcerea din profil inapoi la meniu?
}

void ProfilePage::showIconSelectionDialog() {
	IconSelectionDialog dialog(m_ownedIconIndexes, this);

	// Connect the iconSelected signal from the dialog to the updateCurrentIcon slot
	connect(&dialog, &IconSelectionDialog::iconSelected, this, &ProfilePage::updateCurrentIcon);

	dialog.exec();
}

void ProfilePage::updateCurrentIcon(int newIconIndex) {
	// Update the displayed icon on the main profile page
	m_currentIconIndex = newIconIndex;
	// Set the icon for the ui.iconButton
	QString iconPath = getIconPath(m_currentIconIndex);

	QPixmap pix(iconPath);
	QSize customIconSize(100, 100);  // Adjust the width and height as needed
	QPixmap scaledPixmap = pix.scaled(customIconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

	ui.iconButton->setIcon(QIcon(scaledPixmap));
	ui.iconButton->setIconSize(customIconSize);

	UpdateCurrentPlayerIconOnServer();
}

void ProfilePage::DisplayScore()
{
	std::string username = m_player.GetName();
	std::string url = "http://localhost:18080/getScore?username=" + username;
	cpr::Response response = cpr::Get(cpr::Url(url), cpr::Body{ "username=" + username});

	if (response.status_code == 200) {
		auto json = crow::json::load(response.text);
		if (json) {
			int score = json["Score"].i();
			ui.label_Score->setText("Score: " + QString::number(score));
		}
	}
	else {

		std::cerr << "Failed to get player's score from the server." << std::endl;
	}
}

void ProfilePage::DisplayCoins()
{
	std::string username = m_player.GetName();
	std::string url = "http://localhost:18080/getCoins?username=";
	cpr::Response response = cpr::Get(cpr::Url(url), cpr::Body{ "username=" + username });

	if (response.status_code == 200) {
		auto json = crow::json::load(response.text);
		if (json) {
			int coins = json["Coins"].i();
			ui.label_Coins->setText("Coins: " + QString::number(coins));
		}
	}
	else {

		std::cerr << "Failed to get player's coins from the server." << std::endl;
	}
}

void ProfilePage::UpdateCurrentPlayerIconOnServer()
{
	// aici trimitem la server indexul iconitei curente schimbate (adica m_currentIconIndex)
	// trebuie sa se updateze si in baza de date cu un nou currentIconId dat de cel ce este in momentul de cand se apeleaza functia asta
	// functia asta se apeleaza doar dupa ce userul isi alege o iconita
	std::string username = m_player.GetName();
	int currentIconID = m_player.GetCurrentIconId();
	std::string url = "http://localhost:18080/UpdateCurrentIconID";
	url += "?currentIconID=" + std::to_string(currentIconID);
	url += "&username=" + username;
    cpr::Response response = cpr::Get(cpr::Url{ url });

	
}

void ProfilePage::RetrieveOwnedIcons() {
	// Make a request to the server to get the player's owned icons
	// Update m_ownedIconIndexes based on the server response
	// trebuie request sa luam indexurile iconitelor cumparate de playerul curent cautat dupa nume (este functia "GetPurchasedIconIdsByPlayer"
	// in baza de date)
	// in m_ownedIconIndexes bagam indexurile venite de la server pt playerul curent
	// trimiti la server numele si aduci inapoi id-urile iconitelor pe care le are
}

void ProfilePage::on_exitButton_pressed()
{
	QCoreApplication::quit();
}

QString ProfilePage::getIconPath(int iconIndex) {
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