#pragma once
#include <string>
import <iostream>;
#include <vector>
#include "Message.h"

namespace skribbl
{
	class Player
	{
	public:
		Player() = default;
		Player(int id, const std::string& name, const std::string& password, int16_t score, int16_t coins, int16_t currentIconId);
		Player( const Player& p);
		~Player();

		// getters
		int GetId() const;
		std::string GetName() const;
		std::string GetPassword() const;
		int16_t GetScore() const;
		int16_t GetCoins() const;
		int16_t GetCurrentIconId() const;
		std::vector<Message> GetMessages() const;

		// setters
		void SetId(int id);
		void SetName(const std::string& name);
		void SetPassword(const std::string& password);
		void SetScore(int16_t score);
		void SetCoins(int16_t coins);
		void SetCurrentIconId(int16_t iconId);

		// operators
		Player& operator=(const Player& other);
		bool operator==(const Player& other) const;
		friend std::ostream& operator<<(std::ostream& os, const Player& player);

		void AddMessage(Message message);

	private:
		int m_id;
		std::string m_name;
		std::string m_password;
		std::vector<Message> m_messages;
		int16_t m_score, m_coins, m_currentIconID;
	};
}

