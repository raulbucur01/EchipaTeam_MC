#include "DataBase.h"
#include <regex>

using namespace http;

void populateDB(Storage& storage)
{
	std::vector<Player> players = {
		Player{-1,"Coco20", "amuitato", 200, 10},
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
		if ((*it).second.GetName() == name)
			return it;
	}
	return m_players.end();
}

void DataBase::addPlayer(Player& player)
{
	if (getPlayerIterator(player.GetName()) == m_players.end()) {
		auto id = m_DB.insert(player);
		player.SetId(id);
		m_players[player.GetName()] = player;
	}
}

void DataBase::AddPlayer(Player player)
{
	if (m_players.find(player.GetName()) != m_players.end())
		m_playersInGame[player.GetName()] = player;
	else
		m_players[player.GetName()] = player;
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
		m_DB.remove<Player>((*it).second.GetId());

		m_players.erase(it);
	}
}

bool DataBase::searchPlayer(const std::string& name) const
{
	for (auto& player : m_players)
	{
		if (player.second.GetName() == name)
			return true;
	}
	return false;
}

Player DataBase::GetPlayer(const std::string& name)
{
	if (m_players.find(name) != m_players.end())
		return m_players[name];
	return Player();
}

void DataBase::RemovePlayer(const std::string& name)
{
	m_playersInGame.erase(name);
	m_players.erase(name);// momentan las asa, playerul cand apasa pe exit iese de tot din client, nu revine la meniu
}

void DataBase::updatePlayer(const std::string& name, const Player& new_player)
{
	auto it = getPlayerIterator(name);
	if (it != m_players.end())
	{
		(*it).second = new_player;

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
			m_players[player.GetName()] = player;
		}
	}
}

std::unordered_map<std::string, Player> DataBase::getAllPlayers()
{
	return m_players;
}

void DataBase::printAllPLayers()
{
	std::cout << std::endl;
	for (auto it = m_players.begin(); it != m_players.end(); it++)
	{
		std::cout << it->second << "\n";
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

std::unordered_map<std::string, Player> DataBase::GetAllPlayers()
{
	return m_playersInGame;

}

bool DataBase::LoggedPlayer(const std::string& name)
{
	return m_players.find(name) != m_players.end();
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

GetScoreHandler::GetScoreHandler(DataBase& storage) :m_DB{ storage }
{
}

crow::response GetScoreHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");

	if (usernameIter != end) {
		if (auto currentPlayer = m_DB.SearchPlayerInDB(usernameIter->second); currentPlayer != std::nullopt) {
			crow::json::wvalue jsonResponse{
				{"Score", currentPlayer.value().GetScore()}
			};

			return crow::response(200, jsonResponse);
		}
		else {
			return crow::response(404, "Player not found");
		}
	}
	else {
		return crow::response(400, "Username not provided");
	}
}

GetCoinsHandler::GetCoinsHandler(DataBase& storage) :m_DB{ storage }
{

}

crow::response GetCoinsHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");

	if (usernameIter != end) {
		if (auto currentPlayer = m_DB.SearchPlayerInDB(usernameIter->second); currentPlayer != std::nullopt) {
			crow::json::wvalue jsonResponse{
				{"Coins", currentPlayer.value().GetCoins()}
			};

			return crow::response(200, jsonResponse);
		}
		else {
			return crow::response(404, "Player not found");
		}
	}
	else {
		return crow::response(400, "Username not provided");
	}
}


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
				if (m_DB.LoggedPlayer(person.value().GetName()))
				{
					return crow::response(403, "The user is already logged");
				}
				else
				{
					m_DB.AddPlayer(person.value());


					crow::json::wvalue jsonResponse{
						{"Name",person.value().GetName()},
						{"Password",person.value().GetPassword()},
						{"Score",person.value().GetScore()},
						{"Coins",person.value().GetCoins()}
					};

					return crow::response(200, jsonResponse);

				}
			}
			else
			{
				return crow::response(401, "Password incorrect! Please try again!");
			}
		}
		else
		{
			return crow::response(404, "Username not found! Please try again!");
		}
	}
	else
	{
		return crow::response(400, "You didn't enter anything in one or all slots!");
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
	auto confirmPasswordIter = bodyArgs.find("confirmPassword");

	if (usernameIter == end || passwordIter == end)
	{
		return crow::response(400, "You didn't enter anything in one or all slots!");
	}
	if (m_DB.SearchPlayerInDB(usernameIter->second) != std::nullopt)
	{
		return crow::response(403, "Username already exists! Please try again!");
	}
	else if (passwordIter->second == confirmPasswordIter->second
		&& usernameIter->second.length() > 6
		&& std::regex_match(passwordIter->second,
			std::regex("^.*(?=.{8,})(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#$%^&*+=`~])(?=.*[0-9]).*$")))
	{
		Player newPlayerDB(0, usernameIter->second, passwordIter->second, 0, 0);
		m_DB.AddPlayertoDB(newPlayerDB);
	}
	else
		return crow::response(404, "Credentials are not valid! Please try again!");

	return crow::response(201, "Account successfully created! Welcome!");
}

AddPlayerHandler::AddPlayerHandler(DataBase& storage) : m_DB{ storage }
{

}

crow::response AddPlayerHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");

	//nu stiu daca ar trebui sa folosesc move aici ca sa mut player ul din m_players in m_playersInGame

	m_DB.AddPlayer(m_DB.GetPlayer(usernameIter->second));

	return crow::response(200, "Added player");
}

RemovePlayerHandler::RemovePlayerHandler(DataBase& storage) :m_DB{ storage }
{
}

crow::response RemovePlayerHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	if (usernameIter != end)
	{
		m_DB.RemovePlayer(usernameIter->second);
		return crow::response(200, "Player removed");
	}
	else
		return crow::response(403);
}

