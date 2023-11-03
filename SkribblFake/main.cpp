#include "PlayerRepo.h"
#include "PlayerService.h"
#include "Word.h"
#include <iostream>

#include<conio.h>
#include<ctime>

void afiseazaTimpul(Word word)
{
	clock_t start = clock();
	int seconds_passed = 0;
	int secunde_afisare = 30;
	while (seconds_passed != 60)
	{
		
		clock_t curent = clock();
		seconds_passed = (curent - start) / CLOCKS_PER_SEC;
		std::cout << "Trecerea secundelor: " << seconds_passed << "\r";
		if (seconds_passed == secunde_afisare && secunde_afisare<=55)
		{
			word.revealOneRandomLetter();
			std::cout <<std::endl<< word.getCurrentSlotState() <<std::endl;
			secunde_afisare += (30/(word.getSize()/2));
		}
	}
	std::cout << "Cuvantul este: " << word.getWord();
}

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
	Word word("Ronaldo");
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
	
	afiseazaTimpul(word);
	return 0;
}