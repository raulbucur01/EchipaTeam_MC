#include "WordRepo.h"
#include <iostream>

WordRepo::WordRepo(const std::vector<Word>& words)
{
    m_words = words;
}

void WordRepo::add(const Word& w)
{
    m_words.push_back(w);
}

void WordRepo::del(std::string word)
{
    for (int i = 0; i < m_words.size(); i++)
    {
        if (m_words[i].getWord() == word)
            m_words.erase(m_words.begin() + i);
    }
}

void WordRepo::update(const Word& oldWord, const Word& newWord)
{
    for (auto& word : m_words) {
        if (word.getWord() == oldWord.getWord()) {
            word = newWord;
            break;
        }
    }
}

std::vector<Word> WordRepo::getAll()
{
    return m_words;
}

void WordRepo::printAll()
{
    std::cout << "\n";
    for (int i = 0; i < m_words.size(); i++)
    {
        std::cout << m_words[i].getWord() << " ";
    }
}

WordRepo::~WordRepo()
{
}
