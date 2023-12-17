#include "pch.h"
#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <time.h>
#include "Word.h"


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

void Word::SetWord(std::string word)
{
	m_word = word;
}

void Word::SetId(int id)
{
	m_id = id;
}

std::string Word::GetWord()const noexcept
{
	return m_word;
}

int Word::GetId() const noexcept
{
	return m_id;
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

//friend std::ostream& Word::operator<<(std::ostream& os, const Word& word)
//{
//	os << "ID: " << word.GetId() << ", "
//		<< "Word: " << word.GetWord();
//
//	return os;
//}

void Word::resetSlots()
{
	m_slots = getEmptyLetterSlots();
}

void Word::printPartialWord()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	std::string partialWord;
	std::vector<std::string> partialWords;

	char* word = std::strtok(&m_word[0], " ");
	std::vector<std::string> words;

	while (word != nullptr)
	{
		int revealCount = 1 + rand() % (std::strlen(word) / 2); // Maxim jumatate de cuvant
		words.push_back(word);

		partialWord = revealRandomLetters(revealCount, word);
		//std::cout << partialWord << "";
		partialWords.push_back(partialWord);

		word = strtok(nullptr, " ");
	}

	for (const auto& partialword : partialWords)
	{
		std::cout << partialWord << " ";
	}
}