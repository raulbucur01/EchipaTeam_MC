#pragma once
#include <string>
#include <iostream>
class Purchase
{
public:
    Purchase() = default;

    Purchase(int id, const std::string& playerName, int iconId)
        : m_id(id), m_playerName(playerName), m_iconId(iconId) {}

    // Getter for ID
    int GetId() const;

    // Setter for ID
    void SetId(int id);

    // Getter for playerName
    const std::string& GetPlayerName() const;

    // Setter for playerName
    void SetPlayerName(const std::string& playerName);

    // Getter for iconId
    int GetIconId() const;

    // Setter for iconId
    void SetIconId(int iconId);

    friend std::ostream& operator<<(std::ostream& os, const Purchase& purchase);

private:
    int m_id;
    std::string m_playerName;
    int m_iconId;
};

