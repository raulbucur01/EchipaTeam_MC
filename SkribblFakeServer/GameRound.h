#pragma once
#include<unordered_map>
#include "DataBase.h"
#include <memory>


namespace skribbl
{
	class GameRound
	{
public:
	GameRound(DataBase dB);
	//const Graph& GetGraph() const;

	void roundStart();
	void verifChoice();
	void chooseOneRandomWord();
	void roundTimer();
	void verifGuess();
	void computeScore();
	int swapPainter(int index);

private:
	DataBase m_dB;
	std::unordered_map<std::string, int16_t> m_pointsAcumulated;
	std::unordered_map<std::string, int> m_secondsForGuess;
	int m_secondsPassed;
	std::unique_ptr<Player> m_painter;
	std::vector< std::unique_ptr<Player>> m_restOfPlayers;
	Word word;
	};
}

