#include <iostream>
#include "SkribblServer.h"

using namespace skribbl;

int main() {
	DataBase DB("SkribblData.sqlite");

	DB.UpdatePlayerCoinsInDB("Coco20", 150);

	SkribblServer server(DB);
	server.Start();
	return 0;
}