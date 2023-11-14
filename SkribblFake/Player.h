#pragma once
#include<iostream>
#include <string>
#include "Word.h"

class Player
{
public:
	Player() = default;
	Player(const std::string& name, const std::string& password, std::istream& stream);

	std::string getName() const;
	void setName(const std::string& name);

	int16_t getScore() const;
	std::istream& getStream() const;
	void setScore(int16_t score);
	void setSecondsGuess(int16_t seconds);
	int16_t getSecondsGuess() const;
	
	bool operator ==(const Player& p);
	Player& operator=(const Player& other);
	
	void PositioningBegin();
	bool GetPainter();
	void setPainter(bool este);

private:
	std::string m_name;
	std::string m_password;
	int16_t m_score = 0, m_secondsGuess = 0;
	std::istream& m_streamPlayer;
	bool m_painter = false;
};

