#pragma once

#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include <crow.h>
#include "Player.h"
#include "Word.h"
#include "Purchase.h"
#include <fstream>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include "Message.h"
#include "ObtainedScore.h"
#include "graph.h"
#include "Game.h"
namespace sql = sqlite_orm;
import utils;

namespace skribbl
{
	static auto createStorage(const std::string& filename) {
		return sql::make_storage(
			filename,
			sql::make_table("Player",
				sql::make_column("id", &Player::SetId, &Player::GetId, sql::primary_key().autoincrement()),
				sql::make_column("Name", &Player::SetName, &Player::GetName),
				sql::make_column("Password", &Player::SetPassword, &Player::GetPassword),
				sql::make_column("Score", &Player::SetScore, &Player::GetScore),
				sql::make_column("Coins", &Player::SetCoins, &Player::GetCoins),
				sql::make_column("CurrentIconId", &Player::SetCurrentIconId, &Player::GetCurrentIconId)
			),
			sql::make_table("Word",
				sql::make_column("id", &Word::SetId, &Word::GetId, sql::primary_key().autoincrement()),
				sql::make_column("word", &Word::SetWord, &Word::GetWord)
			),
			sql::make_table("Purchase",
				sql::make_column("id", &Purchase::SetId, &Purchase::GetId, sql::primary_key().autoincrement()),
				sql::make_column("playerName", &Purchase::SetPlayerName, &Purchase::GetPlayerName),
				sql::make_column("iconId", &Purchase::SetIconId, &Purchase::GetIconId)
			),
			sql::make_table("ObtainedScore",
				sql::make_column("id", &ObtainedScore::SetId, &ObtainedScore::GetId, sql::primary_key().autoincrement()),
				sql::make_column("playerName", &ObtainedScore::SetPlayerName, &ObtainedScore::GetPlayerName),
				sql::make_column("obtainedScore", &ObtainedScore::SetObtainedScore, &ObtainedScore::GetObtainedScore)
			)
		);
	}

	using Storage = decltype(createStorage(""));

