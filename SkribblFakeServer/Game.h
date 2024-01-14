#pragma once
#include "GameRound.h"
namespace skribbl
{
	enum class Stage : uint16_t
	{
		Lobby,
		Choosing,
		Drawing,
		Results,
		FinalResults
	};

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

