#include <iostream>
#include "SkribblServer.h"
#include "DataBase.h"

using namespace skribbl;

int main() {
	skribbl::DataBase DB("SkribblData.sqlite");
	//DB.PrintAll<Player>();
	//DB.PrintAll<Purchase>();
	//DB.PrintAll<ObtainedScore>();
	////DB.PrintAll<Word>();
	//DB.printAllWords();

	//DB.UpdatePlayerCoinsInDB("Coco20", 150);
	/*DB.printAllPLayers();

	DB.PrintAllObtainedScores();
	DB.UpdatePlayerScoreInDB("Coco20", 300);*/

	SkribblServer server;
	server.Start(DB);
	return 0;
}