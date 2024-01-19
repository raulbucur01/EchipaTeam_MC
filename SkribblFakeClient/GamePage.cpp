#include "GamePage.h"
#include <QScreen>
#include<QPainter>
#include<QMouseEvent>
#include<QTableWidget>
#include<QHeaderView>
#include<QTableWidgetItem>
#include<QStringListModel>
#include <crow.h>
#include <QTimer>
#include<QGraphicsEffect>
#include <QMessagebox.h>
#include <unordered_set>
#include <algorithm>
#include <ctime>
std::string boolToString(bool painting)
{
	return painting ? "true" : "false";
}
void GamePage::sendMessage()
{

	//QString message = "You: " + ui.mesageBox->toPlainText();
	/*if (!message.isEmpty())
	{
		messages->appendRow(new QStandardItem(message));
		ui.mesageBox->clear();
	}
	*/
	//ui.displayMessage->setModel(messages);
	std::string word = ui.mesageBox->toPlainText().toUtf8().constData();
	ui.mesageBox->clear();
	auto res = cpr::Post(cpr::Url{ "http://localhost:18080/chat/send" },
		cpr::Body{ "username=" + m_playerCurrent.GetName() + "&message=" + word });
}

void GamePage::on_black_button_pressed()
{
	currentColor = Qt::black;
}

void GamePage::on_blue_button_pressed()
{
	currentColor = Qt::blue;
}

void GamePage::on_red_button_pressed()
{
	currentColor = Qt::red;
}

void GamePage::on_orange_button_pressed()
{
	currentColor = QColor::fromRgb(255, 165, 0);
}

void GamePage::on_pink_button_pressed()
{
	currentColor = QColor::fromRgb(255, 182, 193);
}

void GamePage::on_purple_button_pressed()
{
	currentColor = Qt::magenta;
}

void GamePage::on_green_button_pressed()
{
	currentColor = Qt::green;
}

void GamePage::on_gray_button_pressed()
{
	currentColor = Qt::gray;
}

void GamePage::on_yellow_button_pressed()
{
	currentColor = Qt::yellow;
}

void GamePage::on_brown_button_pressed()
{
	currentColor = QColor::fromRgb(139, 69, 19);
}

void GamePage::on_white_button_pressed()
{
	currentColor = Qt::white;
}

void GamePage::on_undo_button_pressed()
{
	g.deletelast();
	update();
}

void GamePage::on_delete_all_pressed()
{
	g.clear();
	update();
}

void GamePage::on_word1Button_pressed()
{
	ui.veil->hide();
	ui.horizontalLayoutWidget->hide();
	auto res = cpr::Post(cpr::Url{ "http://localhost:18080/choosingWord" },
		cpr::Body{ "word=" + words[0] });
	//ui.wordLabel->setText(QString::fromUtf8(words[0].c_str()));
	canPaint = true;
	choiceMade = true;
	seconds = 0;
	gameTimer->start(1000);
	connect(gameTimer.get(), &QTimer::timeout, this, &GamePage::updateTimer);
}

void GamePage::on_word2Button_pressed()
{
	ui.veil->hide();
	ui.horizontalLayoutWidget->hide();
	auto res = cpr::Post(cpr::Url{ "http://localhost:18080/choosingWord" },
		cpr::Body{ "word=" +words[1]});
	//ui.wordLabel->setText(QString::fromUtf8(words[1].c_str()));
	canPaint = true;
	choiceMade = true;
	seconds = 0;
	gameTimer->start(1000);
	connect(gameTimer.get(), &QTimer::timeout, this, &GamePage::updateTimer);
}

void GamePage::on_word3Button_pressed()
{
	ui.veil->hide();
	ui.horizontalLayoutWidget->hide();
	auto res = cpr::Post(cpr::Url{ "http://localhost:18080/choosingWord" },
		cpr::Body{ "word=" + words[2] });
	//ui.wordLabel->setText(QString::fromUtf8(words[2].c_str()));
	canPaint = true;
	choiceMade = true;
	seconds = 0;
	gameTimer->start(1000);
	connect(gameTimer.get(), &QTimer::timeout, this, &GamePage::updateTimer);
}

