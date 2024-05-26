#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>  // �s�W����H�]�t std::cout
#include <utility>   // �s�W����H�]�t std::pair

class PlayerManager {
private:
    std::unordered_map<std::string, int> playerScores;
    std::string currentPlayerID;

public:
    void addPlayer(const std::string& id);
    void deletePlayer(const std::string& id);
    void searchPlayer(const std::string& id);
    void printScoreRanking();
    void savePlayers();
    void loadPlayers();
    void setCurrentPlayerID(const std::string& id);
    std::string getCurrentPlayerID();
    void addPlayerScore(const std::string& id, int score);
};

#endif
