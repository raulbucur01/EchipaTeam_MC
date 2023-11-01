#pragma once
#include <string>
#include <vector>
// Raul
class Word
{
private:
	std::string m_word;
	std::string m_slots;

public:
	Word(std::string word = "");
	// returneaza cuvantul
	std::string getWord();
	// returneaza starea curenta a sloturilor de litere
	std::string getCurrentSlotState();
	// inlocuieste random un slot cu litera de la acelasi index din cuvant
	void revealOneRandomLetter();
	// returneaza un string cu atatea sloturi cate litere are cuvantul
	std::string getEmptyLetterSlots();
	
	void resetSlots();
};

