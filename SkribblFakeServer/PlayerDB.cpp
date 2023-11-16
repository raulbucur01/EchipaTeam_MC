#include "PlayerDB.h"

PlayerDB::PlayerDB(const std::string& filename) : m_playerDB(createPlayerStorage(filename))
{
	m_playerDB.sync_schema();
	auto initPlayersCount = m_playerDB.count<Player>();
	if (initPlayersCount == 0)
		populatePlayerDB(m_playerDB);

	addPlayersFromDBToPlayersVector();
}

void PlayerDB::addPlayer(Player& player)
{
	auto id = m_playerDB.insert(player);
	player.setId(id);
	m_players.push_back(player);
}

void PlayerDB::deletePlayer(const std::string& name)
{
	/*if (searchPlayer(name))
	{
		m_playerDB.remove<Player>(getPlayer(name).getId());
		m_players.erase(getPlayerIterator(name));
	}*/

	auto it = m_players.begin();
	it = getPlayerIterator(name);
	if (it != m_players.end())
	{
		m_playerDB.remove<Player>(it->getId());

		m_players.erase(it);
	}
}

//bool PlayerDB::searchPlayer(const std::string& name) const
//{
//	for (auto& player : m_players)
//	{
//		if (player.getName() == name)
//			return true;
//	}
//	return false;
//}

//Player PlayerDB::getPlayer(const std::string& name)
//{
//
//	for (auto& player : m_players)
//	{
//		if (player.getName() == name)
//			return player;
//	}
//	return Player();
//}

auto PlayerDB::getPlayerIterator(const std::string& name)
{
	for (auto it = m_players.begin(); it != m_players.end(); it++)
	{
		if (it->getName() == name)
			return it;
	}
	return m_players.end();
}

void PlayerDB::updatePlayer(const std::string& name, const Player& new_player)
{
	auto it = getPlayerIterator(name);
	if (it != m_players.end())
	{
		*it = new_player;

		m_playerDB.update(new_player);
	}
}

void PlayerDB::addPlayersFromDBToPlayersVector()
{
	auto playerCount = m_playerDB.count<Player>();
	if (playerCount > 0)
	{
		auto players = m_playerDB.get_all<Player>();
		for (auto& player : players)
		{
			m_players.push_back(player);
		}
	}
}

std::vector<Player> PlayerDB::getAllPlayers()
{
	return m_players;
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