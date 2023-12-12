#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include <crow.h>
#include "Player.h"
namespace sql = sqlite_orm;

import utils;

static auto createPlayerStorage(const std::string& filename) {
	return sql::make_storage(
		filename,
		sql::make_table("Player",
		sql::make_column("id", &Player::SetId, &Player::GetId, sql::primary_key().autoincrement()),
		sql::make_column("Name", &Player::SetName, &Player::GetName),
		sql::make_column("Password", &Player::SetPassword, &Player::GetPassword),
		sql::make_column("Score", &Player::SetScore, &Player::GetScore)
		)
	);
}

using PlayerStorage = decltype(createPlayerStorage(""));

void populatePlayerDB(PlayerStorage& storage);


class PlayerDB
{
public:
	PlayerDB() = default;
	PlayerDB(const std::string& filename);
	
	void addPlayer(Player& p);
	void deletePlayer(const std::string& name);
	bool searchPlayer(const std::string& name) const;
	Player getPlayer(const std::string& name);
	auto getPlayerIterator(const std::string & name);
	void updatePlayer(const std::string& name, const Player& new_player);
	void addPlayersFromDBToPlayersVector();
	std::vector<Player> getAllPlayers();
	void printAllPLayers();
private:
	PlayerStorage m_playerDB;
	// probabil mai eficient cu unordered_map la m_players modific daca trebuie
	std::vector<Player> m_players;

};
//class LoginHandler {
//public:
//	LoginHandler(PlayerDB& storage);
//	crow::response operator()(const crow::request& req)const;
//
//private:
//	PlayerDB& m_db;
//};
//class RegistrationHandler {
//public:
//	RegistrationHandler(PlayerDB& storage);
//	crow::response operator()(const crow::request& req)const;
//private:
//	PlayerDB& m_db;
//};

