#pragma once
#include "pch.h"

#ifdef MYDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif
class Player {
public:
	Player() = default;
	Player(int id, const std::string& name, const std::string& password, int score, std::istream& stream);

	// getters
	int getId() const;
	std::string getName() const;
	std::string getPassword() const;
	int16_t getScore() const;
	int16_t getSecondsGuess() const;
	bool getPainter();
	std::istream& getStream() const;

	// setters
	void setId(int id);
	void setName(const std::string& name);
	void setPassword(const std::string& password);
	void setScore(int16_t score);
	void setSecondsGuess(int16_t seconds);
	void setPainter(bool este);

	// operators
	Player& operator=(const Player& other);
	bool operator==(const Player& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Player& player);

private:
	int m_id;
	std::string m_name;
	std::string m_password;
	int16_t m_score = 0, m_secondsGuess = 0;
	std::istream& m_streamPlayer;
	bool m_painter = false;

};