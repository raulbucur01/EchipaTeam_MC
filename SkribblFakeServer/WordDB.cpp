#include "WordDB.h"

WordDB::WordDB(const std::string& filename) : m_wordDB(createWordStorage(filename))
{
	m_wordDB.sync_schema();
	auto initWordsCount = m_wordDB.count<Word>();
	if (initWordsCount == 0)
		populateWordDB(m_wordDB);

	addWordsFromDBToWordsVector();
}

void WordDB::addWord(Word& word)
{
	auto id = m_wordDB.insert(word);
	word.setId(id);
	m_words.push_back(word);
}

void WordDB::deleteWord(const std::string& word)
{
	auto it = getWordIterator(word);
	if (it != m_words.end())
	{
		m_wordDB.remove<Word>(it->getId());

		m_words.erase(it);
	}
}

auto WordDB::getWordIterator(const std::string& word)
{
	for (auto it = m_words.begin(); it != m_words.end(); it++)
	{
		if (it->getWord() == word)
			return it;
	}
	return m_words.end();
}

void WordDB::updateWord(const std::string& word, const Word& new_word)
{
	auto it = getWordIterator(word);
	if (it != m_words.end())
	{
		*it = new_word;

		m_wordDB.update(new_word);
	}
}

void WordDB::addWordsFromDBToWordsVector()
{
	auto playerCount = m_wordDB.count<Word>();
	if (playerCount > 0)
	{
		auto players = m_wordDB.get_all<Word>();
		for (auto& player : players)
		{
			m_words.push_back(player);
		}
	}
}

std::vector<Word> WordDB::getAllWords()
{
	return m_words;
}

void populateWordDB(Storage& storage)
{
	std::vector<Word> words = {
		Word{-1,"casa de marcat"},
		Word{-1,"Ferrari"},
		Word{-1,"sternocleidomastiodian"},
		Word{-1,"Cristiano Ronaldo"},
		Word{-1,"fasole frecata"},
		Word{-1,"paine"},
		Word{-1,"insula"},
		Word{-1,"ceafa de porc"},
		Word{-1,"KFC"},
		Word{-1,"Formula 1"},
		Word{-1,"Varza"},
		Word{-1,"OK"},
		Word{-1,"branza stricata"},
		Word{-1,"lapte de bivol"},
		Word{-1,"carnat urias"},
		Word{-1,"desert"},
		Word{-1,"tort de ciocolata"},
		Word{-1,"masline negre"},
	};
	storage.insert_range(words.begin(), words.end());
}