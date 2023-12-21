#include "GamePage.h"
#include <QScreen>
#include<QPainter>
#include<QMouseEvent>
#include<QTableWidget>
#include<QHeaderView>
#include<QTableWidgetItem>
#include<QStringListModel>

void GamePage::sendMessage()
{
    QString message = "You: " + ui.mesageBox->toPlainText();
    if (!message.isEmpty())
    {
        messages->appendRow(new QStandardItem(message));
        ui.mesageBox->clear();
    }
    ui.displayMessage->setModel(messages);
}

GamePage::GamePage(QWidget *parent)
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
}

void GamePage::on_exitButton_pressed()
{
	exit(0);
}

GamePage::~GamePage()
{
    delete messages;
}

void GamePage::mousePressEvent(QMouseEvent * e)
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
    ui.tabelaScor->setGeometry(rectangle.x() - 217, rectangle.y(), 217, rectangle.height()/2+52);

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

void GamePage::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.fillRect(rectangle,QBrush(Qt::white));
    painter.drawRect(rectangle);
    std::vector<QPoint> positionsLine;
    painter.setPen(QPen(Qt::black, 5, Qt::SolidLine));
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
        painter.setPen(QPen(Qt::black, 5, Qt::SolidLine));
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