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
        bool node = true;
        if (rectangle.contains(e->pos()) == false)
        {
            node = false;
        }
        if (node == true)
        {
            g.addNode(e->pos());
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
            g.addNode(e->pos());
            update();
        }
    }
}

void GamePage::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::RightButton)
    {
        painting = false;
    }
}

void GamePage::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.fillRect(rectangle,QBrush(Qt::white));
    painter.drawRect(rectangle);
    vector<Node*> nodes = g.getNodes();
    QPen pen;
    for (Node* n : nodes)
    {
        QRect r(n->getPosition().x(), n->getPosition().y(), 5, 5);
        painter.fillRect(r, QBrush(Qt::black));
        painter.drawEllipse(r);
        pen.setBrush(Qt::black);
    }
    std::vector<QPoint> positions;
    for (auto i : nodes)
    {
        positions.push_back(i->getPosition());
    }
    if (nodes.size() > 0)
    {
        painter.drawPolyline(positions.data(), positions.size());
    }
}