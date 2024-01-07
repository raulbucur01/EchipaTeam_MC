#include "ShopPage.h"

ShopPage::ShopPage(QWidget *parent, Player player)
	: QWidget(parent)
{
	ui.setupUi(this);
	QPixmap pix("C:/MY_CODE/GitHubRepos/EchipaTeam_MC/SkribblFakeClient/Icons/Siren.jpeg");
	QIcon icon(pix);

    // Set the icon on the button
    ui.pushButton_Icon1->setIcon(icon);

    // Set the size of the icon to cover the entire button
    QSize iconSize(ui.pushButton_Icon1->size());
    ui.pushButton_Icon1->setIconSize(iconSize);
}

ShopPage::~ShopPage()
{}
