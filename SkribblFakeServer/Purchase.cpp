#include "Purchase.h"

// Getter for ID
int Purchase::GetId() const {
    return m_id;
}

// Setter for ID
void Purchase::SetId(int id) {
    m_id = id;
}

// Getter for playerName
const std::string& Purchase::GetPlayerName() const {
    return m_playerName;
}

// Setter for playerName
void Purchase::SetPlayerName(const std::string& playerName) {
    m_playerName = playerName;
}

// Getter for iconId
int Purchase::GetIconId() const {
    return m_iconId;
}

// Setter for iconId
void Purchase::SetIconId(int iconId) {
    m_iconId = iconId;
}

std::ostream& operator<<(std::ostream& os, const Purchase& purchase)
{
    os << "Purchase ID: " << purchase.GetId() << ", Player Name: " << purchase.GetPlayerName()
        << ", Icon ID: " << purchase.GetIconId();
    return os;
}
