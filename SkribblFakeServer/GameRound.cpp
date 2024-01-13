#include "GameRound.h"

using namespace skribbl;

skribbl::GameRound::GameRound(DataBase dB):
	m_dB { std::move(dB) }
{
	m_secondsPassed = 0;
	std::unordered_map<std::string, Player>::iterator it = m_dB.GetPlayersInGame().begin();
	m_painter = std::make_unique<Player>(it->second);
	while (it != m_dB.GetPlayersInGame().end())
	{
		it++;
		m_restOfPlayers.push_back(std::make_unique<Player>(it->second));
	}
}

void skribbl::GameRound::roundStart()
{
}

void skribbl::GameRound::verifChoice()
{
}

void skribbl::GameRound::chooseOneRandomWord()
{
}

void skribbl::GameRound::roundTimer()
{
}

void skribbl::GameRound::verifGuess()
{
}

void skribbl::GameRound::computeScore()
{
	int secAvg = 0;
	for (auto i : m_secondsForGuess)
	{
		secAvg += i.second;
	}
	secAvg = secAvg / m_secondsForGuess.size();
	if (secAvg != 0)
	{
		m_pointsAcumulated[m_painter->GetName()] = (60 - secAvg) * 100 / 60;
	}
	else
	{
		m_pointsAcumulated[m_painter->GetName()] = -100;
	}
	for (auto it = m_restOfPlayers.begin(); it != m_restOfPlayers.end(); it++)
	{
		if (m_secondsForGuess[it->get()->GetName()] != 0)
		{
			m_pointsAcumulated[it->get()->GetName()] = (60 - m_secondsForGuess[it->get()->GetName()]) * 100 / 30;
		}
		else
		{
			m_pointsAcumulated[it->get()->GetName()] = -100;
		}
	}

}

int skribbl::GameRound::swapPainter(int index)
{
	return 0;
}