	inline void populateDB(Storage& storage)
	{
		std::vector<Player> players = {
			Player{-1,"Coco20", "amuitato", 200, 10, 0},
			Player{-1,"raul807", "parolasmechera", 0, 0, 0},
			Player{-1,"ronaldoGOAT_CR7", "amuitato2", 0, 0, 0},
			Player{-1,"vlad", "parolacomplexa", 0, 0, 0},
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

		std::vector<Purchase> purchases = {
			Purchase{-1, "Coco20", 1},
			Purchase{-1, "raul807", 3},
			Purchase{-1, "Coco20", 3}
		};
		storage.insert_range(purchases.begin(), purchases.end());

		std::vector<ObtainedScore> obtainedScores = {
			ObtainedScore{-1, "Coco20", 100},
			ObtainedScore{-1, "Coco20", 200}
		};
		storage.insert_range(obtainedScores.begin(), obtainedScores.end());
	}

	class DataBase
	{
	public:
		DataBase() = default;
		DataBase(const std::string& filename);

		DataBase& operator=(DataBase& other);
		Storage& GetStorage();

		// Player

		void AddPlayer(const Player& player);
		Player GetPlayer(const std::string& name);
		void RemovePlayer(const std::string& name);

		auto getPlayerIterator(const std::string& name);

		std::unordered_map<std::string, Player> getAllPlayers();
		std::unordered_map<std::string, Player>& GetPlayersInGame();
		Graph& GetGraph();
		std::vector<Node*>& GetLine();
		void printAllPLayers();

		void addWordsFromDBToWordsVector();
		std::vector<Word> getAllWords();
		std::unordered_map<std::string, Player> GetAllPlayers();
		bool LoggedPlayer(const std::string& name);
		void printAllWords();

		// For direct DB interaction:
		// for Player

		std::optional<Player> SearchPlayerInDB(const std::string& name);
		void AddPlayertToDB(Player& player);

		// for Purchase

		// adds a purchase to the database
		void AddPurchaseToDB(const Purchase& purchase);
		// returns all purchases for the player with the specified playerName
		std::vector<Purchase> GetPurchasesByPlayer(const std::string& playerName);
		// returns all the icon ids for the player with the specified playerName
		std::vector<int> GetPurchasedIconIdsByPlayer(const std::string& playerName);
		// for the player with the specified name replaces the coins with the newCoinsAmount in the database
		void UpdatePlayerCoinsInDB(const std::string& name, int newCoinsAmount);
		// for the player with the specified name replaces the currentIconId with the newIconId in the database
		void UpdatePlayerCurrentIconInDB(const std::string& name, int newIconId);

		// for ObtainedScore
		void AddObtainedScoreToDB(const ObtainedScore& obtainedScore);
		std::vector<int> GetObtainedScoresByPlayer(const std::string& playerName);
		void UpdatePlayerScoreInDB(const std::string& name, int newScoreAmount);

		// template doesn't work for Word
		template <class T>
		std::vector<T> GetAll() {
			return m_DB.get_all<T>();
		}

		// template doesn't work for Word
		template <class T>
		void PrintAll() {
			std::cout << "\n";
			std::vector<T> items = GetAll<T>();
			for (auto item : items) {
				std::cout << "\n";
				std::cout << item;
			}
		}

		~DataBase() = default;

	private:
		Storage m_DB;
		std::unordered_map<std::string, Player> m_players;             //la fel
		std::unordered_map<std::string, Player> m_playersInGame;       //Poate ar trebui sa folosesc Player*
		std::vector<Word> m_words;
		Graph m_graph;
		std::vector<Node*>m_line;
	};

	class LoginHandler {
	public:
		LoginHandler(DataBase& storage);
		crow::response operator()(const crow::request& req)const;

	private:
		DataBase& m_DB;
	};

	class RegistrationHandler {
	public:
		RegistrationHandler(DataBase& storage);
		crow::response operator()(const crow::request& req)const;
	private:
		DataBase& m_DB;
	};

	class getPlayerInformationHandler {
	public:
		getPlayerInformationHandler(DataBase& storage);
		crow::response operator()(const crow::request& req)const;
	private:
		DataBase& m_DB;
	};

	class getObtainedScoresHandler {
	public:
		getObtainedScoresHandler(DataBase& storage);
		crow::response operator()(const crow::request& req)const;
	private:
		DataBase& m_DB;
	};

	class ProcessPurchaseHandler {
	public:
		ProcessPurchaseHandler(DataBase& storage);
		crow::response operator()(const crow::request& req)const;
	private:
		DataBase& m_DB;
	};

	class AddPlayerHandler {
	public:
		AddPlayerHandler(DataBase& storage);
		crow::response operator()(const crow::request& req)const;
	private:
		DataBase& m_DB;
	};

	class RemovePlayerHandler {
	public:
		RemovePlayerHandler(DataBase& storage);
		crow::response operator()(const crow::request& req)const;
	private:
		DataBase& m_DB;
	};

	class GetCoinsHandler {
	public:
		GetCoinsHandler(DataBase& storage);
		crow::response operator()(const crow::request& req)const;

	private:
		DataBase& m_DB;
	};

	class GetScoreHandler {
	public:
		GetScoreHandler(DataBase& storage);
		crow::response operator()(const crow::request& req)const;

	private:
		DataBase& m_DB;
	};

	class RandomWordsFromDBHandler {
	public:
		RandomWordsFromDBHandler(DataBase& storage);
		crow::response operator()(const crow::request& req)const;

	private:
		DataBase& m_DB;
	};

	class UpdateCurrentIconIDHandler {
	public:
		UpdateCurrentIconIDHandler(DataBase& storage);
		crow::response operator()(const crow::request& req)const;
	private:
		DataBase& m_DB;
	};
	class SendMessageHandler {
	public:
		SendMessageHandler(Game&game,std::unordered_map<std::string, Player>& players);
		crow::response operator()(const crow::request& req) const;
	private:
		std::unordered_map<std::string, Player>& m_players;
		Game& m_game;
	};
	class GetMessagesHandler {
	public:
		GetMessagesHandler(std::unordered_map<std::string, Player>& players);
		crow::response operator()(const crow::request& req)const;
	private:
		std::unordered_map<std::string, Player>& m_players;
	};
	class GetPlayersHandler {
	public:
		GetPlayersHandler(std::unordered_map<std::string, Player>& players);
		crow::response operator()(const crow::request& req) const;
	private:
		std::unordered_map<std::string, Player>& m_players;
	};
	class SendDrawingHandler {
	public:
		SendDrawingHandler(Graph& graph, std::vector<Node*>& line);
		crow::response operator()(const crow::request& req) const;
	private:
		Graph& m_graph;
		std::vector<Node*>& m_line;

	};
	class GetDrawingHandler {
	public:
		GetDrawingHandler(Graph& graph);
		crow::response operator()(const crow::request& req) const;
	private:
		Graph& m_graph;
	};

	class RetrieveOwnedIconsHandler {
	public:
		RetrieveOwnedIconsHandler(DataBase& storage);
		crow::response operator()(const crow::request& req)const;
	private:
		DataBase& m_DB;
	};
	class stageGameHandler {
	public:
		stageGameHandler(Game& game);
		crow::response operator()(const crow::request& req)const;
	private:
		Game& m_game;
	};

	class StageResultFinalsHandler {
	public:
		StageResultFinalsHandler(Game& game);
		crow::response operator()(const crow::request& req)const;
	private:
		Game& m_game;

	};
	class setPaintHandler {
	public:
		setPaintHandler(Game& game);
		crow::response operator()(const crow::request& req)const;
	private:
		Game& m_game;

	};

	class startGameHandler {
	public:
		startGameHandler(Game& game, DataBase& storage);
		crow::response operator()(const crow::request& req)const;
	private:
		Game& m_game;
		DataBase& m_storage;
	};

	class chooseWordHandler {
	public:
		chooseWordHandler(Game& game);
		crow::response operator()(const crow::request& req)const;
	private:
		Game& m_game;

	};

	class getWordHandler {
	public:
		getWordHandler(Game& game);
		crow::response operator()(const crow::request& req)const;
	private:
		Game& m_game;
	};
}

	

