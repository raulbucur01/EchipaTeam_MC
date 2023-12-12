#pragma once

#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include <crow.h>
#include "Player.h"
#include "Word.h"
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
};

