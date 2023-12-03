#include "StartPage.h"
#include <QScreen>

StartPage::StartPage(QWidget* parent)
	: QMainWindow(parent), loginPage(nullptr)
{
	ui.setupUi(this);
	this->setStyleSheet("QMainWindow {background: 'lightblue';}");
    QScreen* desktop = QApplication::primaryScreen();
    this->resize(desktop->size());
    QPixmap bkgnd("/cutepuppy.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    ui.pushButton_START->setStyleSheet(QString("#%1 { background-color: lightgreen; }").arg(ui.pushButton_START->objectName()));
    ui.pushButton_START->move((this->size().width()-ui.pushButton_START->size().width())/2,(this->size().height() - ui.pushButton_START->size().height())/2);
    connect(ui.pushButton_START, &QPushButton::pressed, this, &StartPage::on_pushButton_Start_pressed);
    ui.pushButton_START->setStyleSheet(QString("#%1 { background-color: red; }").arg(ui.pushButton_START->objectName()));
    ui.pushButton_START->move((this->size().width() - ui.pushButton_START->size().width()), this->size().height());
    connect(ui.exitButton, &QPushButton::pressed, this, &StartPage::on_exitButton_pressed);

}

StartPage::~StartPage()
{
}

void StartPage::on_exitButton_pressed()
{
    return;
}



void StartPage::on_pushButton_Start_pressed() {
	ui.pushButton_START->hide();
    delete ui.pushButton_START;
    LoginPage* loginPage = new LoginPage(this);
    loginPage->show();
}