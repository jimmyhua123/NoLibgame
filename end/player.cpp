#include "player.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

PlayerManager::PlayerManager() {
    loadPlayers();
}

void PlayerManager::addPlayer(const std::string& id) {
    playerScores[id] = 0; // 初始化分數為0
    setCurrentPlayerID(id);
}

void PlayerManager::deletePlayer(const std::string& id) {
    playerScores.erase(id);
}

void PlayerManager::searchPlayer(const std::string& id) {
    auto it = playerScores.find(id);
    if (it != playerScores.end()) {
        std::cout << "Player ID: " << it->first << ", Score: " << it->second << std::endl;
    } else {
        std::cout << "Player ID not found.\n";
    }
}

void PlayerManager::printScoreRanking() {
    std::vector<std::pair<std::string, int>> ranking(playerScores.begin(), playerScores.end());
    std::sort(ranking.begin(), ranking.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return b.second < a.second; // 降序排序
    });
    std::cout << "Score Ranking:\n";
    for (const auto& it : ranking) {
        std::cout << "Player ID: " << it.first << ", Score: " << it.second << std::endl;
    }
}

void PlayerManager::savePlayers() {
    std::ofstream outFile("players.txt");
    for (const auto& it : playerScores) {
        outFile << it.first << " " << it.second << std::endl;
    }
    outFile.close();
}

void PlayerManager::loadPlayers() {
    std::ifstream inFile("players.txt");
    if (inFile.is_open()) {
        std::string id;
        int score;
        while (inFile >> id >> score) {
            playerScores[id] = score;
        }
        inFile.close();
    }
}

void PlayerManager::setCurrentPlayerID(const std::string& id) {
    currentPlayerID = id;
}

bool PlayerManager::hasCurrentPlayer() const {
    return !currentPlayerID.empty();
}
