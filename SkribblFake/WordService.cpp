#include "WordService.h"

WordService::WordService(WordRepo& wordRepo)
{
	m_wordRepo = wordRepo;
}

void WordService::addWord(std::string word)
{
	Word word(word);
	m_wordRepo.add(word);
}

void WordService::updateWord(std::string oldWord, std::string newWord)
{
	std::vector<Word> word = m_wordRepo.getAll();
	for (int i = 0; i < word.size(); i++)
	{
		if (word[i].getWord() == oldWord) {
			word[i].setWord(newWord);
		}
	}
}

void WordService::deleteWord(std::string word)
{
	std::vector<Word> words = m_wordRepo.getAll();
	for (int i = 0; i < words.size(); i++) {
		if (words[i].getWord() == word)
			m_wordRepo.del(word);
	}
}

void WordService::printWords()
{
	m_wordRepo.printAll();
}