void GamePage::on_startButton_pressed()
{
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/startGame" });
	ui.startButton->hide();
	if (isPainter == true)
	{
		randomWordsFromDB();
	}
	wordChoosingSequence();
}

void GamePage::on_exitCurrentGame_pressed()
{
	/*ui.gridLayoutWidget->hide();
	ui.horizontalLayoutWidget->hide();
	ui.verticalLayoutWidget->hide();
	ui.exitButton->hide();
	ui.exitCurrentGame->hide();
	ui.someoneChoosing->hide();
	ui.startButton->hide();
	ui.tabelaScor->hide();
	ui.timerLabel->hide();
	ui.veil->hide();
	ui.wordLabel->hide();

	delete rectangle;
	delete ui.horizontalLayoutWidget;
	delete ui.gridLayoutWidget;
	delete ui.verticalLayoutWidget;
	delete ui.exitButton;
	delete ui.exitCurrentGame;
	delete ui.someoneChoosing;
	delete ui.startButton;
	delete ui.tabelaScor;
	delete ui.timerLabel;
	delete ui.veil;
	delete ui.wordLabel;

	std::string username = m_playerCurrent.GetName();
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
	}*/
}

void GamePage::veilHide()
{
	ui.veil->hide();
	ui.horizontalLayoutWidget->hide();
	ui.someoneChoosing->hide();
}

/*void GamePage::updatePlayers()
{
	cpr::Response response = cpr::Get(cpr::Url{ "http://localHost:18080/currentPlayersInGame" });

}*/

void GamePage::createThread()
{
	QtConcurrent::run([this]() {updateChat(); });
	QtConcurrent::run([this]() {updateTable(); });
	QtConcurrent::run([this]() {checkStage(); });
}

void GamePage::updateChat()
{
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/chat/get" },
		cpr::Body{ "username=" + m_playerCurrent.GetName() });
	auto words = response.text;
	crow::json::rvalue messagesResponse = crow::json::load(words);

	auto count = messages->rowCount();
	if (count == messagesResponse.size())
		return;

	int position = 0;
	for (const auto& message : messagesResponse)
	{
		std::string content = message["Message"].s();
		std::string playerName = message["Name"].s();
		auto v = QString::fromUtf8(content.c_str());

		if (position >= count)
		{
			auto name = QString::fromUtf8(playerName.c_str());
			name += v;
			messages->appendRow(new QStandardItem(name));
		}
		position++;
	}
	ui.displayMessage->setModel(messages);
	//words is a 
	//if (words != "")
		//messages->coun(new QStandardItem(QString::fromUtf8(words.data(), int(words.size()))));

}

void GamePage::updateTable()
{
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/game/getPlayers" });
	crow::json::rvalue playerResponse = crow::json::load(response.text);
	QMutexLocker locker(&lineMutex);
	ui.tabelaScor->clearContents();
	int position = 0;
	for (const auto& person : playerResponse)
	{
		std::string name = person["name"].s();
		int score = person["score"].d();

		ui.tabelaScor->setItem(position, 0, new QTableWidgetItem(QString::fromUtf8(name.c_str())));
		ui.tabelaScor->setItem(position++, 1, new QTableWidgetItem(QString::number(score)));
	}

}

void GamePage::updateDrawing()
{
	QMutexLocker lineLocker(&lineMutex);

	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/round/getDrawing" });
	crow::json::rvalue drawingResponse = crow::json::load(response.text);
	int position = 0;
	auto node1 = drawingResponse[0];
	QColor currentColorNew = QColor::fromRgb(std::stoi(node1["red"].s()), std::stoi(node1["green"].s()), std::stoi(node1["blue"].s()));

	for (auto& node : drawingResponse)
	{
		if (node["idLine"].d() == g.GetSize())
		{
			position++;
			if (position > line.size())
			{
				Node* nodeNew = new Node(QPoint(node["coordinateX"].d(), node["coordinateY"].d()));
				line.push_back(nodeNew);
				update();
			}
		}
		else
			if (node["idLine"].d() > g.GetSize())
			{
				g.addNodes(std::make_pair(line, currentColorNew));
				line.clear();
				Node* nodeNew = new Node(QPoint(node["coordinateX"].d(), node["coordinateY"].d()));
				line.push_back(nodeNew);
				update();
			}
		currentColorNew = QColor::fromRgb(std::stoi(node["red"].s()), std::stoi(node["green"].s()), std::stoi(node["blue"].s()));
	}
}

