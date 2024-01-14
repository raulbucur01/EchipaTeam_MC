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

	private:
		DataBase m_dB;
	};
}

