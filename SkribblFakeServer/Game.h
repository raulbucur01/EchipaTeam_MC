#pragma once
#include "GameRound.h"
namespace skribbl
{
	class Game
	{
	public:
		Game(DataBase& dB, crow::SimpleApp& app);

		DataBase& gameStart();
		void verifStartPressed();
		int GetGameId();

	private:
		DataBase m_dB;
		crow::SimpleApp& m_app;
		int m_gameID;

	};
}

