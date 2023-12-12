#include <iostream>
#include "SkribblServer.h"
#include "DataBase.h"

int main() {
	DataBase DB("SkribblData.sqlite");
	DB.printAllPLayers();
	DB.printAllWords();

	//ScribbleServer server;
	//server.Start(DB);

	return 0;
}