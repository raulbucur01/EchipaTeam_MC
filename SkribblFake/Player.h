#pragma once
#include <string>

class Player
{
public:
	Player(const std::string& name, const std::string& username, const std::string& password);
	std::string GetName() const;
	int16_t GetScore() const;
	void SetScore(int16_t score);
	void SetName(const std::string& name);
	bool operator ==(const Player& p);
	Player& operator=(const Player& other);

private:
	std::string m_username;
	std::string m_password;
	std::string m_name;
	int16_t m_score = 0;
};

