#include "Player.h"

Player::Player(const std::string& name, const std::string& password, std::istream& stream)
	:m_name(name), m_password(password), m_streamPlayer(stream)
{

}

std::string Player::getName() const
{
	return m_name;
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

void Player::setName(const std::string& name)
{
	m_name = name;
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

	m_name = other.m_name;
	m_score = other.m_score;
	return *this;
}

bool Player::operator==(const Player& p) const
{
	return m_name == p.m_name;
}

void Player::PositioningBegin()
{
	m_streamPlayer.seekg(0, std::ios::beg);
}

bool Player::GetPainter()
{
	return m_painter;
}

void Player::setPainter(bool este)
{
	m_painter = este;
}


