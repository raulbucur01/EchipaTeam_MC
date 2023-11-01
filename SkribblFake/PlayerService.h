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
	void addPlayer(std::string name);
	void updatePlayer(std::string oldName, std::string newName);
	void deletePlayer(std::string name);
	void printPlayers();
};

