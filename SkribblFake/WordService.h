#pragma once
#include "WordRepo.h"

class WordService
{
private:
	WordRepo m_wordRepo;
public:
	WordService() = default;
	WordService(WordRepo& wordRepo);
	void addWord(std::string word);
	void updateWord(std::string oldWord, std::string newWord);
	void deleteWord(std::string word);
	void printWords();
};