void GamePage::checkStage()
{
	QMutexLocker lineLocker(&lineMutex);
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/stage" });
	crow::json::rvalue stageResponse = crow::json::load(response.text);
	if (stageResponse["stage"] == "lobby")
	{

	}
	if (stageResponse["stage"] == "choosing")
	{
		cpr::Response response1 = cpr::Get(cpr::Url{ "http://localhost:18080/stage/drawing" },
			cpr::Body{ "name=" + m_playerCurrent.GetName() });
		crow::json::rvalue username = crow::json::load(response1.text);
		if (username["name"] == m_playerCurrent.GetName())
		{
			isPainter = true;
		}
	}
	if (stageResponse["stage"] == "drawing")
	{
		cpr::Response response2 = cpr::Get(cpr::Url{ "http://localhost:18080/getWord" });
		crow::json::rvalue wordResponse = crow::json::load(response2.text);
		word = wordResponse["word"].s();
		//veilHide();
		updateDrawing();
	}
	if (stageResponse["stage"] == "results")
	{

	}
	if (stageResponse["stage"] == "finalresults")
	{

	}
}


GamePage::GamePage(QWidget* parent, Player player, bool leader)
	: QWidget(parent), m_playerCurrent{ player }, lobbyLeader{ leader }
{
	messages = new QStandardItemModel(this);
	ui.setupUi(this);
	m_players.push_back(player);
	isPainter = true;
	choiceMade = false;
	ui.timerLabel->setText("Time Left:");
	//m_player{};
	ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
	connect(ui.exitButton, &QPushButton::pressed, this, &GamePage::on_exitButton_pressed);
	setFixedSize(1000, 750);
	int rectangleWidth = this->size().width() / 2;
	int rectangleHeight = this->size().height() / 2;
	int x = (this->size().width() - rectangleWidth) / 2;
	int y = (this->size().height() - rectangleHeight) / 2;
	rectangle = new QRect();
	rectangle->setRect(x, y, rectangleWidth, rectangleHeight);
	connect(ui.sendButton, &QPushButton::pressed, this, &GamePage::sendMessage);
	setupTabela();
	setupChat();
	setupCulori();
	//word.SetWord("vlad");
	ui.horizontalLayoutWidget->hide();
	ui.someoneChoosing->hide();
	if (lobbyLeader == false)
	{
		ui.startButton->hide();
	}
	ui.startButton->move(rectangle->center().x() - ui.startButton->width() / 2, rectangle->center().y() - ui.startButton->height() / 2);
	ui.startButton->setText("Start!");
	ui.startButton->setFont(QFont("Arial", 40));
	QPalette paleta = ui.startButton->palette();
	paleta.setColor(QPalette::WindowText, Qt::white);
	ui.startButton->setPalette(paleta);
	ui.startButton->setStyleSheet(QString("#%1 { background-color: lightgreen; }").arg(ui.startButton->objectName()));
	ui.veil->setStyleSheet("background-color: black;");
	ui.veil->setFixedSize(rectangle->size());
	ui.veil->move(rectangle->topLeft());
	QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect;
	opacityEffect->setOpacity(0.5);
	ui.veil->setGraphicsEffect(opacityEffect);
	ui.wordLabel->move(rectangle->x() + rectangle->width() / 2, rectangle->y() - 50);
	ui.wordLabel->resize(ui.wordLabel->width() + 30,ui.wordLabel->height());
	ui.wordLabel->show();
	QTimer* timer = new QTimer(this);
	timer->start(1000);
	connect(timer, &QTimer::timeout, this, &GamePage::createThread);

	//connect(timer, &QTimer::timeout, this,&GamePage::updatePlayers);
	gameTimer = std::make_unique<QTimer>(this);
	ui.timerLabel->move(ui.tabelaScor->x() + 25, ui.tabelaScor->y() - 30);
	ui.timerLabel->resize(100, ui.timerLabel->height());

	connect(ui.exitCurrentGame, &QPushButton::clicked, this, &GamePage::on_exitCurrentGame_pressed);

	ui.resultTable->hide();
	/*std::unordered_map<std::string, int> results;
	results["Coco20"] = 100;
	results["Coco"] = 200;
	results["Fasole"] = 300;
	setupResultTable(results);*/
	//deleteResultTable();
}


