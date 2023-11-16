#pragma once
#include <string>

class Player
{
public:
	Player() = default;
	Player(int id, const std::string& name, const std::string& password, int score);

	// getters
	int getId() const;
	std::string getName() const;
	std::string getPassword() const;
	int16_t getScore() const;
	int16_t getSecondsGuess() const;
	bool getPainter();

	// setters
	void setId(int id);
	void setName(const std::string& name);
	void setPassword(const std::string& password);
	void setScore(int16_t score);
	void setSecondsGuess(int16_t seconds);
	void setPainter(bool este);

	// operators
	Player& operator=(const Player& other);
	bool operator==(const Player& other) const;

private:
	int m_id;
	std::string m_name;
	std::string m_password;
	int16_t m_score = 0, m_secondsGuess = 0;
	bool m_painter = false;
};

