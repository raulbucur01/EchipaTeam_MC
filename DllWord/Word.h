#pragma once

#include "pch.h"

#ifdef MYDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif

class Word
{
public:
	Word() = default;
	Word(int id, const std::string& word = "");

	// setters
	void setWord(std::string word);
	void setId(int id);

	// logic
	// returneaza starea curenta a sloturilor de litere
	std::string getCurrentSlotState();
	// inlocuieste random un slot nedezvaluit cu litera de la acelasi index din cuvant
	void revealOneRandomLetter();
	// returneaza un string cu atatea sloturi cate litere are cuvantul
	std::string getEmptyLetterSlots();
	void resetSlots();
	//printeaza cuvintele maxim partial
	void printPartialWord();

	// operators
	bool operator==(const Word& other) const;
	Word& operator=(const Word& other);

private:
	int m_id;
	std::string m_word;
	std::string m_slots;
	std::vector<int> m_unrevealedIndexes;
};
