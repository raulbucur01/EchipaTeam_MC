#pragma once
#include "PlayerRepo.h"
#include <string>

class PlayerService
{
private:
	PlayerRepo m_playerRepo;
public:
	PlayerService() = default;
	PlayerService(PlayerRepo& playerRepo);
	void addPlayer(std::string name,std::istream& stream, std::string username, std::string password);
	void updatePlayer(std::string oldName, std::string newName,std::istream stream);
	void deletePlayer(std::string name);
	void printPlayers();
};



