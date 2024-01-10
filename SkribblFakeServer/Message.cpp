#include "Message.h"

Message::Message(std::string content, std::string playerName): m_content{content},m_playerName{playerName}
{
}

std::string Message::GetContent() const
{
    return m_content;
}

std::string Message::GetPlayerName() const
{
    return m_playerName;
}

void Message::SetContet(std::string content)
{
    m_content = content;
}

void Message::SetPlayerName(std::string playerName)
{
    m_playerName = playerName;
}
