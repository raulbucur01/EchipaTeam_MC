module round;
using skribbl::Round;

Round::Round(std::unordered_map<std::string, Player*> players) :
	m_players{ std::move(players) }
{
	m_secondsPassed = 0;
	g.clear();
	line.clear();
	std::unordered_map<std::string, Player*>::iterator it = m_players.begin();
	m_painter = std::make_unique<Player>(*(it->second));
	while (it != m_players.end())
	{
		it++;
		m_restOfPlayers.push_back(std::make_unique<Player>(*(it->second)));
	}
}

//const skribbl::Graph& skribbl::Round::GetGraph() const
//{
//	return g;
//}

