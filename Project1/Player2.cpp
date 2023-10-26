#include "Player2.h"

Player2::Player2(const std::string& name)
    :m_name { name }
{
}

std::string Player2::GetName() const
{
    return m_name;
}

