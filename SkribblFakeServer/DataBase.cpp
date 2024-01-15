#include "DataBase.h"
#include <regex>
using namespace http;
using namespace skribbl;
import "Node.h";
#include <tuple>
DataBase::DataBase(const std::string& filename) : m_DB(createStorage(filename))
{
	m_DB.sync_schema();
	// daca se mai adauga cuvinte trebuie decomentat ca sa se strearga ce era inainte si sa se refaca baza de date
	//m_DB.remove_all<Word>();
	//m_DB.remove_all<Player>();
	//m_DB.remove_all<Purchase>();
	//m_DB.remove_all<ObtainedScore>();
	auto initPlayerCount = m_DB.count<Player>();
	auto initWordCount = m_DB.count<Word>();
	auto initPurchaseCount = m_DB.count<Purchase>();
	auto initObtainedScoreCount = m_DB.count<ObtainedScore>();
	if (initPlayerCount == 0 && initWordCount == 0 && initPurchaseCount == 0 && initObtainedScoreCount == 0)
	{
		populateDB(m_DB);
	}

	// for testing
	addWordsFromDBToWordsVector(); // avem vectoru de cuvinte permanent in DB momentan ca sa mearga ce a facut leo
}

DataBase& skribbl::DataBase::operator=(DataBase& other)
{
	m_players = other.m_players;
	m_playersInGame = other.m_playersInGame;
	m_words = other.m_words;
	m_graph = other.m_graph;
	m_line = other.m_line;

	return *this;
}

