#pragma once
#include "Word.h"
#include <vector>
#include <string>

class WordRepo {

private:
	std::vector<Word> m_words;

public:
	WordRepo() = default;
	WordRepo(const std::vector<Word>& words);
	void add(const Word& w);
	void del(std::string word); //stergere
	void update(const Word& oldWord, const Word& newWord);
	std::vector<Word> getAll();
	void printAll();
	~WordRepo();

};

