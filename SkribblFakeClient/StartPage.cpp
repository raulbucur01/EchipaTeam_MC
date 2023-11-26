#include "StartPage.h"
#include <QDesktopWidget>

StartPage::StartPage(QWidget* parent)
	: QMainWindow(parent), loginPage(nullptr)
{
	ui.setupUi(this);
	this->setStyleSheet("QMainWindow {background: 'lightblue';}");
    QDesktopWidget* desktop = QApplication::desktop();
    this->resize(desktop.size());
    QPixmap bkgnd("/cutepuppy.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
	connect(ui.pushButton_START, &QPushButton::pressed, this, &StartPage::on_pushButton_Start_pressed);
    ui.pushButton_START->setStyleSheet(QString("#%1 { background-color: lightgreen; }").arg(ui.pushButton_START->objectName()));
    ui.pushButton_START->move(this->size().width()/2,this->size().height()/2);
}

StartPage::~StartPage()
{
}

void StartPage::on_pushButton_Start_pressed() {
	ui.pushButton_START->hide();
    LoginPage* loginPage = new LoginPage(this); // Assuming MainWindow is the parent
    loginPage->show();
}