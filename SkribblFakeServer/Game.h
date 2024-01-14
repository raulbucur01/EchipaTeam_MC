#pragma once
#include "GameRound.h"

namespace skribbl
{
	class Game
	{
	public:
		Game(DataBase& dB);

		DataBase& gameStart();
		void verifStartPressed();
		int GetGameId();

	private:
		DataBase m_dB;
		int m_gameID;
	};
}

