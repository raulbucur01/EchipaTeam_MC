#pragma once
#include <string>
#include <vector>
#include <iostream>

class Word
{
public:
	Word() = default;
	Word(int id, const std::string& word = "");

	// getters
	std::string GetWord() const;
	int GetId() const;
	
	// setters
	void SetWord(std::string word);
	void SetId(int id);

	// logic
	// returneaza starea curenta a sloturilor de litere
	std::string GetCurrentSlotState();
	// inlocuieste random un slot nedezvaluit cu litera de la acelasi index din cuvant
	void RevealOneRandomLetter();
	// returneaza un string cu atatea sloturi cate litere are cuvantul
	std::string GetEmptyLetterSlots();
	//returneaza lungimea cuvantului
	int GetSize();
	int GetSizeUnrevealedWord();
	void ResetSlots();

	// operators
	bool operator==(const Word& other) const;
	Word& operator=(const Word& other);
	friend std::ostream& operator<<(std::ostream& os, const Word& word);

private:
	int m_id;
	std::string m_word;
	std::string m_slots;
	std::vector<int> m_unrevealedIndexes;
};

