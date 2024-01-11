#include "SkribblServer.h"

using namespace http;

void SkribblServer::Start(DataBase& storage)
{
	// Rutele pentru diferite requesturi
	CROW_ROUTE(m_app, "/")([]() {
		return "The server is working";
		});

	auto& loginTest = CROW_ROUTE(m_app, "/login")
		.methods(crow::HTTPMethod::POST);
	loginTest(LoginHandler(storage));

	auto& registrationTest = CROW_ROUTE(m_app, "/registration")
		.methods(crow::HTTPMethod::PUT);
	registrationTest(RegistrationHandler(storage));
	CROW_ROUTE(m_app, "/currentPlayersInGame")([&]() {
		std::unordered_map<std::string,Player> playersInGame = storage.GetAllPlayers();
		std::vector<crow::json::wvalue> players;
		for (const auto& player : playersInGame)
			players.push_back(crow::json::wvalue{
				{"Player:",player.first},
				{"Score:",player.second.GetScore()},
				{"Coins:",player.second.GetCoins()}
				});
		return crow::json::wvalue{players };
		
		});

	auto& messageSent = CROW_ROUTE(m_app, "/chat/send")
		.methods(crow::HTTPMethod::POST);
	messageSent(SendMessageHandler(storage.GetPlayersInGame()));
	auto& messagesGet = CROW_ROUTE(m_app, "/chat/get")
		.methods(crow::HTTPMethod::GET);
	messagesGet(GetMessagesHandler(storage.GetPlayersInGame()));

	//CROW_ROUTE(m_app,"/newMessageSend")


	/*CROW_ROUTE(m_app, "/send").methods(crow::HTTPMethod::POST)([&](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
		auto end = bodyArgs.end();
		auto usernameIter = bodyArgs.find("username");
		auto wordIter = bodyArgs.find("word");
		if (wordIter==end)
			return crow::response(400, "The message was not sent correctly");
		//m_messages.push_back({ usernameIter->second, wordIter->second });
		return crow::response(200,"Added succesfully to server");
		});
	std::string word ="";
	*/
	/*CROW_ROUTE(m_app, "/get")([&]() {
		if (!m_messages.empty())
		{
			//auto lastMessage = messages[messages.size() - 1];
			messages.clear();
			return lastMessage;
			
		}
		return word;
		});*/
	auto& addPlayer = CROW_ROUTE(m_app, "/game/addPlayer")
		.methods(crow::HTTPMethod::PUT);
	addPlayer(AddPlayerHandler(storage));

	auto& removePlayer = CROW_ROUTE(m_app, "/game/removePlayer")
		.methods(crow::HTTPMethod::PUT);
	removePlayer(RemovePlayerHandler(storage));




	CROW_ROUTE(m_app, "/join").methods("POST"_method)([this](const crow::request& req) {
		crow::response res;
		HandleJoinRequest(req, res);
		return res;
		});

	CROW_ROUTE(m_app, "/drawing").methods("POST"_method)([this](const crow::request& req) {
		crow::response res;
		HandleDrawing(req, res);
		return res;
		});

	CROW_ROUTE(m_app, "/guess").methods("POST"_method)([this](const crow::request& req) {
		crow::response res;
		HandleGuess(req, res);
		return res;
		});

	CROW_ROUTE(m_app, "/gamestate").methods("GET"_method)([this](const crow::request& req) {
		crow::response res;
		HandleGameStateRequest(req, res);
		return res;
		});

	CROW_ROUTE(m_app, "/UpdateCurrentIconID").methods(crow::HTTPMethod::PUT); {
		auto& UpdateCurrentIconID(UpdateCurrentIconIDHandler(storage));
	};

	CROW_ROUTE(m_app, "/RetrieveOwnedIcons").methods(crow::HTTPMethod::GET); {
		auto& RetrieveOwnedIcons(RetrieveOwnedIconsHandler(storage));
	};

	auto& getScore = CROW_ROUTE(m_app, "/getScore")
		.methods(crow::HTTPMethod::GET);
	getScore(GetScoreHandler(storage));
	
	auto& getCoins = CROW_ROUTE(m_app, "/getCoins")
		.methods(crow::HTTPMethod::GET);
	getCoins(GetCoinsHandler(storage));
	
	auto& RandomWordsFromDB = CROW_ROUTE(m_app, "/RandomWordsFromDB")
		.methods(crow::HTTPMethod::GET);
	RandomWordsFromDB(RandomWordsFromDBHandler(storage));

	m_app.port(18080).multithreaded().run();
}

void SkribblServer::HandleRequest(const crow::request& req, crow::response& res, void (SkribblServer::* handler)(const crow::request&, crow::response&))
{
	(this->*handler)(req, res);
}

void SkribblServer::HandleJoinRequest(const crow::request& req, crow::response& res)
{
	auto json = crow::json::load(req.body);
	if (!json) {
		res.code = 400;
		res.write("Bad Request");
		res.end();
		return;
	}

	// Primeste numele playerului
	std::string playerName = json["name"].s();

	// Urmeaza implementarea playerului in lista de playeri a bazei de date
	// ...

	// Mesaj cu informatii legate de noul player
	std::string broadcastMessageText = "Player " + playerName + " joined the game\n";
	BroadcastMessage(broadcastMessageText);

	res.code = 200;
	res.write("OK");
	res.end();
}

void SkribblServer::HandleDrawing(const crow::request& req, crow::response& res)
{

	auto json = crow::json::load(req.body);
	if (!json) {
		res.code = 400;
		res.write("Bad Request");
		res.end();
		return;
	}

	// Extract drawing data from JSON
	std::string drawingData = json["drawing"].s();

	// Implementare date despre desen in sqlite
	// ...

	// Urmeaza modificare dupa terminarea UI ului pentru a arata desenul tuturor playerilor corespunzatori logicii jocului
	std::string broadcastMessageText = "Drawing: " + drawingData + "\n";
	BroadcastMessage(broadcastMessageText);

	res.code = 200;
	res.write("OK");
	res.end();
}

void SkribblServer::HandleGuess(const crow::request& req, crow::response& res)
{
	auto json = crow::json::load(req.body);
	if (!json) {
		res.code = 400;
		res.write("Bad Request");
		res.end();
		return;
	}

	std::string guessData = json["guess"].s();

	// Implementare ghicire cuvant
	// ...

	// Ce a ghicit player ul
	std::string resultMessage = "Player guessed: " + guessData + "\n";
	BroadcastMessage(resultMessage);

	res.code = 200;
	res.write("OK");
	res.end();
}

void SkribblServer::HandleGameStateRequest(const crow::request& req, crow::response& res)
{
	// Trimite starea jocului curent playerului ce o cere
	std::string gameState = "Current Game State:\n";
	gameState += "Drawings: ";
	for (const auto& drawing : m_drawings) {
		gameState += drawing + ", ";
	}
	gameState += "\n";

	res.code = 200;
	res.write(gameState);
	res.end();
}

void SkribblServer::BroadcastMessage(const std::string& message)
{
	// nu am UI ul sa trimit mesaje tuturor playerilor
	//for (auto& client : connectedPlayers) {
	//	client.send_text(message);
	//}
}

