#include <iostream>
#include "SkribblServer.h"

using namespace skribbl;

int main() {
	DataBase DB("SkribblData.sqlite");
	
	////DB.PrintAll<Word>();
	//DB.printAllWords();

	//DB.UpdatePlayerCoinsInDB("Coco20", 150);
	/*DB.printAllPLayers();

	DB.PrintAllObtainedScores();
	DB.UpdatePlayerScoreInDB("Coco20", 300);*/

	SkribblServer server(DB);
	server.Start();
	return 0;
}