#include <iostream>
#include "SkribblServer.h"
#include "DataBase.h"

int main() {
	DataBase DB("SkribblData.sqlite");
	//DB.printAllPLayers();
	/*DB.printAllPLayers();
	DB.printAllWords();
	auto p = DB.searchPlayerInDB("Coco20");
	if (p == std::nullopt)
		std::cout << "\nNu a fost gasit!";
	else
	{
		if (p.has_value()) {
			std::cout << "\nA fost gasit: " << p.value().GetName();
		}
	}

	auto p2 = DB.searchPlayerInDB("asdfg");
	if (p2 == std::nullopt)
		std::cout << "\nNu a fost gasit!";
	else
		std::cout << "\nA fost gasit";
*/
	SkribblServer server;
	server.Start(DB);
	return 0;
}