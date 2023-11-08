#pragma once
#include "Word.h"
#include <vector>
#include <string>

class WordRepo {

private:
	std::vector<Word> m_words;

public:
	WordRepo(const std::vector<Word>& words);
	void add(const Word& w);
	void del(const Word& w); //stergere
	void update(const Word& oldWord, const Word& newWord);
	bool operator ==(const Word& w);
	~WordRepo();

};

