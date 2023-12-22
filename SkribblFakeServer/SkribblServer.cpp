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

	CROW_ROUTE(m_app, "/getScore").methods("GET"_method)([this](const crow::request& req) {
		crow::response res;
	HandleGetScoreRequest(req, res);
	return res;
		});

	CROW_ROUTE(m_app, "/getCoins").methods("GET"_method)([this](const crow::request& req) {
		crow::response res;
	HandleGetCoinsRequest(req, res);
	return res;
		});

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

