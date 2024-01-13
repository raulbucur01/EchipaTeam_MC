#include<unordered_map>
#include "Player.h"
#include "graph.h"
#include <memory>

export module round;

namespace skribbl
{
	export class Round
	{
	public:
		Round(std::unordered_map<std::string, Player*> players);

	private:
		Graph g;
		std::vector<Node*>line;
		std::unordered_map<std::string, Player*> m_players;
		std::unordered_map<std::string, int> m_pointsAcumulated;
		int m_secondsPassed;
		std::unique_ptr<Player> m_painter;
		std::vector< std::unique_ptr<Player>> m_restOfPlayers;
	};
}