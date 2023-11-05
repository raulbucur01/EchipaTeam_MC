#include "PlayerRepo.h"
#include "PlayerService.h"
#include "Word.h"
#include <iostream>
#include"GameLogic.h"
#include<fstream>

// revert
int main() {
	/*// PlayerRepo test
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
	ps.printPlayers();*/

	// Word class test
	Word word("casa de marcat");

	/*std::cout << word.getCurrentSlotState() << std::endl;
	word.revealOneRandomLetter();
	std::cout << word.getCurrentSlotState() << std::endl;
	word.revealOneRandomLetter();
	std::cout << word.getCurrentSlotState() << std::endl;
	word.revealOneRandomLetter();
	std::cout << word.getCurrentSlotState() << std::endl;
	word.revealOneRandomLetter();
	std::cout << word.getCurrentSlotState() << std::endl;
	word.revealOneRandomLetter();
	std::cout << word.getCurrentSlotState() << std::endl;*/
	PlayerRepo p;
	std::ifstream citire("fisier.in");
	p.add(Player("Vlad", citire));
	GameLogic round(p);
	round.TimePassing(word);
	citire.close();
	return 0;
}