void GamePage::on_exitButton_pressed()
{
	cpr::Response response = cpr::Put(cpr::Url{ "http://localhost:18080/game/removePlayer" },
		cpr::Body{ "username=" + m_playerCurrent.GetName() });
	QCoreApplication::quit();

}

GamePage::~GamePage()
{
	if (rectangle != nullptr)
		delete rectangle;

	cpr::Response response = cpr::Put(cpr::Url{ "http://localhost:18080/game/removePlayer" },
		cpr::Body{ "username=" + m_playerCurrent.GetName() }); //doar pentru butonul de exit default de la interfata 
	//delete messages;
	g.clear();

}



void GamePage::setupTabela()
{
	ui.tabelaScor->setWindowTitle("Tabela Scor");
	ui.tabelaScor->setGeometry(rectangle->x() - 220, rectangle->y(), 220, rectangle->height() / 2 + 80);

	ui.tabelaScor->setRowCount(8);
	ui.tabelaScor->setColumnCount(2);

	ui.tabelaScor->setHorizontalHeaderLabels(QStringList() << "Username" << "Scor");

	ui.tabelaScor->setStyleSheet("QTableWidget { background-color: lightblue; }"
		"QHeaderView::section { background-color: lightblue; }");
	ui.tabelaScor->verticalHeader()->setVisible(false);
	ui.tabelaScor->horizontalHeader()->setSectionsClickable(false);
	ui.tabelaScor->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void GamePage::setupChat()
{
	ui.verticalLayoutWidget->setGeometry(rectangle->x() + rectangle->width(), rectangle->y(), 200, rectangle->height());
	ui.displayMessage->setFixedSize(200, ui.verticalLayoutWidget->height() - ui.sendButton->height());
	ui.mesageBox->setFixedSize(200 - ui.sendButton->width(), ui.sendButton->height());
	ui.displayMessage->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void GamePage::setupCulori()
{
	ui.gridLayoutWidget->setGeometry(rectangle->bottomLeft().x(), rectangle->bottomLeft().y() + 50, ui.gridLayoutWidget->width(), ui.gridLayoutWidget->height());
	ui.black_button->setStyleSheet(QString("#%1 { background-color: black; }").arg(ui.black_button->objectName()));
	ui.blue_button->setStyleSheet(QString("#%1 { background-color: blue; }").arg(ui.blue_button->objectName()));
	ui.red_button->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.red_button->objectName()));
	ui.orange_button->setStyleSheet(QString("#%1 { background-color: orange; }").arg(ui.orange_button->objectName()));
	ui.pink_button->setStyleSheet(QString("#%1 { background-color: pink; }").arg(ui.pink_button->objectName()));
	ui.purple_button->setStyleSheet(QString("#%1 { background-color: purple; }").arg(ui.purple_button->objectName()));
	ui.green_button->setStyleSheet(QString("#%1 { background-color: green; }").arg(ui.green_button->objectName()));
	ui.gray_button->setStyleSheet(QString("#%1 { background-color: gray; }").arg(ui.gray_button->objectName()));
	ui.yellow_button->setStyleSheet(QString("#%1 { background-color: yellow; }").arg(ui.yellow_button->objectName()));
	ui.brown_button->setStyleSheet(QString("#%1 { background-color: brown; }").arg(ui.brown_button->objectName()));
	ui.white_button->setStyleSheet(QString("#%1 { background-color: white; }").arg(ui.white_button->objectName()));
}

