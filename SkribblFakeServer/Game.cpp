#include "Game.h"
#include <ctime>

using namespace skribbl;

skribbl::Game::Game()
{
	int m_CurentStageIndex = 0;
}

void skribbl::Game::setStages(int playerNumber)
{
	m_stage.push_back(Stage::Lobby);
	for (int i = 0; i < playerNumber; i++)
	{
		m_stage.push_back(Stage::Choosing);
		m_stage.push_back(Stage::Drawing);
		m_stage.push_back(Stage::Results);
	}
	m_stage.push_back(Stage::FinalResults);
}

void skribbl::Game::incrementIndex()
{
	m_CurentStageIndex++;
}

Stage skribbl::Game::getCurrentStage()
{
	return m_stage[m_CurentStageIndex];
}

void skribbl::Game::setPlayers(std::unordered_map<std::string, Player>& players)
{
	m_players = std::move(players);
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

