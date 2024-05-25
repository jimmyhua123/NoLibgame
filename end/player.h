#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <map>

class PlayerManager {
public:
    PlayerManager();
    void addPlayer(const std::string& id);
    void deletePlayer(const std::string& id);
    void searchPlayer(const std::string& id);
    void printScoreRanking();
    void savePlayers();
    void loadPlayers();
    void setCurrentPlayerID(const std::string& id);
    bool hasCurrentPlayer() const;

private:
    std::map<std::string, int> playerScores;
    std::string currentPlayerID;
};

#endif
