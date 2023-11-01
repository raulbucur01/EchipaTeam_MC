#include "Word.h"

Word::Word(std::string word)
	: m_word(word)
{
	m_slots = getEmptyLetterSlots();

	for (int i = 0; i < m_slots.length(); i++)
	{
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
	while (!indexFound && !m_unrevealedIndexes.empty()) {
		randomIndex = rand() % m_word.length();

		// vedem daca indexul e in lista de indexuri nedezvaluite
		auto it = std::find(m_unrevealedIndexes.begin(), m_unrevealedIndexes.end(), randomIndex);

		// daca se gaseste printre indexurile nedezvaluite marcam drept gasit si iesim din loop
		if (it != m_unrevealedIndexes.end()) {
			indexFound = true;
			m_unrevealedIndexes.erase(it); // scoatem indexul care urmeaza dezvaluit din lista de nedezvaluite
		}
	}

	if (indexFound) {
		m_slots[randomIndex] = m_word[randomIndex];
	}
}

std::string Word::getEmptyLetterSlots()
{
	std::string letterSlots = "";
	for (int i = 0; i < m_word.length(); i++)
	{
		letterSlots += "-";
	}
	return letterSlots;
}

void Word::resetSlots()
{
	m_slots = getEmptyLetterSlots();
}
