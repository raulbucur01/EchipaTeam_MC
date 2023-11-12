#pragma once
#include "pch.h"

#ifdef MYDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif
class Player {
private:
	std::string getName();
	int16_t getScore();
	std::istream& getStream();
	void setScore(int16_t score);
	void setName(const std::string& name);
	void setSecondsGuess(int16_t seconds);
	int16_t getSecondsGuess();
	//bool operator ==(const Player& p);
	//Player& operator=(const Player& other);
	Player(std::istream& streamPlayer);
public:
private:
	std::string m_name;
	std::string m_username;
	std::string m_password;
	int16_t m_score = 0, m_secondsGuess = 0;
	std::istream& m_streamPlayer;

};