void GamePage::wordChoosingSequence()
{
	QTimer* timer = new QTimer(this);
	timer->start(10000);
	connect(timer, &QTimer::timeout, this, [this, timer]() {ui.veil->hide();
	ui.someoneChoosing->hide();
	ui.horizontalLayoutWidget->hide();
	if (isPainter == true)
		canPaint = true;
	timer->stop();
	timer->deleteLater();
	if (choiceMade == false)
	{
		srand(time(0));
		int index = std::rand() % 3;
		auto res = cpr::Post(cpr::Url{ "http://localhost:18080/choosingWord" },
			cpr::Body{ "word=" + words[index]});
		//ui.wordLabel->setText(QString::fromUtf8(words[index].c_str()));
		seconds = 0;
		gameTimer->start(1000);
		connect(gameTimer.get(), &QTimer::timeout, this, &GamePage::updateTimer);
	} });

	if (isPainter == true)
	{
		ui.horizontalLayoutWidget->setGeometry(rectangle->x(), rectangle->y() + rectangle->width() / 2, rectangle->width(), ui.horizontalLayoutWidget->height());
		ui.word1Button->setText(QString::fromUtf8(words[0].c_str()));
		ui.word2Button->setText(QString::fromUtf8(words[1].c_str()));
		ui.word3Button->setText(QString::fromUtf8(words[2].c_str()));
		ui.horizontalLayoutWidget->show();

	}
	else
	{
		ui.someoneChoosing->show();
		ui.someoneChoosing->setText("Someone is choosing a word");
		ui.someoneChoosing->resize(260, 30);
		ui.someoneChoosing->setFont(QFont("Arial", 15));
		ui.someoneChoosing->move(rectangle->center().x() - 125, rectangle->center().y() - 15);
	}
}

void GamePage::randomWordsFromDB()
{
	std::string url = "http://localhost:18080/RandomWordsFromDB";
	cpr::Response response = cpr::Get(cpr::Url(url));
	std::array<std::string, 3> wordsServer;
	std::array<std::string, 3>::iterator it = wordsServer.begin();
	if (response.status_code == 200) {
		auto json = crow::json::load(response.text);
		if (json) {
			for (const auto& word : json["RandomWords"]) {

				*it = word.s();
				it++;
			}
		}
		else {

			std::cerr << "Failed to get words from the server." << std::endl;
		}
	}
	words = wordsServer;
}

void GamePage::updateTimer()
{
	ui.timerLabel->setText("Time left : " + QString::number(60 - seconds));
	seconds++;
	if (seconds == 60)
		gameTimer->stop();
	ui.wordLabel->setText(QString::fromUtf8(word.c_str()));
}

void GamePage::setLobbyLeader(bool este)
{
	lobbyLeader = este;
}

void sendDrawing(int x, int y, bool painting, int red, int green, int blue) {
	auto response = cpr::Post(cpr::Url{ "http://localhost:18080/round/sendDrawing" },
		cpr::Body{ "coordinateX=" + std::to_string(x)
		+ "&coordinateY=" + std::to_string(y) +
		"&painting=" + boolToString(painting) +
		"&red=" + std::to_string(red) +
		"&green=" + std::to_string(green) +
		"&blue=" + std::to_string(blue) });
}
void GamePage::mousePressEvent(QMouseEvent* e)
{
	if (canPaint == true)
	{
		if (e->button() == Qt::RightButton)
		{
			painting = true;
			bool node = true;
			QMutexLocker locker(&lineMutex);
			if (rectangle->contains(e->pos()) == false)
			{
				node = false;
			}
			if (node == true)
			{
				QtConcurrent::run(sendDrawing, e->pos().x(), e->pos().y(), painting, 0, 0, 0);
				Node* curent = new Node(e->pos());
				line.push_back(curent);
				update();
			}

		}
	}
}

void GamePage::mouseMoveEvent(QMouseEvent* e)
{
	if ((e->buttons() && Qt::RightButton) && painting)
	{
		//verificare puncte 

		QMutexLocker locker(&lineMutex);
		if (rectangle->contains(e->pos()))
		{
			QtConcurrent::run(sendDrawing, e->pos().x(), e->pos().y(), painting, 0, 0, 0);

			Node* curent = new Node(e->pos());
			line.push_back(curent);
			update();
		}
	}
}

