#include "Word.h"
#include <time.h>
Word::Word(int id, const std::string& word)
	: m_id(id), m_word(word)
{
	m_slots = getEmptyLetterSlots();

	for (int i = 0; i < m_slots.length(); i++)
	{
		if (m_slots[i] == '-')
			m_unrevealedIndexes.push_back(i);
	}
}

std::string Word::getWord() const
{
	return m_word;
}

int Word::getId() const
{
	return m_id;
}

void Word::setWord(std::string word)
{
	m_word = word;
}

void Word::setId(int id)
{
	m_id = id;
}

std::string Word::getCurrentSlotState()
{
	return m_slots;
}

void Word::revealOneRandomLetter()
{
	int randomIndex;
	bool indexFound = false;

	srand(static_cast<unsigned int>(time(NULL)));
	randomIndex = rand() % m_unrevealedIndexes.size();

	//afisez litera dezvaluita 
	m_slots[m_unrevealedIndexes[randomIndex]] = m_word[m_unrevealedIndexes[randomIndex]];
	// sterg indexul literei dezvaluite 
	m_unrevealedIndexes.erase(m_unrevealedIndexes.begin() + randomIndex);


}

std::string Word::getEmptyLetterSlots()
{
	std::string letterSlots = "";
	for (size_t i = 0; i < m_word.length(); i++)
	{
		if (m_word[i] != ' ')
			letterSlots += "-";
		else
			letterSlots += " ";
	}
	return letterSlots;
}

bool Word::operator==(const Word& other) const
{
	return (m_id == other.m_id && m_word == other.m_word);
}

Word& Word::operator=(const Word& other)
{
	if (this == &other) {
		return *this;
	}

	m_id = other.m_id;
	m_word = other.m_word;
	return *this;
}

int Word::getSize()
{
	return static_cast<int>(m_word.size());
}

int Word::getSizeUnrevealedWord()
{
	return static_cast<int>(m_unrevealedIndexes.size());
}

void Word::resetSlots()
{
	m_slots = getEmptyLetterSlots();
}

