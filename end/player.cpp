#include "player.h" // �]�tplayer.h���Y�ɮסA�w�qPlayerManager��
#include <iostream> // �]�tiostream���Y�ɡA�Ω��J��X
#include <algorithm> // �]�talgorithm���Y�ɡA�Ω�зǺ�k
#include <vector> // �]�tvector���Y�ɡA�Ω�ʺA�Ʋ�
#include <fstream> // �]�tfstream���Y�ɡA�Ω����J��X

// �K�[�@�ӷs�����aID
void PlayerManager::addPlayer(const std::string& id) {
    if (playerScores.find(id) == playerScores.end()) { // �ˬd���aID�O�_�w�s�b
        playerScores[id] = 0; // �p�G���s�b�A�K�[���a�ó]�m��l���Ƭ�0
        std::cout << "Player " << id << " added.\n"; // ��X���a�w�K�[���H��
    } else {
        std::cout << "Player " << id << " already exists.\n"; // �p�G���a�w�s�b�A��X���ܫH��
    }
}

// �R�����w�����aID
void PlayerManager::deletePlayer(const std::string& id) {
    if (playerScores.erase(id)) { // �R�����a�A�p�G���\��^true
        std::cout << "Player " << id << " deleted.\n"; // ��X���a�w�R�����H��
    } else {
        std::cout << "Player " << id << " not found.\n"; // �p�G���a�����A��X���ܫH��
    }
}

// �j������ܫ��w�����aID�Ψ����
void PlayerManager::searchPlayer(const std::string& id) {
    auto it = playerScores.find(id); // �d�䪱�aID
    if (it != playerScores.end()) { // �p�G��쪱�a
        std::cout << "Player ID: " << it->first << ", Score: " << it->second << "\n"; // ��ܪ��aID�M����
    } else {
        std::cout << "Player " << id << " not found.\n"; // �p�G����쪱�a�A��X���ܫH��
    }
}

// ���L�Ҧ����a�����ƱƦW
void PlayerManager::printScoreRanking() {
    std::vector<std::pair<std::string, int>> ranking(playerScores.begin(), playerScores.end()); // �Ыؤ@�ӥ]�t�Ҧ����aID�M���ƪ��V�q
    std::sort(ranking.begin(), ranking.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second; // ���Ӥ��Ʊq����C�Ƨ�
    });

    for (const auto& it : ranking) { // �M���Ƨǫ᪺�V�q
        std::cout << "Player ID: " << it.first << ", Score: " << it.second << "\n"; // ��ܪ��aID�M����
    }
}

// �O�s�Ҧ����a�ƾڨ���
void PlayerManager::savePlayers() {
    std::ofstream ofs("players.dat"); // ���}���i��g�ާ@
    for (const auto& pair : playerScores) { // �M���Ҧ����a
        ofs << pair.first << " " << pair.second << "\n"; // �N���aID�M���Ƽg�J���
    }
}

// �q��󤤥[�����a�ƾ�
void PlayerManager::loadPlayers() {
    std::ifstream ifs("players.dat"); // ���}���i��Ū�ާ@
    std::string id; // �Ω�s�xŪ�������aID
    int score; // �Ω�s�xŪ��������
    while (ifs >> id >> score) { // �v��Ū�����aID�M����
        playerScores[id] = score; // �NŪ�������a�ƾڦs�Jmap
    }
}

// �]�m��e���aID
void PlayerManager::setCurrentPlayerID(const std::string& id) {
    currentPlayerID = id; // �]�m��e���aID
}

// �����e���aID
std::string PlayerManager::getCurrentPlayerID() {
    return currentPlayerID; // ��^��e���aID
}

// �����w���a�K�[����
void PlayerManager::addPlayerScore(const std::string& id, int score) {
    if (playerScores.find(id) != playerScores.end()) { // �ˬd���a�O�_�s�b
        playerScores[id] += score; // �K�[����
    }
}
