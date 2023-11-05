#include "Word.h"
#include <time.h>
Word::Word(std::string word)
	: m_word(word)
{
	m_slots = getEmptyLetterSlots();

	for (int i = 0; i < m_slots.length(); i++)
	{	
		if(m_slots[i]=='-')
			m_unrevealedIndexes.push_back(i);
	}
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
	int randomIndex;
	bool indexFound = false;
	
	srand(time(NULL));
	randomIndex = rand() % m_unrevealedIndexes.size();

	//afisez litera dezvaluita 
	m_slots[m_unrevealedIndexes[randomIndex]] = m_word[m_unrevealedIndexes[randomIndex]];
	// sterg indexul literii dezvaluite 
	m_unrevealedIndexes.erase(m_unrevealedIndexes.begin() + randomIndex);
	

}

std::string Word::getEmptyLetterSlots()
{
	std::string letterSlots = "";
	for (int i = 0; i < m_word.length(); i++)
	{
		if (m_word[i] != ' ')
			letterSlots += "-";
		else
			letterSlots += " ";
	}
	return letterSlots;
}

int Word::getSizeWord()
{
	return m_word.size();
}

int Word::getSizeUnrevealedWord()
{
	return m_unrevealedIndexes.size();
}

void Word::resetSlots()
{
	m_slots = getEmptyLetterSlots();
}

