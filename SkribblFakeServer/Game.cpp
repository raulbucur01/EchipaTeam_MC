#include "Game.h"
using namespace skribbl;

skribbl::Game::Game(DataBase& dB, crow::SimpleApp&app):
	m_dB {std::move(dB)},m_app{app}
{
}

DataBase& skribbl::Game::gameStart()
{
	verifStartPressed();

	for (int i = 0; i < 4; i++)
	{
		GameRound* round = new GameRound(m_dB,m_app);
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
