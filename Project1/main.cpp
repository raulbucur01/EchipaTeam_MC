#include "PlayerRepo.h"
#include "PlayerService.h"
// revert
int main() {
	// PlayerRepo test
	PlayerRepo p;
	p.add(Player("Raul"));
	p.add(Player("Vlad"));
	p.add(Player("Leo"));
	p.add(Player("Cristi"));
	p.printAll();
	p.update(Player("Raul"), Player("RaulBucur"));
	p.update(Player("Leo"), Player("Leonard"));
	p.printAll();
	p.del("Leo");
	p.printAll();

	// Player service test
	PlayerService ps(p);
	ps.addPlayer("Ceorce");
	ps.addPlayer("Burebista");
	ps.printPlayers();
	ps.updatePlayer("Burebista", "AndreiBurebista");
	ps.printPlayers();
	ps.deletePlayer("Ceorce");
	ps.printPlayers();
	ps.deletePlayer("Ceorce");
	ps.printPlayers();
	return 0;
}