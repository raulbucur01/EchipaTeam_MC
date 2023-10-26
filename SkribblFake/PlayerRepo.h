#pragma once
#include <vector>
#include <string>
#include "Player.h"

// clasa asta o stergem dupa ce implementeaza Leo clasa Player
//class Player {
//private:
//	std::string m_name;
//public:
//	Player(std::string name = "") {
//		m_name = name;
//	}
//
//	void setName(std::string name) {
//		m_name = name;
//	}
//
//	std::string getName() {
//		return m_name;
//	}
//
//	bool operator==(Player& p) {
//		return m_name == p.getName();
//	}
// 
//	/*Player& operator=(Player& other) {
//		if (this != &other) { 
//			m_name = other.getName();
//		}
//		return *this;
//
//	}*/
//};

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


