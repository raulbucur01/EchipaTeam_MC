#include <iostream>
#include "SkribblServer.h"
#include "DataBase.h"

int main() {
	DataBase DB("SkribblData.sqlite");
	DB.printAllPLayers();
	DB.printAllWords();
	auto p = DB.searchPlayerInDB("Coco20");
	if (p == std::nullopt)
		std::cout << "Nu a fost gasit!";
	else
		std::cout << "A fost gasit";

	auto p2 = DB.searchPlayerInDB("asdfg");
	if (p2 == std::nullopt)
		std::cout << "Nu a fost gasit!";
	else
		std::cout << "A fost gasit";


	//ScribbleServer server;
	//server.Start(DB);

	return 0;
}