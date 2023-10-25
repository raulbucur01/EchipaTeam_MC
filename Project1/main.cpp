// salut!
//buna Raul
#include "PlayerRepo.h"

int main() {
	// PlayerRepo test
	PlayerRepo p;
	p.add(Player("Raul"));
	p.add(Player("Vlad"));
	p.add(Player("Leo"));
	p.add(Player("Cristi"));
	p.printAll();
	p.update(Player("Raul"), Player("RaulBucur"));
	p.printAll();
	p.del("Leo");
	p.printAll();


	return 0;
}