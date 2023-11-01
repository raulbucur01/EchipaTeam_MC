#include "Word.h"

Word::Word(std::string word)
	: m_word(word)
{
}

std::string Word::getWord()
{
	return m_word;
}
