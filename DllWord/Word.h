#pragma once
#include "pch.h"
//
//#ifdef MYDLL_EXPORTS
//#define __declspec(dllexport)
//#else
//#define __declspec(dllimport)
//#endif

class __declspec(dllexport) Word
{
public:
	Word() = default;
	Word(int id, const std::string& word = "");

	// setters
	void SetWord(std::string word);
	void SetId(int id);

	//getters
	std::string GetWord() const noexcept;
	int GetId() const noexcept;

	// logic
	std::string getCurrentSlotState();
	void revealOneRandomLetter();
	std::string getEmptyLetterSlots();
	void resetSlots();
	std::string getEmptyLetterSlots(char* word);
	std::string revealRandomLetters(int numToReveal, char* word);
	void printPartialWord();

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
