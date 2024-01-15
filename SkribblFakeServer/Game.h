#pragma once
#include <queue>
#include <unordered_map>
#include "Player.h"
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
		Game();
		void setStages(int playerNumber);
		void incrementIndex();
		Stage getCurrentStage();
		void setPlayers(std::unordered_map<std::string, Player>& players);
		void setQueue();
		std::unordered_map<std::string,Player> GetPlayers();
		std::string getWhoPaints();
		void incrementPainter();

	private:
		std::vector<Stage> m_stage;
		int m_CurentStageIndex;
		std::unordered_map<std::string, Player> m_players;
		std::queue<std::string> m_painter;
	};
}

