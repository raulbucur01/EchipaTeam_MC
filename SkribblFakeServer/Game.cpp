#include "Game.h"
#include <ctime>

using namespace skribbl;

skribbl::Game::Game()
{
	int m_CurentStageIndex = 0;
	m_stage.push_back(Stage::Lobby);
}

void skribbl::Game::setStages(int playerNumber)
{
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < playerNumber; i++)
		{
			m_stage.push_back(Stage::Choosing);
			m_stage.push_back(Stage::Drawing);
			m_stage.push_back(Stage::Results);
		}
	}
	m_stage.push_back(Stage::FinalResults);
}

void skribbl::Game::incrementIndex()
{
	m_CurentStageIndex++;
	m_verification.clear();
}

Stage skribbl::Game::getCurrentStage()
{
	return m_stage[m_CurentStageIndex];
}

void skribbl::Game::setPlayers(std::unordered_map<std::string, Player>& players)
{
	m_players = players;
}

void skribbl::Game::setQueue()
{
	for (auto player : m_players)
	{
		m_painter.push(player.first);
	}
}

std::unordered_map<std::string, Player> skribbl::Game::GetPlayers()
{
	return m_players;
}



std::string skribbl::Game::getWhoPaints()
{
	return m_painter.front();
}

void skribbl::Game::incrementPainter()
{
	std::string username = m_painter.front();
	m_painter.pop();
	m_painter.push(username);
}

bool skribbl::Game::verifyPlayer(std::string name)
{
	if (std::find(m_verification.begin(), m_verification.end(), name) != m_verification.end())
	{
		return true;
	}
	else
	{
		m_verification.insert(name);
		return false;
	}
}

std::unordered_set<std::string> skribbl::Game::VerifyPlayers()
{
	return m_verification;
}

Word skribbl::Game::GetWord()
{
	return m_word;
}

void skribbl::Game::setWord(const Word& word)
{
	m_word = word;
}

