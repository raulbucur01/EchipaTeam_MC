#include "PlayerService.h"

PlayerService::PlayerService(PlayerRepo& playerRepo)
{
	m_playerRepo = playerRepo;
}

void PlayerService::addPlayer(std::string name, std::istream& stream, std::string username, std::string password)
{
	// in service se construiesc obiectele cu informatiile de la user si se adauga la repo
	Player newPlayer(name, stream, username, password);
	m_playerRepo.add(newPlayer);
}

void PlayerService::updatePlayer(std::string oldName, std::string newName)
{
	std::vector<Player> players = m_playerRepo.getAll();
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].getName() == oldName) {
			players[i].setName(newName);
		}
	}
}

void PlayerService::deletePlayer(std::string name)
{
	std::vector<Player> players = m_playerRepo.getAll();
	for (int i = 0; i < players.size(); i++) {
		if (players[i].getName() == name)
			m_playerRepo.del(name);
	}
}

void PlayerService::printPlayers()
{
	m_playerRepo.printAll();
}

