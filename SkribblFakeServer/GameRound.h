#pragma once
#include<unordered_map>
#include "DataBase.h"
#include <memory>
#include "crow.h"

namespace skribbl
{
	class GameRound
	{
public:
	GameRound(DataBase& dB, crow::SimpleApp&app);
	~GameRound();
	//const Graph& GetGraph() const;

	DataBase& roundStart();
	void verifChoice();
	void chooseThreeRandomWords();
	void chooseOneRandomWord();
	void roundTimer();
	bool verifGuess();
	void computeScore();
	int swapPainter(int index);
	void endOfRoundTimer();

private:
	DataBase m_dB;
	crow::SimpleApp& m_app;
	std::unordered_map<std::string, int16_t> m_pointsAcumulated;
	std::unordered_map<std::string, int> m_secondsForGuess;
	int m_secondsPassed;
	std::unique_ptr<Player> m_painter;
	std::vector< std::unique_ptr<Player>> m_restOfPlayers;
	Word m_word;
	std::vector<Word> m_wordChoice;
	
	
	};
}

