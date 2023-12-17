#include "GamePage.h"
#include <QScreen>
#include<QPainter>

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

void GamePage::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.fillRect(rectangle,QBrush(Qt::white));
    painter.drawRect(rectangle);
    vector<Node*> nodes = g.getNodes();
    QPen pen;
    for (Node* n : nodes)
    {
        QRect r(n->getPosition().x() - 10, n->getPosition().y() - 10, 20, 20);
        painter.fillRect(r, QBrush(Qt::black));
        painter.drawEllipse(r);
        pen.setBrush(Qt::black);

    }
}
