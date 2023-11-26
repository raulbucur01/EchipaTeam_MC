#pragma once
#include <iostream>
#include <vector>
#include <thread>

class ScribbleServer {
public:
    ScribbleServer(int port);
    void start();

private:
    int serverSocket;
    std::vector<std::thread> clientThreads;

    std::vector<std::string> players;
    std::vector<std::string> drawings;
    std::string currentWord;

    void handleClient(int clientSocket);
    void handleJoinRequest(int clientSocket);
    void handleDrawing(int clientSocket, const std::string& drawing);
    void handleGuess(int clientSocket, const std::string& guess);
    void handleGameStateRequest(int clientSocket);

    void broadcastMessage(const std::string& message);
};