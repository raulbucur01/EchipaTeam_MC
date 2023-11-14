#pragma once
#include <string>
#pragma once
#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

class DataBase
{
private:
};

struct Player {
	int id;
	std::string name;
	std::string password;
};

struct Word {
	int id;
	std::string word;
};

inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Players",
			sql::make_column("id", &Player::id, sql::primary_key().autoincrement()),
			sql::make_column("name", &Player::name),
			sql::make_column("password", &Player::password)
		),
		sql::make_table(
			"Words",
			sql::make_column("id", &Word::id),
			sql::make_column("word", &Word::word)
		)
	);
}

using Storage = decltype(createStorage(""));


void populateStorage(Storage& storage);


