#pragma once
#include <string>

class Player
{
public:
	Player(const std::string& name);
	std::string GetName() const;
	int16_t GetScore() const;
	int16_t SetScore(int16_t score);
	std::string SetName(const std::string& name);
	bool operator ==(Player& p);
	Player& operator =(Player& other);

private:
	std::string m_name;
	int16_t m_score = 0;
};

