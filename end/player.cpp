#include "player.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

PlayerManager::PlayerManager() {
    loadPlayers();
}

void PlayerManager::addPlayer(const std::string& id) {
    if (playerScores.find(id) == playerScores.end()) {
        playerScores[id] = 0;
        cout << "Player " << id << " added.\n";
    } else {
        cout << "Player " << id << " already exists.\n";
    }
}

void PlayerManager::searchPlayer(const std::string& id) {
    if (playerScores.find(id) != playerScores.end()) {
        cout << "Player " << id << " found with score " << playerScores[id] << ".\n";
    } else {
        cout << "Player " << id << " not found.\n";
    }
}

void PlayerManager::printScoreRanking() {
    vector<pair<string, int>> ranking(playerScores.begin(), playerScores.end());
    sort(ranking.begin(), ranking.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return b.second < a.second;
    });

    cout << "Score Ranking:\n";
    for (const auto& it : ranking) {
        cout << "Player ID: " << it.first << ", Score: " << it.second << endl;
    }
}

void PlayerManager::deletePlayer(const std::string& id) {
    if (playerScores.erase(id)) {
        cout << "Player " << id << " deleted.\n";
    } else {
        cout << "Player " << id << " not found.\n";
    }
}

void PlayerManager::savePlayers() {
    ofstream outFile("players.dat");
    for (const auto& it : playerScores) {
        outFile << it.first << " " << it.second << endl;
    }
}

void PlayerManager::loadPlayers() {
    ifstream inFile("players.dat");
    string id;
    int score;
    while (inFile >> id >> score) {
        playerScores[id] = score;
    }
}

void PlayerManager::setCurrentPlayerID(const std::string& id) {
    currentPlayerID = id;
}

std::string PlayerManager::getCurrentPlayerID() {
    return currentPlayerID;
}
