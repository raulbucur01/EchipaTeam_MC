export module game;
import <unordered_map>;
import<string>;
export import round;

namespace skribbl
{
	class Player;

	export class Game
	{
		std::unordered_map<std::string, Player*> m_players;
	};
}