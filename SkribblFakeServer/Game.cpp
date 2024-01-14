#include "Game.h"
#include <ctime>

using namespace skribbl;

skribbl::Game::Game(DataBase& dB):
	m_dB {std::move(dB)}
{
	srand(time(0));
	m_gameID = std::rand() % 100000;
}

DataBase& skribbl::Game::gameStart()
{
	verifStartPressed();

	for (int i = 0; i < 4; i++)
	{
		GameRound* round = new GameRound(m_dB);
		m_dB = round->roundStart();
		delete round;
	}

	//trebuie adaugat scorul in baza de date
	return std::ref(m_dB);
}

void skribbl::Game::verifStartPressed()
{
	//aici ar trebui sa verificam daca butonul start a fost apasat
	//si nu ar trebui sa lase programul sa continue pana nu este apasat;
}

int skribbl::Game::GetGameId()
{
	return m_gameID;
}
