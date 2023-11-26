#include "SkribblServer.h"

ScribbleServer::ScribbleServer(int port) : port(port) {
	// Rutele pentru diferite requesturi
	CROW_ROUTE(app, "/join").methods("POST"_method)([this](const crow::request& req) {
		crow::response res;
	handleJoinRequest(req, res);
	return res;
		});

	CROW_ROUTE(app, "/drawing").methods("POST"_method)([this](const crow::request& req) {
		crow::response res;
	handleDrawing(req, res);
	return res;
		});

	CROW_ROUTE(app, "/guess").methods("POST"_method)([this](const crow::request& req) {
		crow::response res;
	handleGuess(req, res);
	return res;
		});

	CROW_ROUTE(app, "/gamestate").methods("GET"_method)([this](const crow::request& req) {
		crow::response res;
	handleGameStateRequest(req, res);
	return res;
		});
}

void ScribbleServer::start()
{
	//porneste aplicatia crow
	app.port(port).multithreaded().run();

}

void ScribbleServer::handleRequest(const crow::request& req, crow::response& res, void (ScribbleServer::* handler)(const crow::request&, crow::response&))
{
	(this->*handler)(req, res);
}

void ScribbleServer::handleJoinRequest(const crow::request& req, crow::response& res)
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
	broadcastMessage(broadcastMessageText);

	res.code = 200;
	res.write("OK");
	res.end();
}

void ScribbleServer::handleDrawing(const crow::request& req, crow::response& res)
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
	broadcastMessage(broadcastMessageText);

	res.code = 200;
	res.write("OK");
	res.end();
}

void ScribbleServer::handleGuess(const crow::request& req, crow::response& res)
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
	broadcastMessage(resultMessage);

	res.code = 200;
	res.write("OK");
	res.end();
}

void ScribbleServer::handleGameStateRequest(const crow::request& req, crow::response& res)
{
	// Trimite starea jocului curent playerului ce o cere
	std::string gameState = "Current Game State:\n";
	gameState += "Drawings: ";
	for (const auto& drawing : drawings) {
		gameState += drawing + ", ";
	}
	gameState += "\n";

	res.code = 200;
	res.write(gameState);
	res.end();
}

void ScribbleServer::broadcastMessage(const std::string& message)
{
	// nu am UI ul sa trimit mesaje tuturor playerilor
	//for (auto& client : connectedPlayers) {
	//	client.send_text(message);
	//}
}
