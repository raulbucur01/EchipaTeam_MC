#include "WordRepo.h"

WordRepo::WordRepo(const std::vector<Word>& words) :
	m_words(words)
{
}

void WordRepo::add(Word w)
{
}

void WordRepo::del(Word w)
{
}

void WordRepo::update(Word oldWord, Word newWord)
{
}

bool WordRepo::operator==(const Word& w)
{
	return false;
}

Word& WordRepo::operator=(const Word& other)
{
	// TODO: insert return statement here
}

WordRepo::~WordRepo()
{
}
