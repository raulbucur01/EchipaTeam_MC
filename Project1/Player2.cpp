#include "Player2.h"

Player2::Player2(const std::string& name)
    :m_name { name }
{
}

std::string Player2::GetName() const
{
    return m_name;
}

int16_t Player2::GetScore() const
{
    return m_score;
}

int16_t Player2::SetScore(int16_t score)
{
     m_score = score;
}

std::string Player2::SetName(const std::string& name)
{
    m_name = name;
}

