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
	DisplayCoins();
	RetrieveOwnedIcons();

	RetrieveObtainedScores();
	DisplayScore();
	m_matchHistoryDialog = new MatchHistoryDialog(this);
	connect(ui.matchHistoryButton, &QPushButton::pressed, this, &ProfilePage::showMatchHistoryDialog);
}

void ProfilePage::showMatchHistoryDialog() {
	m_matchHistoryDialog->setMatchHistory(m_obtainedScores);
	m_matchHistoryDialog->exec();
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
	int sum = 0;
	for (const auto& score : m_obtainedScores) {
		sum += score;
	}

	QString qs = QString::number(sum);
	ui.label_Score->setText("All time score: " + qs);
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
	std::string url = "http://localhost:18080/UpdateCurrentIconID";
	url += "?currentIconID=" + std::to_string(m_currentIconIndex);
	url += "&username=" + username;
	cpr::Response response = cpr::Put(cpr::Url{ url },
	cpr::Body{ "currentIconID=" + std::to_string(m_currentIconIndex) + "&username=" + username });

	if (response.status_code == 200) {
		auto json = crow::json::load(response.text);
		//QMessageBox::information(this, "Icon updated", QString::fromUtf8(response.text.data(), int(response.text.size())));
	}
	else if (response.status_code == 400)
	{
		auto json = crow::json::load(response.text);
		QMessageBox::warning(this, "Error!", QString::fromUtf8(response.text.data(), int(response.text.size())));
	}
	else if (response.status_code == 404) {
		auto json = crow::json::load(response.text);
		QMessageBox::warning(this, "Error!", QString::fromUtf8(response.text.data(), int(response.text.size())));
	}

}

void ProfilePage::RetrieveOwnedIcons() {
	// Make a request to the server to get the player's owned icons
	// Update m_ownedIconIndexes based on the server response
	// trebuie request sa luam indexurile iconitelor cumparate de playerul curent cautat dupa nume (este functia "GetPurchasedIconIdsByPlayer"
	// in baza de date)
	// in m_ownedIconIndexes bagam indexurile venite de la server pt playerul curent
	// trimiti la server numele si aduci inapoi id-urile iconitelor pe care le are

	std::string username = m_player.GetName();
	
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/RetrieveOwnedIcons" },
		cpr::Body{ "username=" + username });
	int index;

	if (response.status_code == 200) {

		auto& ownedIcons = crow::json::load(response.text)["ownedIcons"];
		for (const auto& icon : ownedIcons)
		{
			index = icon.i();
			m_ownedIconIndexes.push_back(index);
		}

		//QMessageBox::information(this, "Icons Retrieved!", QString::fromUtf8(response.text.data(), int(response.text.size())));
	}
	else {
		auto json = crow::json::load(response.text);
		QMessageBox::information(this, "Error!", QString::fromUtf8(response.text.data(), int(response.text.size())));
	}
	

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

void ProfilePage::on_matchHistoryButton_pressed() {
	// Create the MatchHistoryDialog if not already created
	if (!m_matchHistoryDialog) {
		m_matchHistoryDialog = new MatchHistoryDialog(this);
	}
	// Show the MatchHistoryDialog
	m_matchHistoryDialog->show();
}

void ProfilePage::RetrieveObtainedScores() {
	// Fetch obtained scores from the server and update m_obtainedScores
	// ...

	std::string username = m_player.GetName();

	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/getObtainedScores" },
	cpr::Body{ "username=" + username });
	int index;

	if (response.status_code == 200) {

		auto& obtainedScores= crow::json::load(response.text)["obtainedScores"];
		for (const auto& score : obtainedScores)
		{
			index = score.i();
			m_obtainedScores.push_back(index);
		}
		
		//pentru verificarea decomenteaza linia de mai jos
		//QMessageBox::information(this, "Scors Obtained!", QString::fromUtf8(response.text.data(), int(response.text.size())));
	}
	else {
		auto json = crow::json::load(response.text);
		QMessageBox::information(this, "Error!", QString::fromUtf8(response.text.data(), int(response.text.size())));
	}

}

MatchHistoryDialog::MatchHistoryDialog(QWidget* parent)
	: QDialog(parent) {
	setWindowTitle("Match History");

	m_layout = new QVBoxLayout(this);
	m_scrollArea = new QScrollArea(this);
	m_scrollArea->setWidgetResizable(true);

	QWidget* scrollWidget = new QWidget;
	QVBoxLayout* scrollLayout = new QVBoxLayout(scrollWidget);
	m_scrollArea->setWidget(scrollWidget);

	m_averageScoreLabel = new QLabel("Average Score: N/A");
	m_gameNumberHeaderLabel = new QLabel("Game Number");
	m_obtainedScoreHeaderLabel = new QLabel("Obtained Score");

	// Create a QHBoxLayout for the header labels
	QHBoxLayout* headerLayout = new QHBoxLayout;
	headerLayout->addWidget(m_gameNumberHeaderLabel);
	headerLayout->addWidget(m_obtainedScoreHeaderLabel);

	m_layout->addWidget(m_averageScoreLabel);
	m_layout->addLayout(headerLayout);  // Add the header labels layout
	m_layout->addWidget(m_scrollArea);
}

MatchHistoryDialog::~MatchHistoryDialog() {
	// Cleanup if needed.
}

void MatchHistoryDialog::setMatchHistory(std::vector<int>& obtainedScores) {
	// Clear previous rows
	QLayoutItem* item;
	while ((item = m_scrollArea->widget()->layout()->takeAt(0)) != nullptr) {
		delete item->widget();
		delete item;
	}

	// Calculate average score
	double averageScore = 0.0;
	if (!obtainedScores.empty()) {
		for (int score : obtainedScores) {
			averageScore += score;
		}
		averageScore /= obtainedScores.size();
	}

	// Set the average score label
	m_averageScoreLabel->setText("Average Score: " + QString::number(averageScore));

	// Access the layout of the scroll widget
	QVBoxLayout* scrollLayout = qobject_cast<QVBoxLayout*>(m_scrollArea->widget()->layout());
	if (!scrollLayout) {
		qWarning() << "Failed to get the scroll layout.";
		return;
	}

	// Populate the scroll area with rows
	int limit = obtainedScores.size();
	for (int i : std::ranges::iota_view(0, limit)) {
		QLabel* gameNumberLabel = new QLabel(QString::number(i + 1));
		QLabel* scoreLabel = new QLabel(QString::number(obtainedScores[i]));

		QHBoxLayout* rowLayout = new QHBoxLayout;
		rowLayout->addWidget(gameNumberLabel);
		rowLayout->addWidget(scoreLabel);

		scrollLayout->addLayout(rowLayout);
	}
}

