#include "DataBase.h"


using namespace http;

void populateDB(Storage& storage)
{
	std::vector<Player> players = {
		Player{-1,"Coco20", "amuitato", 0, 0},
		Player{-1,"raul807", "parolasmechera", 0, 0},
		Player{-1,"ronaldoGOAT_CR7", "amuitato2", 0, 0},
		Player{-1,"vlad", "parolacomplexa", 0, 0},
	};
	storage.insert_range(players.begin(), players.end());

	std::ifstream input("Words.txt");
	std::vector<Word> words;
	std::string word;
	while (std::getline(input, word)) {
		words.emplace_back(-1, word);
	}

	storage.insert_range(words.begin(), words.end());
	input.close();
}

DataBase::DataBase(const std::string& filename) : m_DB(createStorage(filename))
{
	m_DB.sync_schema();
	// daca se mai adauga cuvinte trebuie decomentat ca sa se strearga ce era inainte si sa se refaca baza de date
	//m_DB.remove_all<Word>();
	//m_DB.remove_all<Player>();
	auto initPlayerCount = m_DB.count<Player>();
	auto initWordCount = m_DB.count<Word>();
	if (initPlayerCount == 0 && initWordCount == 0)
		populateDB(m_DB);

	// for testing
	//addPlayersFromDBToPlayersVector();
	//addWordsFromDBToWordsVector();
}

// Player

auto DataBase::getPlayerIterator(const std::string& name)
{
	for (auto it = m_players.begin(); it != m_players.end(); it++)
	{
		if (it->GetName() == name)
			return it;
	}
	return m_players.end();
}

void DataBase::addPlayer(Player& player)
{
	if (getPlayerIterator(player.GetName()) == m_players.end()) {
		auto id = m_DB.insert(player);
		player.SetId(id);
		m_players.push_back(player);
	}
}

void DataBase::deletePlayer(const std::string& name)
{
	/*if (searchPlayer(name))
	{
		m_playerDB.remove<Player>(getPlayer(name).getId());
		m_players.erase(getPlayerIterator(name));
	}*/

	auto it = m_players.begin();
	it = getPlayerIterator(name);
	if (it != m_players.end())
	{
		m_DB.remove<Player>(it->GetId());

		m_players.erase(it);
	}
}

bool DataBase::searchPlayer(const std::string& name) const
{
	for (auto& player : m_players)
	{
		if (player.GetName() == name)
			return true;
	}
	return false;
}

Player DataBase::getPlayer(const std::string& name)
{
	for (auto& player : m_players)
	{
		if (player.GetName() == name)
			return player;
	}
	return Player();
}

void DataBase::updatePlayer(const std::string& name, const Player& new_player)
{
	auto it = getPlayerIterator(name);
	if (it != m_players.end())
	{
		*it = new_player;

		m_DB.update(new_player);
	}
}

void DataBase::addPlayersFromDBToPlayersVector()
{
	auto playerCount = m_DB.count<Player>();
	if (playerCount > 0)
	{
		auto players = m_DB.get_all<Player>();
		for (auto& player : players)
		{
			m_players.push_back(player);
		}
	}
}

std::vector<Player> DataBase::getAllPlayers()
{
	return m_players;
}

void DataBase::printAllPLayers()
{
	std::cout << std::endl;
	for (int i = 0; i < m_players.size(); i++)
	{
		std::cout << m_players[i] << "\n";
	}
}

// Word

auto DataBase::getWordIterator(const std::string& word)
{
	for (auto it = m_words.begin(); it != m_words.end(); it++)
	{
		if (it->GetWord() == word)
			return it;
	}
	return m_words.end();
}

void DataBase::addWord(Word& word)
{
	if (getWordIterator(word.GetWord()) == m_words.end()) {
		auto id = m_DB.insert(word);
		word.SetId(id);
		m_words.push_back(word);
	}
}

void DataBase::deleteWord(const std::string& word)
{
	auto it = m_words.begin();
	it = getWordIterator(word);
	if (it != m_words.end())
	{
		m_DB.remove<Word>(it->GetId());

		m_words.erase(it);
	}
}

void DataBase::updateWord(const std::string& word, const Word& new_word)
{
	auto it = getWordIterator(word);
	if (it != m_words.end())
	{
		*it = new_word;

		m_DB.update(new_word);
	}
}

void DataBase::addWordsFromDBToWordsVector()
{
	auto playerCount = m_DB.count<Word>();
	if (playerCount > 0)
	{
		auto players = m_DB.get_all<Word>();
		for (auto& player : players)
		{
			m_words.push_back(player);
		}
	}
}

std::vector<Word> DataBase::getAllWords()
{
	return m_words;
}

void DataBase::printAllWords()
{
	std::cout << std::endl;
	for (int i = 0; i < m_words.size(); i++)
	{
		std::cout << m_words[i].GetId() << " " << m_words[i].GetWord() << "\n";
	}
}

void DataBase::AddPlayertoDB(Player& player)
{
	auto id = m_DB.insert(player);
	player.SetId(id);

}


// DB operations

std::optional<Player> DataBase::SearchPlayerInDB(const std::string& name)
{
	auto result = m_DB.get_all<Player>(sql::where(sql::is_equal(&Player::GetName, name)));

	if (!result.empty()) {
		// Player found, return the player
		return std::optional<Player>{result.front()};
	}
	else {
		// Player not found, return an empty optional
		return std::nullopt;
	}
}



// handlers

LoginHandler::LoginHandler(DataBase& storage) :m_DB{ storage }
{
}

crow::response LoginHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");
	if (usernameIter != end && passwordIter != end)
	{
		if (auto person{ m_DB.SearchPlayerInDB(usernameIter->second) }; person != std::nullopt)
		{
			if (person.value().GetPassword() == passwordIter->second)
			{
				return crow::response(200, "Login successful");
			}
			else
			{
				return crow::response(401, "Password incorrect.Try again");
			}
		}
		else
		{
			return crow::response(404, "Username not found");
		}
	}
	else
	{
		return crow::response(400);
	}
}

RegistrationHandler::RegistrationHandler(DataBase& storage) :m_DB{ storage }
{
}

crow::response RegistrationHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	auto passwordIter = bodyArgs.find("password");

	if (usernameIter == end || passwordIter == end)
	{
		return crow::response(400);
	}
	if (m_DB.SearchPlayerInDB(usernameIter->second) != std::nullopt)
	{
		return crow::response(403, "Username already exists");
	}
	else
	{
		/* verificare pentru username si pentru password
		if ()
		{
			return crow::response(403, "Credentials not valid");
		}
		*/
		Player newPlayerDB(0, usernameIter->second, passwordIter->second, 0, 0);
		m_DB.AddPlayertoDB(newPlayerDB);
	}
	return crow::response(201, "Successfull registration");
}
