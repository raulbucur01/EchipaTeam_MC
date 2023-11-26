#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <cstring>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "Word.h"
#include "Player.h"

using namespace sqlite_orm;

//using PlayerStorage = storage_t<Player>;
//using WordStorage = storage_t<Word>;

class ScribbleServer {
public:
    ScribbleServer() = default; 
    ScribbleServer(int port);
    void start();

private:
    crow::SimpleApp app;
    int port;

    // Game state
    std::vector<std::string> drawings;
    std::string currentWord;

    void handleRequest(const crow::request& req, crow::response& res, void(ScribbleServer::* handler)(const crow::request&, crow::response&));
    void handleJoinRequest(const crow::request& req, crow::response& res);
    void handleDrawing(const crow::request& req, crow::response& res);
    void handleGuess(const crow::request& req, crow::response& res);
    void handleGameStateRequest(const crow::request& req, crow::response& res);
    void broadcastMessage(const std::string& message);
};