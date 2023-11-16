#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "Player.h"
namespace sql = sqlite_orm;

static auto createPlayerStorage(const std::string& filename) {
	return sql::make_storage(
		filename,
		sql::make_table(
			"Player",
			sql::make_column("id", &Player::setId, &Player::getId, sql::autoincrement(), sql::primary_key()),
			sql::make_column("Name", &Player::setName, &Player::getName),
			sql::make_column("Password", &Player::setPassword, &Player::getPassword),
			sql::make_column("Score", &Player::setScore, &Player::getScore)
		)
	);
}

using Storage = decltype(createPlayerStorage(""));

void populatePlayerDB(Storage& storage);

class PlayerDB
{
public:
	PlayerDB() = default;
	PlayerDB(const std::string& filename);

	void addPlayer(const Player& p);
	void deletePlayer(const std::string& name);
	bool searchPlayer(const std::string& name) const;
	void updatePlayer(const std::string& name, const Player& new_player);
	std::vector<Player> getAllPlayers();

private:
	Storage m_playerDB;
};

