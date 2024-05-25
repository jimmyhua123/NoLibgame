#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>
#include <vector>

class PlayerManager {
public:
    PlayerManager();
    void addPlayer(const std::string& id);
    void searchPlayer(const std::string& id);
    void printScoreRanking();
    void deletePlayer(const std::string& id);
    void savePlayers();
    void loadPlayers();
    void setCurrentPlayerID(const std::string& id);
    std::string getCurrentPlayerID();
private:
    std::unordered_map<std::string, int> playerScores;
    std::string currentPlayerID;
};

#endif // PLAYER_H
