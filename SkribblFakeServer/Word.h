#pragma once
#include <string>
#include <vector>

class Word
{
public:
	Word() = default;
	Word(int id, const std::string& word = "");
	// getters
	std::string getWord() const;
	int getId() const;
	
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
	//returneaza lungimea cuvantului
	int getSize();
	int getSizeUnrevealedWord();
	void resetSlots();

	// operators
	bool operator==(const Word& other) const;
	Word& operator=(const Word& other);

private:
	int m_id;
	std::string m_word;
	std::string m_slots;
	std::vector<int> m_unrevealedIndexes;
};

