#include "player.h"
#include <iostream>
#include <algorithm>
#include <vector>

void PlayerManager::addPlayer(const std::string& id) {
    if (playerScores.find(id) == playerScores.end()) {
        playerScores[id] = 0;
        std::cout << "Player " << id << " added.\n";
    } else {
        std::cout << "Player " << id << " already exists.\n";
    }
}

void PlayerManager::deletePlayer(const std::string& id) {
    if (playerScores.erase(id)) {
        std::cout << "Player " << id << " deleted.\n";
    } else {
        std::cout << "Player " << id << " not found.\n";
    }
}

void PlayerManager::searchPlayer(const std::string& id) {
    auto it = playerScores.find(id);
    if (it != playerScores.end()) {
        std::cout << "Player ID: " << it->first << ", Score: " << it->second << "\n";
    } else {
        std::cout << "Player " << id << " not found.\n";
    }
}

void PlayerManager::printScoreRanking() {
    std::vector<std::pair<std::string, int>> ranking(playerScores.begin(), playerScores.end());
    std::sort(ranking.begin(), ranking.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
    });

    for (const auto& it : ranking) {
        std::cout << "Player ID: " << it.first << ", Score: " << it.second << "\n";
    }
}

void PlayerManager::savePlayers() {
    std::ofstream ofs("players.dat");
    for (const auto& pair : playerScores) {
        ofs << pair.first << " " << pair.second << "\n";
    }
}

void PlayerManager::loadPlayers() {
    std::ifstream ifs("players.dat");
    std::string id;
    int score;
    while (ifs >> id >> score) {
        playerScores[id] = score;
    }
}

void PlayerManager::setCurrentPlayerID(const std::string& id) {
    currentPlayerID = id;
}

std::string PlayerManager::getCurrentPlayerID() {
    return currentPlayerID;
}

void PlayerManager::addPlayerScore(const std::string& id, int score) {
    if (playerScores.find(id) != playerScores.end()) {
        playerScores[id] += score;
    }
}
