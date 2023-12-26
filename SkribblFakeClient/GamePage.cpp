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
void GamePage::sendMessage()
{
	QString message = "You: " + ui.mesageBox->toPlainText();
	if (!message.isEmpty())
	{
		messages->appendRow(new QStandardItem(message));
		ui.mesageBox->clear();
	}
	ui.displayMessage->setModel(messages);
	std::string word=message.toUtf8().constData();

	/*auto res = cpr::Post(cpr::Url{"http://localhost:18080/send"},
		cpr::Body{ "word="+word});
	*/
}

void GamePage::on_black_button_pressed()
{
	currentColor = Qt::black;
}

void GamePage::on_blue_button_pressed()
{
	currentColor = Qt::blue;
}

/*void GamePage::updateChat()
{
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/get" });
	auto words = response.text;
	if (words != "")
		messages->appendRow(new QStandardItem(QString::fromUtf8(words.data(), int(words.size()))));


}
*/

GamePage::GamePage(QWidget* parent)
	: QWidget(parent)
{
	messages = new QStandardItemModel(this);
	ui.setupUi(this);
	ui.exitButton->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.exitButton->objectName()));
	connect(ui.exitButton, &QPushButton::pressed, this, &GamePage::on_exitButton_pressed);
	QScreen* desktop = QApplication::primaryScreen();
	this->resize(desktop->size());
	int rectangleWidth = this->size().width() / 2;
	int rectangleHeight = this->size().height() / 2;
	int x = (this->size().width() - rectangleWidth) / 2;
	int y = (this->size().height() - rectangleHeight) / 2;
	rectangle.setRect(x, y, rectangleWidth, rectangleHeight);
	connect(ui.sendButton, &QPushButton::pressed, this, &GamePage::sendMessage);
	setupTabela();
	setupChat();
	setupCulori();
	/*QTimer* timerChat = new QTimer(this);
	connect(timerChat, &QTimer::timeout, this, &GamePage::updateChat);
	timerChat->start(1000);  // 10 seconds interval
	*/
}

void GamePage::on_exitButton_pressed()
{
	exit(0);
}

GamePage::~GamePage()
{
	delete messages;
}

void GamePage::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::RightButton)
	{
		painting = true;
		line.clear();
		bool node = true;
		if (rectangle.contains(e->pos()) == false)
		{
			node = false;
		}
		if (node == true)
		{
			Node* curent = new Node(e->pos());
			line.push_back(curent);
			update();
		}

	}
}

void GamePage::mouseMoveEvent(QMouseEvent* e)
{
	if ((e->buttons() && Qt::RightButton) && painting)
	{
		if (rectangle.contains(e->pos()))
		{
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
		painting = false;
		g.addNodes(line);
		update();
	}
}

void GamePage::setupTabela()
{
	ui.tabelaScor->setWindowTitle("Tabela Scor");
	ui.tabelaScor->setGeometry(rectangle.x() - 217, rectangle.y(), 217, rectangle.height() / 2 + 52);

	ui.tabelaScor->setRowCount(8);
	ui.tabelaScor->setColumnCount(2);

	ui.tabelaScor->setHorizontalHeaderLabels(QStringList() << "Username" << "Scor");

	ui.tabelaScor->setStyleSheet("QTableWidget { background-color: lightblue; }"
		"QHeaderView::section { background-color: lightblue; }");
	ui.tabelaScor->verticalHeader()->setVisible(false);
	ui.tabelaScor->horizontalHeader()->setSectionsClickable(false);
}

void GamePage::setupChat()
{
	ui.verticalLayoutWidget->setGeometry(rectangle.x() + rectangle.width(), rectangle.y(), 200, rectangle.height());
	ui.displayMessage->setGeometry(ui.verticalLayoutWidget->x(), ui.verticalLayoutWidget->y(), 200, ui.verticalLayoutWidget->height() - ui.sendButton->height());
	ui.mesageBox->setGeometry(ui.verticalLayoutWidget->x() + ui.displayMessage->height(), ui.verticalLayoutWidget->y(), 200 - ui.sendButton->width(), ui.sendButton->height());
}

void GamePage::setupCulori()
{
	ui.gridLayoutWidget->setGeometry(rectangle.bottomLeft().x(), rectangle.bottomLeft().y() + 50,ui.gridLayoutWidget->width(),ui.gridLayoutWidget->height());
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

void GamePage::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.fillRect(rectangle, QBrush(Qt::white));
	painter.drawRect(rectangle);
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
	vector<vector<Node*>> nodes = g.getNodes();
	for (vector<Node*> i : nodes)
	{
		std::vector<QPoint> positions;
		painter.setPen(QPen(currentColor, 5, Qt::SolidLine));
		for (auto j : i)
		{
			positions.push_back(j->getPosition());
		}
		if (positions.size() > 0)
		{
			painter.drawPolyline(positions.data(), positions.size());
		}
	}
}