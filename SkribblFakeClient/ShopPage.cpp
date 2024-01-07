#include "ShopPage.h"

ShopPage::ShopPage(QWidget *parent, Player player)
	: QWidget(parent)
{
	ui.setupUi(this);
	QPixmap pix1("C:/MY_CODE/GitHubRepos/EchipaTeam_MC/SkribblFakeClient/Icons/Siren.jpeg");
	QIcon icon1(pix1);

    // Set the icon on the button
    ui.pushButton_Icon1->setIcon(icon1);

    // Set the size of the icon to cover the entire button
    QSize iconSize1(ui.pushButton_Icon1->size());
    ui.pushButton_Icon1->setIconSize(iconSize1);

    QPixmap pix2("C:/MY_CODE/GitHubRepos/EchipaTeam_MC/SkribblFakeClient/Icons/Gladiator.jpeg");
    QIcon icon2(pix2);

    // Set the icon on the button
    ui.pushButton_Icon2->setIcon(icon2);

    // Set the size of the icon to cover the entire button
    QSize iconSize2(ui.pushButton_Icon2->size());
    ui.pushButton_Icon2->setIconSize(iconSize2);

    QPixmap pix3("C:/MY_CODE/GitHubRepos/EchipaTeam_MC/SkribblFakeClient/Icons/Pig.jpeg");
    QIcon icon3(pix3);

    // Set the icon on the button
    ui.pushButton_Icon3->setIcon(icon3);

    // Set the size of the icon to cover the entire button
    QSize iconSize3(ui.pushButton_Icon3->size());
    ui.pushButton_Icon3->setIconSize(iconSize3);

    QPixmap pix4("C:/MY_CODE/GitHubRepos/EchipaTeam_MC/SkribblFakeClient/Icons/Wizard.jpeg");
    QIcon icon4(pix4);

    // Set the icon on the button
    ui.pushButton_Icon4->setIcon(icon4);

    // Set the size of the icon to cover the entire button
    QSize iconSize4(ui.pushButton_Icon4->size());
    ui.pushButton_Icon4->setIconSize(iconSize4);
}

ShopPage::~ShopPage()
{}
