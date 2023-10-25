#pragma once
#include <vector>
#include <string>

// clasa asta o stergem dupa ce implementeaza Leo clasa Player
class Player {
private:
	std::string m_name;
public:
	Player(std::string name="") {
		m_name = name;
	}

	void setName(std::string name) {
		m_name = name;
	}

	std::string getName() {
		return m_name;
	}
};

// Clasa asta e un model de pastrare a datelor, va fi inclocuita cu o baza de date
class PlayerRepo
{
private:
	std::vector<Player> players;
public:
	PlayerRepo() = default;
	// Operatii CRUD:
	// Create (add)
	void create(Player p);
	// Update 
	void update(Player p, Player new_p);
	//
	~PlayerRepo() = default;
};

