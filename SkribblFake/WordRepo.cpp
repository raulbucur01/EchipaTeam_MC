#include "WordRepo.h"

WordRepo::WordRepo(const std::vector<Word>& words)
{
    m_words = words;
}

void WordRepo::add(const Word& w)
{
	m_words.push_back(w);
}

void WordRepo::del(const Word& w)
{
    for (auto it = m_words.begin(); it != m_words.end(); ) {
        if (it->getWord() == w.getWord()) {
            it = m_words.erase(it);
        }
        else {
            ++it;
        }
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

WordRepo::~WordRepo()
{
}
