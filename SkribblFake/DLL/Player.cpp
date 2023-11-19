#include "pch.h"
#include <iostream>
#include <istream>
#include <string>
#include "Player.h"

Player::Player(int id, const std::string& name, const std::string& password, int score, std::istream& stream)
	:m_id(id), m_name(name), m_password(password), m_score(score), m_streamPlayer(stream)
{
}

int Player::getId() const
{
	return m_id;
}

std::string Player::getName() const
{
	return m_name;
}

std::string Player::getPassword() const
{
	return m_password;
}

int16_t Player::getScore() const
{
	return m_score;
}

std::istream& Player::getStream() const
{
	return m_streamPlayer;
}

void Player::setScore(int16_t score)
{
	m_score = score;
}

void Player::setId(int id)
{
	m_id = id;
}

void Player::setName(const std::string& name)
{
	m_name = name;
}

void Player::setPassword(const std::string& password)
{
	m_password = password;
}

void Player::setSecondsGuess(int16_t seconds)
{
	m_secondsGuess = seconds;
}

int16_t Player::getSecondsGuess() const
{
	return m_secondsGuess;
}

Player& Player::operator=(const Player& other)
{
	if (this == &other) {
		return *this;
	}

	m_id = other.m_id;
	m_name = other.m_name;
	m_password = other.m_password;
	m_score = other.m_score;
	return *this;
}

bool Player::operator==(const Player& p) const
{
	return (m_id == p.m_id &&
		m_name == p.m_name &&
		m_password == p.m_password &&
		m_score == p.m_score);
}

bool Player::getPainter()
{
	return m_painter;
}

void Player::setPainter(bool este)
{
	m_painter = este;
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	os << "ID: " << player.m_id << ", "
		<< "Name: " << player.m_name << ", "
		<< "Password: " << player.m_password << ", "
		<< "Score: " << player.m_score;

	return os;
}


