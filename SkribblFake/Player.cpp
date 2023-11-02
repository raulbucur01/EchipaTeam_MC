#include "Player.h"

Player::Player(const std::string& name)
	:m_name{ name }
{
}

std::string Player::GetName() const
{
	return m_name;
}

int16_t Player::GetScore() const
{
	return m_score;
}

void Player::SetScore(int16_t score)
{
	m_score = score;
}

void Player::SetName(const std::string& name)
{
	m_name = name;
}

bool Player::operator==(const Player& p)
{
	return m_name == p.GetName();
}

Player& Player::operator=(const Player& other)
{
	if (this == &other) {
		return *this;
	}

	m_name = other.m_name;
	m_score = other.m_score;
	return *this;
}


