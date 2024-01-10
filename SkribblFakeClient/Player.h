#pragma once
#include <string>
#include <iostream>

class Player
{
public:
	Player() = default;
	Player(int id, const std::string& name, const std::string& password, int16_t score, int16_t coins, int16_t currentIconId);

	// getters
	int GetId() const;
	std::string GetName() const;
	std::string GetPassword() const;
	int16_t GetScore() const;
	int16_t GetCoins() const;
	int16_t GetCurrentIconId() const;
	int16_t GetSecondsGuess() const;
	bool GetPainter();

	// setters
	void SetId(int id);
	void SetName(const std::string& name);
	void SetPassword(const std::string& password);
	void SetScore(int16_t score);
	void SetCoins(int16_t coins);
	void SetCurrentIconId(int16_t iconId);
	void SetSecondsGuess(int16_t seconds);
	void SetPainter(bool este);

	// operators
	Player& operator=(const Player& other);
	bool operator==(const Player& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Player& player);

private:
	int m_id;
	std::string m_name;
	std::string m_password;
	
	int16_t m_score, m_coins, m_currentIconID, m_secondsGuess = 0;
	bool m_painter = false;
};