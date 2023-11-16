#include "PlayerDB.h"

PlayerDB::PlayerDB(const std::string& filename) : m_playerDB(createPlayerStorage(filename))
{
	m_playerDB.sync_schema();
	auto initPlayersCount = m_playerDB.count<Player>();
	if (initPlayersCount == 0)
		populatePlayerDB(m_playerDB);
}

void populatePlayerDB(Storage& storage)
{
	std::vector<Player> players = {
		Player{-1,"Coco20", "amuitato", 0},
		Player{-1,"raul807", "parolasmechera", 0},
		Player{-1,"ronaldoGOAT_CR7", "amuitato2", 0},
		Player{-1,"vlad", "parolacomplexa", 0},
	};
	storage.insert_range(players.begin(), players.end());
}
