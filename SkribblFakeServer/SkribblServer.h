#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <cstring>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "Word.h"
#include "Player.h"
#include "PlayerDB.h"
using namespace sqlite_orm;

//using PlayerStorage = storage_t<Player>;
//using WordStorage = storage_t<Word>;

class ScribbleServer {
public:
    void Start(PlayerDB& storage);
private:
    crow::SimpleApp m_app;

    // Game state
    std::vector<std::string> m_drawings;
    std::string m_currentWord;

    void HandleRequest(const crow::request& req, crow::response& res, void(ScribbleServer::* handler)(const crow::request&, crow::response&));
    void HandleJoinRequest(const crow::request& req, crow::response& res);
    void HandleDrawing(const crow::request& req, crow::response& res);
    void HandleGuess(const crow::request& req, crow::response& res);
    void HandleGameStateRequest(const crow::request& req, crow::response& res);
    void BroadcastMessage(const std::string& message);
};