#pragma once
#include <string>
#include <vector>
// Raul
class Word
{
private:
	std::string m_word;
	std::string m_slots;
	std::vector<int> m_unrevealedIndexes;

public:
	Word(std::string word = "");
	// returneaza cuvantul
	std::string getWord() const;
	// returneaza starea curenta a sloturilor de litere
	void setWord(std::string word);
	std::string getCurrentSlotState();
	// inlocuieste random un slot nedezvaluit cu litera de la acelasi index din cuvant
	void revealOneRandomLetter();
	// returneaza un string cu atatea sloturi cate litere are cuvantul
	std::string getEmptyLetterSlots();
	//returneaza lungimea cuvantului
	bool operator==(const Word& w) const;
	int getSize();
	void resetSlots();
};


