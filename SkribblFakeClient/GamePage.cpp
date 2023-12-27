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
	ui.wordLabel->move(rectangle.x() + rectangle.width() / 2, rectangle.y() - 50);
	ui.wordLabel->setText("vlad");
	/*QTimer* timerChat = new QTimer(this);
	connect(timerChat, &QTimer::timeout, this, &GamePage::updateChat);
	timerChat->start(1000);  // 10 seconds interval
	*/
}

void GamePage::on_exitButton_pressed()
{
	QCoreApplication::quit();

}

GamePage::~GamePage()
{
	delete messages;
	g.clear();

}

void GamePage::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::RightButton)
	{
		painting = true;
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
		g.addNodes(std::make_pair(line,currentColor));
		line.clear();
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
	ui.tabelaScor->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void GamePage::setupChat()
{
	ui.verticalLayoutWidget->setGeometry(rectangle.x() + rectangle.width(), rectangle.y(), 200, rectangle.height());
	ui.displayMessage->setFixedSize( 200, ui.verticalLayoutWidget->height() - ui.sendButton->height());
	ui.mesageBox->setFixedSize( 200 - ui.sendButton->width(), ui.sendButton->height());
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
	vector<std::pair<vector<Node*>,QColor>> nodes = g.getNodes();
	for (std::pair<vector<Node*>,QColor> i : nodes)
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