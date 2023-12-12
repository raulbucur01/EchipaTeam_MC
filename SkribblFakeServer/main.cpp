#include <iostream>
#include "SkribblServer.h"
#include "DataBase.h"

int main() {
	DataBase DB("SkribblData.sqlite");

	ScribbleServer server;
	server.Start(DB);

	return 0;
}