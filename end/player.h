#ifndef PLAYER_H // ����ƥ]�t���Y�ɮ�
#define PLAYER_H // �w�qPLAYER_H��

#include <string> // �]�tstring���Y�ɡA�Ω�r�Ŧ�ާ@
#include <unordered_map> // �]�tunordered_map���Y�ɡA�Ω󫢧ƬM�g
#include <fstream> // �]�tfstream���Y�ɡA�Ω���ާ@
#include <vector> // �]�tvector���Y�ɡA�Ω�ʺA�Ʋ�
#include <algorithm> // �]�talgorithm���Y�ɡA�Ω�зǺ�k
#include <iostream> // �]�tiostream���Y�ɡA�Ω��J��X
#include <utility> // �]�tutility���Y�ɡA�Ω�std::pair

class PlayerManager {
private:
    std::unordered_map<std::string, int> playerScores; // �s�x���aID�M���ƪ����ƬM�g
    std::string currentPlayerID; // ��e���a��ID

public:
    void addPlayer(const std::string& id); // �K�[���aID
    void deletePlayer(const std::string& id); // �R�����aID
    void searchPlayer(const std::string& id); // �j�����aID
    void printScoreRanking(); // ���L���ƱƦW
    void savePlayers(); // �O�s���a�ƾڨ���
    void loadPlayers(); // �q���[�����a�ƾ�
    void setCurrentPlayerID(const std::string& id); // �]�m��e���aID
    std::string getCurrentPlayerID(); // �����e���aID
    void addPlayerScore(const std::string& id, int score); // �K�[���a����
};

#endif // ����PLAYER_H������sĶ
