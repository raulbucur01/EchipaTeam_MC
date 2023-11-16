#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "Word.h"
namespace sql = sqlite_orm;

static auto createWordStorage(const std::string& filename) {
	return sql::make_storage(
		filename,
		sql::make_table(
			"Word",
			sql::make_column("id", &Word::setId, &Word::getId, sql::primary_key().autoincrement()),
			sql::make_column("word", &Word::setWord, &Word::getWord)
		)
	);
}

using WordStorage = decltype(createWordStorage(""));

void populateWordDB(WordStorage& storage);

class WordDB
{
public:
	WordDB() = default;
	WordDB(const std::string& filename);

	void addWord(Word& p);
	void deleteWord(const std::string& word);
	//bool searchWord(const std::string& name) const;
	//Word getWord(const std::string& name);
	auto getWordIterator(const std::string& word);
	void updateWord(const std::string& word, const Word& new_word);

	void addWordsFromDBToWordsVector();
	std::vector<Word> getAllWords();

private:
	WordStorage m_wordDB;
	// probabil mai eficient cu unordered_map la m_words modific daca trebuie
	std::vector<Word> m_words;
};

