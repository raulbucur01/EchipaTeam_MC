#include "SkribblServer.h"

ScribbleServer::ScribbleServer(int port) : port(port) {
    // Set up routes for handling different requests
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

void ScribbleServer::handleJoinRequest(const crow::request& req, crow::response& res)
{
}

void ScribbleServer::handleDrawing(const crow::request& req, crow::response& res)
{
}

void ScribbleServer::handleGuess(const crow::request& req, crow::response& res)
{
}

void ScribbleServer::handleGameStateRequest(const crow::request& req, crow::response& res)
{
}

void ScribbleServer::broadcastMessage(const std::string& message)
{
}
