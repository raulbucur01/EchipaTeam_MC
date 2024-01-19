#include <iostream>
#include "SkribblServer.h"

using namespace skribbl;

int main() {
	DataBase DB("SkribblData.sqlite");

	SkribblServer server(DB);
	server.Start();
	return 0;
}