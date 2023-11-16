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
			sql::make_column("id", )
		)
	)
}

class PlayerDB
{
};

