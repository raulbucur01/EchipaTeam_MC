#include "pch.h"
#include <iostream>
#include <istream>
#include <string>
#include "Player.h"

std::string Player::getName()
{
	return m_name;
}

int16_t Player::getScore()
{
	return m_score;
}

std::istream& Player::getStream()
{
	return m_streamPlayer;
}

void Player::setScore(int16_t score)
{
	m_score = score;
}

void Player::setName(const std::string& name)
{
	m_name = name;
}

void Player::setSecondsGuess(int16_t seconds)
{
	m_secondsGuess = seconds;
}

int16_t Player::getSecondsGuess()
{
	return m_secondsGuess;
}

Player::Player(std::istream& streamPlayer)
	: m_streamPlayer(streamPlayer)  
{
	
}

//bool Player::operator==(const Player& p)
//{
//	return m_name == p.getName();
//}

//Player& Player::operator=(const Player& other)
//{
//	if (this == &other) {
//		return *this;
//	}
//
//	m_name = other.m_name;
//	m_score = other.m_score;
//	return *this;
//}


