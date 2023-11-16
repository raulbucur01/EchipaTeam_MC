#pragma once
#include <string>

class Player
{
public:
	Player() = default;
	Player(const std::string& name, const std::string& password);

	// getters
	std::string getName() const;
	int16_t getScore() const;
	int16_t getSecondsGuess() const;
	bool GetPainter();

	void setName(const std::string& name);
	void setScore(int16_t score);
	void setSecondsGuess(int16_t seconds);
	void setPainter(bool este);

	Player& operator=(const Player& other);
	bool operator==(const Player& p) const;

	
	

private:
	int m_id;
	std::string m_name;
	std::string m_password;
	int16_t m_score = 0, m_secondsGuess = 0;
	bool m_painter = false;
};

