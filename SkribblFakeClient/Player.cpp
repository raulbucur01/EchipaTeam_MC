#include "Player.h"

Player::Player(int id, const std::string& name, const std::string& password, int16_t score = 0, int16_t coins = 0, int16_t currentIconId = 0) :
	m_id{ id },
	m_name{ name },
	m_password{ password },
	m_score{ score },
	m_coins{ coins },
	m_currentIconID{ currentIconId }
{

}

int Player::GetId() const
{
	return m_id;
}

std::string Player::GetName() const
{
	return m_name;
}

std::string Player::GetPassword() const
{
	return m_password;
}

int16_t Player::GetScore() const
{
	return m_score;
}

int16_t Player::GetCoins() const
{
	return m_coins;
}

int16_t Player::GetCurrentIconId() const
{
	return m_currentIconID;
}

void Player::SetScore(int16_t score)
{
	m_score = score;
}

void Player::SetCoins(int16_t coins)
{
	m_coins = coins;
}

void Player::SetCurrentIconId(int16_t iconId)
{
	m_currentIconID = iconId;
}

void Player::SetId(int id)
{
	m_id = id;
}

void Player::SetName(const std::string& name)
{
	m_name = name;
}

void Player::SetPassword(const std::string& password)
{
	m_password = password;
}

void Player::SetSecondsGuess(int16_t seconds)
{
	m_secondsGuess = seconds;
}

int16_t Player::GetSecondsGuess() const
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
	m_coins = other.m_coins;
	m_currentIconID = other.m_currentIconID;
	return *this;
}

bool Player::operator==(const Player& p) const
{
	return (m_id == p.m_id &&
		m_name == p.m_name &&
		m_password == p.m_password &&
		m_score == p.m_score &&
		m_coins == p.m_coins &&
		m_currentIconID == p.m_currentIconID);
}

bool Player::GetPainter()
{
	return m_painter;
}

void Player::SetPainter(bool este)
{
	m_painter = este;
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	os << "ID: " << player.m_id << ", "
		<< "Name: " << player.m_name << ", "
		<< "Password: " << player.m_password << ", "
		<< "Score: " << player.m_score << ", "
		<< "Coins: " << player.m_coins << ", "
		<< "CurrentIconId: " << player.m_currentIconID;

	return os;
}