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

	//void populateDB(Storage& storage);

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

		void deletePlayer(const std::string& name);
		bool searchPlayer(const std::string& name) const;
		auto getPlayerIterator(const std::string& name);
		void updatePlayer(const std::string& name, const Player& new_player);

		void addPlayersFromDBToPlayersVector();
		std::unordered_map<std::string, Player> getAllPlayers();
		std::unordered_map<std::string, Player>& GetPlayersInGame();
		Graph& GetGraph();
		std::vector < Node*>& GetLine();
		void printAllPLayers();

		// Word
		void addWord(Word& p);
		void deleteWord(const std::string& word);
		//bool searchWord(const std::string& name) const;
		//Word getWord(const std::string& name);
		auto getWordIterator(const std::string& word);
		void updateWord(const std::string& word, const Word& new_word);

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
		// returns all purchases in the database
		std::vector<Purchase> GetAllPurchases();
		// prints all purchases
		void PrintAllPurchases();
		// for the player with the specified name replaces the coins with the newCoinsAmount in the database
		void UpdatePlayerCoinsInDB(const std::string& name, int newCoinsAmount);
		// for the player with the specified name replaces the currentIconId with the newIconId in the database
		void UpdatePlayerCurrentIconInDB(const std::string& name, int newIconId);

		// for ObtainedScore
		void AddObtainedScoreToDB(const ObtainedScore& obtainedScore);
		std::vector<ObtainedScore> GetAllObtainedScores();
		void PrintAllObtainedScores();
		std::vector<int> GetObtainedScoresByPlayer(const std::string& playerName);
		void UpdatePlayerScoreInDB(const std::string& name, int newScoreAmount);

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
		SendMessageHandler(std::unordered_map<std::string, Player>& players);
		crow::response operator()(const crow::request& req) const;
	private:
		std::unordered_map<std::string, Player>& m_players;
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
}

	

