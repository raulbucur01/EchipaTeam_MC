#pragma once
#include <string>
class Message
{
private:
	std::string m_content;
	std::string m_playerName;
public:
	Message(std::string content, std::string playerName);
	std::string GetContent() const ;
	std::string GetPlayerName() const;
	void SetContet();
	void SetPlayerName();


};

