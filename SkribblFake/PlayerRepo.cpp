#include "PlayerRepo.h"
#include <iostream>

void PlayerRepo::add(Player p)
{
	m_players.push_back(p);
}

void PlayerRepo::update(Player oldP, Player newP)
{
	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players[i] == oldP)
			m_players[i].SetName(newP.GetName());
	}
}

void PlayerRepo::del(std::string name)
{
	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players[i].GetName() == name)
			m_players.erase(m_players.begin() + i);
	}
}

std::vector<Player> PlayerRepo::getAll()
{
	return m_players;
}

void PlayerRepo::printAll()
{
	std::cout << "\n";
	for (int i = 0; i < m_players.size(); i++)
	{
		std::cout << m_players[i].GetName() << " ";
	}
}
