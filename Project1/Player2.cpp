#include "Player2.h"

Player::Player(const std::string& name)
    :m_name { name }
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

int16_t Player::SetScore(int16_t score)
{
     m_score = score;
}

std::string Player::SetName(const std::string& name)
{
    m_name = name;
}

bool Player::operator==(Player& p)
{
    return m_name == p.GetName();
}

Player& Player::operator=(Player& other)
{
    if (this != &other)
    {
    m_name = other.GetName();
    }
    return *this;
}

