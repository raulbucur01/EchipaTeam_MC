#pragma once
#include <string>

class Player2
{
public:
	Player2(const std::string& name);
	std::string GetName() const;
	int16_t GetScore() const;
	int16_t SetScore(int16_t score);
	std::string SetName(const std::string& name);

private:
	std::string m_name;
	int16_t m_score;
};

