#include "SkribblServer.h"
using namespace http;
using namespace skribbl;

SkribblServer::SkribblServer(DataBase& dB):
	storage{std::move(dB)}
{
}

void SkribblServer::Start()
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
	messageSent(SendMessageHandler(game,storage.GetPlayersInGame()));
	auto& messagesGet = CROW_ROUTE(m_app, "/chat/get")
		.methods(crow::HTTPMethod::GET);
	messagesGet(GetMessagesHandler(storage.GetPlayersInGame()));

	auto& addPlayer = CROW_ROUTE(m_app, "/game/addPlayer")
		.methods(crow::HTTPMethod::PUT);
	addPlayer(AddPlayerHandler(storage));

	auto& removePlayer = CROW_ROUTE(m_app, "/game/removePlayer")
		.methods(crow::HTTPMethod::PUT);
	removePlayer(RemovePlayerHandler(storage));

	auto& getPlayers = CROW_ROUTE(m_app, "/game/getPlayers")
		.methods(crow::HTTPMethod::GET);
	getPlayers(GetPlayersHandler(storage.GetPlayersInGame())); //pentru scor o sa fac o ruta pt update la fiecare jucator 
	auto& sendDrawing = CROW_ROUTE(m_app, "/round/sendDrawing")
		.methods(crow::HTTPMethod::POST);
	sendDrawing(SendDrawingHandler(storage.GetGraph(), storage.GetLine()));
	auto& getDrawing = CROW_ROUTE(m_app, "/round/getDrawing")
		.methods(crow::HTTPMethod::GET);
	getDrawing(GetDrawingHandler(storage.GetGraph()));
															  
	auto& getObtainedScores = CROW_ROUTE(m_app, "/getObtainedScores")
		.methods(crow::HTTPMethod::GET);
	getObtainedScores(getObtainedScoresHandler(storage));

	auto& getPlayerInformation = CROW_ROUTE(m_app, "/getPlayerInformation")
		.methods(crow::HTTPMethod::GET);
	getPlayerInformation(getPlayerInformationHandler(storage));

	auto& ProcessPurchase = CROW_ROUTE(m_app, "/ProcessPurchase")
		.methods(crow::HTTPMethod::PUT);
	ProcessPurchase(ProcessPurchaseHandler(storage));

	auto& UpdateCurrentIconID = CROW_ROUTE(m_app, "/UpdateCurrentIconID")
		.methods(crow::HTTPMethod::PUT);
	UpdateCurrentIconID(UpdateCurrentIconIDHandler(storage));
	
	auto& RetrieveOwnedIcons = CROW_ROUTE(m_app, "/RetrieveOwnedIcons")
		.methods(crow::HTTPMethod::GET);
	RetrieveOwnedIcons(RetrieveOwnedIconsHandler(storage));

	auto& getScore = CROW_ROUTE(m_app, "/getScore")
		.methods(crow::HTTPMethod::GET);
	getScore(GetScoreHandler(storage));
	
	auto& getCoins = CROW_ROUTE(m_app, "/getCoins")
		.methods(crow::HTTPMethod::GET);
	getCoins(GetCoinsHandler(storage));
	
	auto& RandomWordsFromDB = CROW_ROUTE(m_app, "/RandomWordsFromDB")
		.methods(crow::HTTPMethod::GET);
	RandomWordsFromDB(RandomWordsFromDBHandler(storage));
	auto& stageGame = CROW_ROUTE(m_app, "/stage")
		.methods(crow::HTTPMethod::GET);
	stageGame(stageGameHandler(game));
	auto& setPaint = CROW_ROUTE(m_app, "/stage/drawing")
		.methods(crow::HTTPMethod::GET);
	setPaint(setPaintHandler(game));
	auto& startGame = CROW_ROUTE(m_app, "/startGame")
		.methods(crow::HTTPMethod::GET);
	startGame(startGameHandler(game,storage));
	auto& choosingWord = CROW_ROUTE(m_app, "/choosingWord")
		.methods(crow::HTTPMethod::POST);
	choosingWord(chooseWordHandler(game));
	auto& getWord = CROW_ROUTE(m_app, "/getWord")
		.methods(crow::HTTPMethod::GET);
	getWord(getWordHandler(game));


	//auto& stageResult = CROW_ROUTE(m_app, "/stage/result")
		//.methods(crow::HTTPMethod::GET);
	//stageResult(StageResultHandler(game));

	auto& stageResultFinals = CROW_ROUTE(m_app, "/stage/resultFinals")
		.methods(crow::HTTPMethod::GET);
	stageResultFinals(StageResultFinalsHandler(game));
	m_app.port(18080).multithreaded().run();
}

void SkribblServer::GameStart()
{
	game.setStages(storage.GetPlayersInGame().size());
}



