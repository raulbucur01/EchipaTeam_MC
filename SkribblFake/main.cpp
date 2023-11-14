#include "PlayerRepo.h"
#include "PlayerService.h"
#include "Word.h"
#include <iostream>
#include"GameLogic.h"
#include "WordRepo.h"
#include "WordService.h"
#include<fstream>

// revert
int main() {
	//// PlayerRepo test
	//PlayerRepo pr;
	//std::ifstream ifs("fisier.in");
	//Player p1("Raul", ifs, "wow", "wow");
	//pr.add(p1);
	//pr.add(Player("coco", ifs, "coco", "coco"));
	//pr.printAll();
	//Player p2("RAUL", ifs, "wow", "wow");
	//pr.update(p1, p2);
	//pr.printAll();
	//pr.del("coco");
	//pr.printAll();

	//// Player service test
	//PlayerService ps(pr);
	//ps.addPlayer("Ceorce",ifs, "haha", "haha");
	//ps.addPlayer("Burebista", ifs, "ahha", "AHAH");
	//ps.printPlayers();
	//ps.updatePlayer("Burebista", "AndreiBurebista");
	//ps.printPlayers();
	//ps.deletePlayer("Ceorce");
	//ps.printPlayers();
	//ps.deletePlayer("Ceorce");
	//ps.printPlayers();

	//// wordRepo test
	//WordRepo wr;
	//Word w1("casa de marcat");
	//Word w2("fcsb e steaua");
	//wr.add(w1);
	//wr.add(w2);
	//wr.printAll();
	//wr.del(w1.getWord());
	//wr.printAll();
	//wr.update(w2, w1);
	//wr.printAll();

	//// wordService test
	//WordService ws(wr);
	//ws.printWords();
	//ws.addWord("floare verde");
	//ws.addWord("buie mecali");
	//ws.printWords();
	//ws.updateWord("buie mecali", "Fii patron nu antrenor");
	//ws.printWords();
	//ws.deleteWord("buie mecali");
	//ws.printWords();


	// Word class test
	Word word("casa de marcat");

	/* std::cout << word.getCurrentSlotState() << std::endl;
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
	p.add(Player("Vlad", "parola", citire));
	GameLogic round(p);
	round.TimePassing(word);
	citire.close();
	return 0;
}