void GamePage::mouseReleaseEvent(QMouseEvent* e)
{
	if (e->button() == Qt::RightButton)
	{
		QMutexLocker locker(&lineMutex);
		if (rectangle->contains(e->pos()))
		{
			int red = currentColor.red();
			int blue = currentColor.blue();
			int green = currentColor.green();
			painting = false;
			QtConcurrent::run(sendDrawing, e->pos().x(), e->pos().y(), painting, red, green, blue);
			Node* curent = new Node(e->pos());
			line.push_back(curent);
			//transmitere desen server;
			g.addNodes(std::make_pair(line, currentColor));
			line.clear();
			update();
		}

	}
}

void GamePage::setupResultTable(const std::unordered_map<std::string, int>& results)
{
	// Convert the unordered_map items to a vector of std::pair
	std::vector<std::pair<std::string, int>> resultVector(results.begin(), results.end());

	if (std::ranges::is_sorted(resultVector, {}, [](const auto& pair) { return pair.second; }))
	{
		// Sort the vector based on the second part of each pair (the score)
		std::sort(resultVector.begin(), resultVector.end(), [](const auto& a, const auto& b) {
			return a.second > b.second; // Sorting in descending order by score
			});
	}

	// Show the veil
	ui.veil->show();

	// Set up the result table
	int tableWidth = 220;
	int tableHeight = rectangle->height() / 2 + 80;
	int tableX = rectangle->x() + (rectangle->width() - tableWidth) / 2;
	int tableY = rectangle->y() + (rectangle->height() - tableHeight) / 2;

	ui.resultTable->setWindowTitle("Rezultat");
	ui.resultTable->setGeometry(tableX, tableY, tableWidth, tableHeight);

	ui.resultTable->setRowCount(8);
	ui.resultTable->setColumnCount(2);

	ui.resultTable->setHorizontalHeaderLabels(QStringList() << "Username" << "Scor");

	ui.resultTable->setStyleSheet("QTableWidget { background-color: lightblue; }"
		"QHeaderView::section { background-color: lightblue; }");
	ui.resultTable->verticalHeader()->setVisible(false);
	ui.resultTable->horizontalHeader()->setSectionsClickable(false);
	ui.resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	// Populate the table with sorted results
	int row = 0;
	for (const auto& result : resultVector)
	{
		QString username = QString::fromUtf8(result.first.c_str());
		int score = result.second;

		QTableWidgetItem* usernameItem = new QTableWidgetItem(username);
		QTableWidgetItem* scoreItem = new QTableWidgetItem(QString::number(score));

		ui.resultTable->setItem(row, 0, usernameItem);
		ui.resultTable->setItem(row, 1, scoreItem);

		++row;
	}

	// Show the result table
	ui.resultTable->show();
}

void GamePage::deleteResultTable()
{
	// Delete items in the result table
	for (int row = 0; row < ui.resultTable->rowCount(); ++row)
	{
		for (int col = 0; col < ui.resultTable->columnCount(); ++col)
		{
			QTableWidgetItem* item = ui.resultTable->item(row, col);
			delete item;
		}
	}

	// Clear the table
	ui.resultTable->clearContents();
	ui.resultTable->setRowCount(0);
	ui.resultTable->setColumnCount(0);

	// Hide the result table
	ui.resultTable->hide();
}


void GamePage::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.fillRect(*rectangle, QBrush(Qt::white));
	painter.drawRect(*rectangle);
	std::vector<QPoint> positionsLine;
	painter.setPen(QPen(currentColor, 5, Qt::SolidLine));
	for (auto i : line)
	{
		positionsLine.push_back(i->getPosition());
	}
	if (positionsLine.size() > 0)
	{
		painter.drawPolyline(positionsLine.data(), positionsLine.size());
	}
	vector<std::pair<vector<Node*>, QColor>> nodes = g.getNodes();
	for (std::pair<vector<Node*>, QColor> i : nodes)
	{
		std::vector<QPoint> positions;
		painter.setPen(QPen(i.second, 5, Qt::SolidLine));
		for (auto j : i.first)
		{
			positions.push_back(j->getPosition());
		}
		if (positions.size() > 0)
		{
			painter.drawPolyline(positions.data(), positions.size());
		}
	}
}