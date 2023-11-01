#include "Word.h"

Word::Word(std::string word)
	: m_word(word)
{
	m_slots = getEmptyLetterSlots();
}

std::string Word::getWord()
{
	return m_word;
}

std::string Word::getCurrentSlotState()
{
	return m_slots;
}

void Word::revealOneRandomLetter()
{
	std::vector<int> unrevealedIndexes;
	for (int i = 0; i < m_slots.length(); i++)
	{
		unrevealedIndexes.push_back(i);
	}

	//if (unrevealedIndexes.empty())
	//{
	//	return m_slots;
	//}

	int randomIndex = 1 + (rand() % m_word.length());
	//if (randomIndex < 0 || randomIndex > m_word.length())
	//	return m_slots;

	m_slots[randomIndex] = m_word[randomIndex];
	//return m_slots;
}

std::string Word::getEmptyLetterSlots()
{
	std::string letterSlots = "";
	for (int i = 0; i < m_word.length(); i++)
	{
		letterSlots += "_";
	}
	return letterSlots;
}

void Word::resetSlots()
{
	m_slots = getEmptyLetterSlots();
}
