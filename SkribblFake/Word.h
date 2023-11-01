#pragma once
#include <string>
class Word
{
private:
	std::string m_word;

public:
	Word(std::string word = "");
	std::string getWord();
	std::string revealOneRandomLetter();
	std::string getLetterSlots();
};