Storage& skribbl::DataBase::GetStorage()
{
	return m_DB;
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

void DataBase::AddPlayer(const Player& player)
{
	if (m_players.find(player.GetName()) != m_players.end())
		m_playersInGame[player.GetName()] = player;
	else
		m_players[player.GetName()] = player;
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

std::unordered_map<std::string, Player> DataBase::getAllPlayers()
{
	return m_players;
}

std::unordered_map<std::string, Player>& DataBase::GetPlayersInGame()
{
	return m_playersInGame;
}

Graph& DataBase::GetGraph()
{
	return m_graph;
}

std::vector<Node*>& DataBase::GetLine()
{
	return m_line;
}

void DataBase::printAllPLayers()
{
	std::cout << std::endl;
	for (auto it = m_players.begin(); it != m_players.end(); it++)
	{
		std::cout << it->second << "\n";
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

void DataBase::AddPlayertToDB(Player& player)
{
		auto id = m_DB.insert(player);
		player.SetId(id);
}

void DataBase::UpdatePlayerCoinsInDB(const std::string& name, int newCoins)
{
	m_DB.update_all(
		sql::set(sqlite_orm::c(&Player::GetCoins) = newCoins),
		sql::where(sqlite_orm::c(&Player::GetName) == name));
}

void DataBase::UpdatePlayerCurrentIconInDB(const std::string& name, int newIconId)
{
	m_DB.update_all(
		sql::set(sqlite_orm::c(&Player::GetCurrentIconId) = newIconId),
		sql::where(sqlite_orm::c(&Player::GetName) == name));
}

void DataBase::AddObtainedScoreToDB(const ObtainedScore& obtainedScore)
{
	m_DB.insert(obtainedScore);
}

//std::vector<ObtainedScore> DataBase::GetAllObtainedScores()
//{
//	return m_DB.get_all<ObtainedScore>();
//}

//void DataBase::PrintAllObtainedScores()
//{
//	std::cout << "\n";
//	std::vector<ObtainedScore> obtainedScores = GetAllObtainedScores();
//	for (auto obtainedScore : obtainedScores) {
//		std::cout << "\n";
//		std::cout << obtainedScore.GetId() << " " << obtainedScore.GetPlayerName() << " " << obtainedScore.GetObtainedScore();
//	}
//}

std::vector<int> DataBase::GetObtainedScoresByPlayer(const std::string& playerName)
{
	std::vector<ObtainedScore> obtainedScores = m_DB.get_all<ObtainedScore>(sql::where(sql::is_equal(&ObtainedScore::GetPlayerName, playerName)));
	std::vector<int> obtainedScoresValues;

	for (auto osc : obtainedScores) {
		obtainedScoresValues.push_back(osc.GetObtainedScore());
	}

	return obtainedScoresValues;
}

void DataBase::UpdatePlayerScoreInDB(const std::string& name, int newScoreAmount)
{
	m_DB.update_all(
		sql::set(sqlite_orm::c(&Player::GetScore) = newScoreAmount),
		sql::where(sqlite_orm::c(&Player::GetName) == name));
}

void DataBase::AddPurchaseToDB(const Purchase& purchase)
{
	m_DB.insert(purchase);
}

std::vector<Purchase> DataBase::GetPurchasesByPlayer(const std::string& playerName)
{
	return m_DB.get_all<Purchase>(sql::where(sql::is_equal(&Purchase::GetPlayerName, playerName)));
}

std::vector<int> DataBase::GetPurchasedIconIdsByPlayer(const std::string& playerName)
{
	std::vector<Purchase> purchases = GetPurchasesByPlayer(playerName);
	std::vector<int> purchasedIconIds;

	for (auto purchase : purchases) {
		purchasedIconIds.push_back(purchase.GetIconId());
	}

	return purchasedIconIds;
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

getObtainedScoresHandler::getObtainedScoresHandler(DataBase& storage) : m_DB{ storage }
{
}

crow::response getObtainedScoresHandler::operator()(const crow::request& req) const
{
	std::vector<int> obtainedScores;
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");

	if (usernameIter != end)
	{
		if (auto currentPlayer = m_DB.SearchPlayerInDB(usernameIter->second); currentPlayer != std::nullopt)
		{
			obtainedScores = m_DB.GetObtainedScoresByPlayer(usernameIter->second);

			crow::json::wvalue jsonResponse;
			jsonResponse["obtainedScores"] = obtainedScores;

			return crow::response(200, jsonResponse);
		}
		else crow::response(404, "Player not found in DataBase");
	}
	else crow::response(400, "Player`s name not found in url");
}

getPlayerInformationHandler::getPlayerInformationHandler(DataBase& storage) :m_DB{ storage }
{
}

crow::response getPlayerInformationHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");

	if (usernameIter != end)
	{
		if (auto currentPlayer = m_DB.SearchPlayerInDB(usernameIter->second); currentPlayer != std::nullopt)
		{
			crow::json::wvalue jsonResponse{
						{"Name", currentPlayer.value().GetName()},
						{"Password",  currentPlayer.value().GetPassword()},
						{"Score",  currentPlayer.value().GetScore()},
						{"Coins", currentPlayer.value().GetCoins()},
						{"CurrentIconId",  currentPlayer.value().GetCurrentIconId()}
			};

			return crow::response(200, jsonResponse);
		}
		else return crow::response(404, "Player not found in DataBase");
	}
	else return crow::response(400, "Player name not found in url");
}


ProcessPurchaseHandler::ProcessPurchaseHandler(DataBase& storage) : m_DB{ storage }
{
}

crow::response ProcessPurchaseHandler::operator()(const crow::request& req) const
{
	std::vector<int> iconIds;
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	auto iconIdPos = bodyArgs.find("currentIconID");

	if (iconIdPos != end && usernameIter != end)
	{
		int iconID = stoi(iconIdPos->second);
		if (auto currentPlayer = m_DB.SearchPlayerInDB(usernameIter->second); currentPlayer != std::nullopt)
		{
			iconIds = m_DB.GetPurchasedIconIdsByPlayer(usernameIter->second);
			for (auto i : iconIds)
			{
				if (i == iconID)
				{
					return crow::response(400, "You already own this icon!");

				}
			}
			if (currentPlayer->GetCoins() >= 20) {

				Purchase purchase = { -1, usernameIter->second, iconID };
				m_DB.AddPurchaseToDB(purchase);
				m_DB.UpdatePlayerCoinsInDB(usernameIter->second, currentPlayer->GetCoins() - 20);

				crow::json::wvalue jsonResponse{
			   {"Coins", currentPlayer.value().GetCoins() - 20}
				};

				return crow::response(200, jsonResponse);

			}
			else
			{
				return crow::response(404, "You don't have enough coins for this purchase! Each Icon costs 20 coins!");
			}
		}
		else {
			return crow::response(400, "Player not found in DataBase");
		}
	}
	else {
		return crow::response(400, "Icon id or Username not found in URL");
	}
}



RetrieveOwnedIconsHandler::RetrieveOwnedIconsHandler(DataBase& storage) : m_DB{ storage }
{
}

crow::response RetrieveOwnedIconsHandler::operator()(const crow::request& req) const
{
	std::vector<int> ownedIcons;
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");

	if (usernameIter != end)
	{
		if (auto currentPlayer = m_DB.SearchPlayerInDB(usernameIter->second); currentPlayer != std::nullopt)
		{
			ownedIcons = m_DB.GetPurchasedIconIdsByPlayer(usernameIter->second);

			crow::json::wvalue jsonResponse;
			jsonResponse["ownedIcons"] = ownedIcons;

			return crow::response(200, jsonResponse);
		}
		else {
			crow::response(404, "Player not found in DataBase");
		}
	}
	else {
		crow::response(400, "URL is not valid");
	}

}

UpdateCurrentIconIDHandler::UpdateCurrentIconIDHandler(DataBase& storage) : m_DB{ storage }
{
}

crow::response UpdateCurrentIconIDHandler::operator()(const crow::request& req) const
{

	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	auto positionId = bodyArgs.find("currentIconID");

	if (positionId != end && usernameIter != end) {

		if (usernameIter != end) {
			if (auto currentPlayer = m_DB.SearchPlayerInDB(usernameIter->second); currentPlayer != std::nullopt) {
				m_DB.UpdatePlayerCurrentIconInDB(usernameIter->second, stoi(positionId->second));
			};
		}
		else {
			return crow::response(404, "Player not found");
		}
	}
	else {
		return crow::response(400, "CurrentIconID or Username not found in the URL");
	}

	return crow::response(200, "Iconita ti-a fost modificata cu succes!");
}

RandomWordsFromDBHandler::RandomWordsFromDBHandler(DataBase& storage) :m_DB{ storage }
{
}

crow::response RandomWordsFromDBHandler::operator()(const crow::request& req) const
{
	std::srand(std::time(0));

	std::vector<Word> words = m_DB.getAllWords();

	if (words.size() < 3) {
		return crow::response(404, "Not enough words in the database");
	}

	int randomIndex;
	std::vector<std::string> randomWords;
	for (int i = 0; i < 3; ++i) {
		randomIndex = std::rand() % words.size();
		randomWords.push_back(words[randomIndex].GetWord());
	}


	crow::json::wvalue jsonResponse;
	jsonResponse["RandomWords"] = randomWords;

	return crow::response(200, jsonResponse);
}

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
						{"Name", person.value().GetName()},
						{"Password", person.value().GetPassword()},
						{"Score", person.value().GetScore()},
						{"Coins", person.value().GetCoins()},
						{"CurrentIconId", person.value().GetCurrentIconId()}
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
		Player newPlayerDB(0, usernameIter->second, passwordIter->second, 0, 0, 0);
		m_DB.AddPlayertToDB(newPlayerDB);
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
	if (usernameIter != end)
	{
		m_DB.AddPlayer(m_DB.GetPlayer(usernameIter->second));

		return crow::response(200, "Added player");
	}
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


SendMessageHandler::SendMessageHandler(Game& game,std::unordered_map<std::string, Player>& players) :m_game{ game }, m_players { players }
{
}

crow::response SendMessageHandler::operator()(const crow::request& req)  const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	auto messageIter = bodyArgs.find("message");
	bool ok = false;
	if (usernameIter != end && messageIter != end)
	{
		std::unordered_set<std::string> verify = m_game.VerifyPlayers();
		if (verify.find(usernameIter->second) != verify.end())
			return crow::response(402);
		Message message;
		if (messageIter->second == m_game.GetWord().GetWord())
		{
			m_game.verifyPlayer(usernameIter->second);
			message.SetContet(" guessed the word!");
			message.SetPlayerName(usernameIter->second);
		}
		else
		{
			message.SetContet(": " + messageIter->second);
			message.SetPlayerName(usernameIter->second);
		}
		for (auto& player : m_players)
		{
			player.second.AddMessage(message);
		}
		return crow::response(200);
		
	}
		return crow::response(400);
}





GetMessagesHandler::GetMessagesHandler(std::unordered_map<std::string, Player>& players) : m_players{ players }
{
}

crow::response GetMessagesHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto usernameIter = bodyArgs.find("username");
	if (usernameIter != end)
	{
		std::vector<crow::json::wvalue> messages;
		for (auto message : m_players[usernameIter->second].GetMessages())
			messages.push_back(crow::json::wvalue{
				{"Name",message.GetPlayerName()},
				{"Message",message.GetContent()},
				});
		return crow::json::wvalue{ messages };
	}
	else
		crow::response(400);
}

GetPlayersHandler::GetPlayersHandler(std::unordered_map<std::string, Player>& players) : m_players{ players }
{
}

crow::response GetPlayersHandler::operator()(const crow::request& req) const
{
	std::vector<crow::json::wvalue> players;
	if (m_players.empty())
		return crow::response(400);
	else
	{
		for (auto person : m_players)
		{
			players.push_back(crow::json::wvalue{
				{"name",person.second.GetName() },
				{"score",person.second.GetScore()},
				});
		}
		return crow::json::wvalue{ players };
	}
}

SendDrawingHandler::SendDrawingHandler(Graph& graph, std::vector<Node*>& line):
	m_graph{graph},
	m_line{line}
{
}

crow::response SendDrawingHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto coordinateXIter = bodyArgs.find("coordinateX");
	auto coordinateYIter = bodyArgs.find("coordinateY");
	auto redIter = bodyArgs.find("red");
	auto greenIter = bodyArgs.find("green");
	auto blueIter = bodyArgs.find("blue");
	auto isPaintingIter = bodyArgs.find("painting");
	if (isPaintingIter != end)
	{
		if (isPaintingIter->second == "false")
		{

			if (redIter != end && greenIter != end && blueIter != end)
			{
				m_graph.addNodes(std::make_pair(m_line, std::make_tuple(redIter->second, greenIter->second, blueIter->second)));
				m_line.clear();
			}
		}
		else if(coordinateXIter!=end && coordinateYIter!=end)
		{
			uint16_t x = stoi(coordinateXIter->second);
			uint16_t y = stoi(coordinateYIter->second);
			skribbl::Node* node = new skribbl::Node(std::make_pair(x, y));
			m_line.push_back(node);
		}
		return crow::response(200);
	}
	else
		return crow::response(401);
}

GetDrawingHandler::GetDrawingHandler(Graph& graph) : m_graph{graph}
{
}

crow::response GetDrawingHandler::operator()(const crow::request& req) const
{
	    std::vector<crow::json::wvalue> resultGraph;
		int index = 0;
		for (auto& line : m_graph.getNodes())
		{
			
			std::string red = std::get<0>(line.second);
			std::string green = std::get<1>(line.second);
			std::string blue = std::get<2>(line.second);
			for (const auto& node : line.first)
			{
				auto coordinates = node->getPosition();
				resultGraph.push_back(crow::json::wvalue{
					{"idLine",index},
					{"coordinateX", coordinates.first},
					{"coordinateY", coordinates.second},
					{"red", red},
					{"green", green},
					{"blue", blue} }
				);
			}
			index++;
			
		}
		return crow::json::wvalue{ resultGraph };
	
	

}

skribbl::stageGameHandler::stageGameHandler(Game& game): m_game{game}
{
}

crow::response skribbl::stageGameHandler::operator()(const crow::request& req) const
{
	crow::json::wvalue jsonResponse;
	if (m_game.getCurrentStage() == Stage::Lobby)
	{
		jsonResponse["stage"]="lobby";

	}
	if (m_game.getCurrentStage()==Stage::Choosing)
	{
		jsonResponse["stage"] = "choosing";
	}
	if (m_game.getCurrentStage()==Stage::Drawing)
	{
		jsonResponse["stage"] = "drawing";

	}
	if (m_game.getCurrentStage()==Stage::Results)
	{
		jsonResponse["stage"] = "results";

	}
	if (m_game.getCurrentStage()==Stage::FinalResults)
	{
		jsonResponse["stage"] = "finalresults";

	}
	return jsonResponse;

}

skribbl::StageResultFinalsHandler::StageResultFinalsHandler(Game& game):m_game{game}
{
}


crow::response skribbl::StageResultFinalsHandler::operator()(const crow::request& req) const
{
	std::vector<crow::json::wvalue> resultFinals;
	std::unordered_map<std::string, Player> players = m_game.GetPlayers();
	for (auto& player : players)
	{
		resultFinals.push_back(crow::json::wvalue{
			{player.second.GetName(),player.second.GetScore()} }
		);
	}
	return crow::json::wvalue{ resultFinals };
}

skribbl::setPaintHandler::setPaintHandler(Game& game):m_game{game}
{
}

crow::response skribbl::setPaintHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto nameIter = bodyArgs.find("name");
	if (nameIter != end)
	{
		if (m_game.verifyPlayer(nameIter->second) == false)
		{
			crow::json::wvalue text{ {"name",m_game.getWhoPaints()} };
			return text;
		}
	}	
	return crow::json::wvalue{ " " };
}

skribbl::startGameHandler::startGameHandler(Game& game, DataBase& storage): m_game{game}, m_storage{storage}
{
}

crow::response skribbl::startGameHandler::operator()(const crow::request& req) const
{
	m_game.setPlayers(m_storage.GetPlayersInGame());
	m_game.setQueue();
	m_game.setStages(m_storage.GetPlayersInGame().size());
	m_game.incrementIndex();
	return crow::response(200);
}

skribbl::chooseWordHandler::chooseWordHandler(Game& game):m_game{game}
{
}

crow::response skribbl::chooseWordHandler::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto wordIter = bodyArgs.find("word");
	if (wordIter != end)
	{
		m_game.setWord(Word(0,wordIter->second));
		m_game.incrementIndex();
		return crow::response(200);
	}
	return crow::response(402);
}

skribbl::getWordHandler::getWordHandler(Game& game):m_game{game}
{
}

crow::response skribbl::getWordHandler::operator()(const crow::request& req) const
{
	crow::json::wvalue text{ {"word",m_game.GetWord().GetWord()} };
	return text;
}
