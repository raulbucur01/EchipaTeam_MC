#include "GamePage.h"
#include <QScreen>
#include<QPainter>
#include<QMouseEvent>

GamePage::GamePage(QWidget *parent)
	: QWidget(parent)
{
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
}

void GamePage::on_exitButton_pressed()
{
	exit(0);
}

GamePage::~GamePage()
{}

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