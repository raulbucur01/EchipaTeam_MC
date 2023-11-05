#pragma once
#include<iostream>
#include <string>
#include "Word.h"

class Player
{
public:
	Player(const std::string& name,std::istream& stream);
	std::string GetName() const;
	int16_t GetScore() const;
	std::istream& GetStream() const;
	void SetScore(int16_t score);
	void SetName(const std::string& name);
	void SetSecondsGuess(int16_t seconds);
	int16_t GetSecondsGuess() const;
	bool operator ==(const Player& p);
	Player& operator=(const Player& other);

private:
	std::string m_name;
	int16_t m_score = 0,m_secondsGuess=0;
	std::istream& m_streamPlayer;
};

