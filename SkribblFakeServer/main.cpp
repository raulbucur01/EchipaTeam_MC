#include <iostream>
#include "SkribblServer.h"

using namespace skribbl;


int main() {
	DataBase DB("SkribblData.sqlite");
	//DB.printAllPLayers();
	//DB.GetAllPurchases();
	//DB.PrintAllPurchases();
	/*std::vector<Purchase> playerPurchases = DB.GetPurchasesByPlayer("Coco20");
	std::cout << "\n";
	for (auto purchase : playerPurchases) {
		std::cout << "\n";
		std::cout << purchase.GetId() << " " << purchase.GetPlayerName() << " " << purchase.GetIconId();
	}*/

	//DB.UpdatePlayerCoinsInDB("Coco20", 150);
	/*DB.printAllPLayers();

	DB.PrintAllObtainedScores();
	DB.UpdatePlayerScoreInDB("Coco20", 300);*/

	SkribblServer server(DB);
	server.Start();
	return 0;
}