#include "WordDB.h"
#include "PlayerDB.h"
#include <iostream>

int main() {
	PlayerDB playerDB("Players.sqlite");
	WordDB wordDB("Words.sqlite");

	playerDB.printAllPLayers();

	wordDB.printAllWords();

	Word word(-1, "laptop de gaming");
	wordDB.addWord(word);
	wordDB.printAllWords();

	Word newWord(word.getId() + 100, "laptop gaming");
	wordDB.updateWord("laptop de gaming", newWord);
	wordDB.printAllWords();

	wordDB.deleteWord("laptop gaming");
	wordDB.printAllWords();
	return 0;
}