#pragma once
#include "Word.h"
#include <vector>
#include <string>

class WordRepo {

private:
	std::vector<Word> m_words;

public:
	WordRepo();
	void add(Word w); 
	void del(Word w); //stergere
	void update(Word oldWord, Word newWord);
	bool operator ==(const Word& w);
	Word& operator=(const Word& other);
	~WordRepo();

};