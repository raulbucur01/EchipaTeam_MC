#include "Word.h"
#include <time.h>
Word::Word(int id, const std::string& word):
	m_id{ id },
	m_word{ word }
{
	m_slots = GetEmptyLetterSlots();

	for (int i = 0; i < m_slots.length(); i++)
	{
		if (m_slots[i] == '-')
			m_unrevealedIndexes.push_back(i);
	}
}

std::string Word::GetWord() const
{
	return m_word;
}

int Word::GetId() const
{
	return m_id;
}

void Word::SetWord(std::string word)
{
	m_word = word;
}

void Word::SetId(int id)
{
	m_id = id;
}

std::string Word::GetCurrentSlotState()
{
	return m_slots;
}

void Word::RevealOneRandomLetter()
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

std::string Word::GetEmptyLetterSlots()
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

int Word::GetSize()
{
	return static_cast<int>(m_word.size());
}

int Word::GetSizeUnrevealedWord()
{
	return static_cast<int>(m_unrevealedIndexes.size());
}

void Word::ResetSlots()
{
	m_slots = GetEmptyLetterSlots();
}

std::ostream& operator<<(std::ostream& os, const Word& word)
{
	os << "ID: " << word.GetId() << ", "
		<< "Word: " << word.GetWord();

	return os;
}
