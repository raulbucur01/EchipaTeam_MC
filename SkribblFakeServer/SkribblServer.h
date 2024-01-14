#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <cstring>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
#include "Word.h"
#include "Player.h"
#include "DataBase.h"
#include <optional>
#include <unordered_set>
#include "Message.h"
#include "Game.h"
using namespace sqlite_orm;
using namespace skribbl;
//using PlayerStorage = storage_t<Player>;
//using WordStorage = storage_t<Word>;

class SkribblServer {
public:
    SkribblServer(DataBase& dB);
    void Start();
    void GameStart();

private:
    crow::SimpleApp m_app;
    DataBase storage;
    Game game;
};