#pragma once
#include <vector>
#include <string>
#include "Player.h"

// Clasa asta e un model de pastrare a datelor, va fi inclocuita cu o baza de date
class PlayerRepo
{
private:
	std::vector<Player> m_players;
public:
	PlayerRepo() = default;

	// Create (add)
	void add(Player p);

	// Update 
	void update(Player old_p, Player new_p);

	// Delete dupa nume
	void del(std::string name);

	std::vector<Player> getAll();

	void printAll();

	~PlayerRepo() = default;
};



