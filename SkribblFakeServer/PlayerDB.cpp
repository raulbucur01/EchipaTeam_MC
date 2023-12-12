#include "PlayerDB.h"

using namespace http;

PlayerDB::PlayerDB(const std::string& filename) : m_playerDB(createPlayerStorage(filename))
{
	m_playerDB.sync_schema();
	auto initPlayersCount = m_playerDB.count<Player>();
	if (initPlayersCount == 0)
		populatePlayerDB(m_playerDB);

	addPlayersFromDBToPlayersVector();
}

auto PlayerDB::getPlayerIterator(const std::string& name)
{
	for (auto it = m_players.begin(); it != m_players.end(); it++)
	{
		if (it->GetName() == name)
			return it;
	}
	return m_players.end();
}

void PlayerDB::addPlayer(Player& player)
{
	if (getPlayerIterator(player.GetName()) == m_players.end()) {
		auto id = m_playerDB.insert(player);
		player.SetId(id);
		m_players.push_back(player);
	}
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
		m_playerDB.remove<Player>(it->GetId());

		m_players.erase(it);
	}
}

bool PlayerDB::searchPlayer(const std::string& name) const
{
	for (auto& player : m_players)
	{
		if (player.GetName() == name)
			return true;
	}
	return false;
}

Player PlayerDB::getPlayer(const std::string& name)
{
	for (auto& player : m_players)
	{
		if (player.GetName() == name)
			return player;
	}
	return Player();
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

void PlayerDB::printAllPLayers()
{
	std::cout << std::endl;
	for (int i = 0; i < m_players.size(); i++)
	{
		std::cout << m_players[i] << "\n";
	}
}

void populatePlayerDB(PlayerStorage& storage)
{
	std::vector<Player> players = {
		Player{-1,"Coco20", "amuitato", 0},
		Player{-1,"raul807", "parolasmechera", 0},
		Player{-1,"ronaldoGOAT_CR7", "amuitato2", 0},
		Player{-1,"vlad", "parolacomplexa", 0},
	};
	storage.insert_range(players.begin(), players.end());
}

//LoginHandler::LoginHandler(PlayerDB& storage):m_db{storage}
//{
//}
//
//crow::response LoginHandler::operator()(const crow::request& req) const
//{
//	auto bodyArgs = parseUrlArgs(req.body);
//	auto end = bodyArgs.end();
//	auto usernameIter = bodyArgs.find("Name");
//	auto passwordIter = bodyArgs.find("Password");
//	if (usernameIter != end && passwordIter != end)
//	{
//		if (m_db.searchPlayer(usernameIter->second)==true)
//		{
//			if (m_db.getPlayer(usernameIter->second).GetPassword() == passwordIter->second)
//			{
//				return crow::response(200, "Login successful");
//			}
//			else
//			{
//				return crow::response(401, "Password incorrect.Try again");
//			}
//		}
//		else
//		{
//			return crow::response(404, "Username not found");
//		}
//	}
//	else
//	{
//		return crow::response(400);
//	}
//}
//
//RegistrationHandler::RegistrationHandler(PlayerDB& storage):m_db{storage}
//{
//}
//
//crow::response RegistrationHandler::operator()(const crow::request& req) const
//{
//	auto bodyArgs = parseUrlArgs(req.body);
//	auto end = bodyArgs.end();
//	auto usernameIter = bodyArgs.find("username");
//	auto passwordIter = bodyArgs.find("password");
//
//	if (usernameIter == end || passwordIter == end)
//	{
//		return crow::response(400);
//	}
//	if (m_db.searchPlayer(usernameIter->second))
//	{
//		return crow::response(403, "Username already exists");
//	}
//	//adaugare user in database
//	// 
//	//verificare daca s a adaugat cu succes usernameul
//
//	return crow::response(201, "Successfully registration");
//}
