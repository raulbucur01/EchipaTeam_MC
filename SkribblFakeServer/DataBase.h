#pragma once

#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include <crow.h>
#include "Player.h"
#include "Word.h"
#include <fstream>
namespace sql = sqlite_orm;
import utils;

static auto createStorage(const std::string& filename) {
	return sql::make_storage(
		filename,
		sql::make_table("Player",
			sql::make_column("id", &Player::SetId, &Player::GetId, sql::primary_key().autoincrement()),
			sql::make_column("Name", &Player::SetName, &Player::GetName),
			sql::make_column("Password", &Player::SetPassword, &Player::GetPassword),
			sql::make_column("Score", &Player::SetScore, &Player::GetScore)
		),
		sql::make_table("Word",
			sql::make_column("id", &Word::SetId, &Word::GetId, sql::primary_key().autoincrement()),
			sql::make_column("word", &Word::SetWord, &Word::GetWord)
		)
	);
}

using Storage = decltype(createStorage(""));

void populateDB(Storage& storage);

class DataBase
{
public:
	DataBase() = default;
	DataBase(const std::string& filename);

	// Player
	void addPlayer(Player& p);
	void deletePlayer(const std::string& name);
	bool searchPlayer(const std::string& name) const;
	Player getPlayer(const std::string& name);
	auto getPlayerIterator(const std::string& name);
	void updatePlayer(const std::string& name, const Player& new_player);
	
	void addPlayersFromDBToPlayersVector();
	std::vector<Player> getAllPlayers();
	void printAllPLayers();

	// Word
	void addWord(Word& p);
	void deleteWord(const std::string& word);
	//bool searchWord(const std::string& name) const;
	//Word getWord(const std::string& name);
	auto getWordIterator(const std::string& word);
	void updateWord(const std::string& word, const Word& new_word);

	void addWordsFromDBToWordsVector();
	std::vector<Word> getAllWords();
	void printAllWords();

	// For direct DB interaction:
	// for Player
	std::optional<Player> searchPlayerInDB(const std::string& name);
	void AddPlayertoDB(Player& player);

	~DataBase() = default;

private:
	Storage m_DB;
	std::vector<Player> m_players;
	std::vector<Word> m_words;
};

class LoginHandler {
public:
	LoginHandler(DataBase& storage);
	crow::response operator()(const crow::request& req)const;

private:
	DataBase& m_DB;
};

class RegistrationHandler {
public:
	RegistrationHandler(DataBase& storage);
	crow::response operator()(const crow::request& req)const;
private:
	DataBase& m_DB;
};