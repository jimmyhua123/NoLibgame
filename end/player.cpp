#include "player.h" // 包含player.h標頭檔案，定義PlayerManager類
#include <iostream> // 包含iostream標頭檔，用於輸入輸出
#include <algorithm> // 包含algorithm標頭檔，用於標準算法
#include <vector> // 包含vector標頭檔，用於動態數組
#include <fstream> // 包含fstream標頭檔，用於文件輸入輸出

// 添加一個新的玩家ID
void PlayerManager::addPlayer(const std::string& id) {
    if (playerScores.find(id) == playerScores.end()) { // 檢查玩家ID是否已存在
        playerScores[id] = 0; // 如果不存在，添加玩家並設置初始分數為0
        std::cout << "Player " << id << " added.\n"; // 輸出玩家已添加的信息
    } else {
        std::cout << "Player " << id << " already exists.\n"; // 如果玩家已存在，輸出提示信息
    }
}

// 刪除指定的玩家ID
void PlayerManager::deletePlayer(const std::string& id) {
    if (playerScores.erase(id)) { // 刪除玩家，如果成功返回true
        std::cout << "Player " << id << " deleted.\n"; // 輸出玩家已刪除的信息
    } else {
        std::cout << "Player " << id << " not found.\n"; // 如果玩家未找到，輸出提示信息
    }
}

// 搜索並顯示指定的玩家ID及其分數
void PlayerManager::searchPlayer(const std::string& id) {
    auto it = playerScores.find(id); // 查找玩家ID
    if (it != playerScores.end()) { // 如果找到玩家
        std::cout << "Player ID: " << it->first << ", Score: " << it->second << "\n"; // 顯示玩家ID和分數
    } else {
        std::cout << "Player " << id << " not found.\n"; // 如果未找到玩家，輸出提示信息
    }
}

// 打印所有玩家的分數排名
void PlayerManager::printScoreRanking() {
    std::vector<std::pair<std::string, int>> ranking(playerScores.begin(), playerScores.end()); // 創建一個包含所有玩家ID和分數的向量
    std::sort(ranking.begin(), ranking.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second; // 按照分數從高到低排序
    });

    for (const auto& it : ranking) { // 遍歷排序後的向量
        std::cout << "Player ID: " << it.first << ", Score: " << it.second << "\n"; // 顯示玩家ID和分數
    }
}

// 保存所有玩家數據到文件
void PlayerManager::savePlayers() {
    std::ofstream ofs("players.dat"); // 打開文件進行寫操作
    for (const auto& pair : playerScores) { // 遍歷所有玩家
        ofs << pair.first << " " << pair.second << "\n"; // 將玩家ID和分數寫入文件
    }
}

// 從文件中加載玩家數據
void PlayerManager::loadPlayers() {
    std::ifstream ifs("players.dat"); // 打開文件進行讀操作
    std::string id; // 用於存儲讀取的玩家ID
    int score; // 用於存儲讀取的分數
    while (ifs >> id >> score) { // 逐行讀取玩家ID和分數
        playerScores[id] = score; // 將讀取的玩家數據存入map
    }
}

// 設置當前玩家ID
void PlayerManager::setCurrentPlayerID(const std::string& id) {
    currentPlayerID = id; // 設置當前玩家ID
}

// 獲取當前玩家ID
std::string PlayerManager::getCurrentPlayerID() {
    return currentPlayerID; // 返回當前玩家ID
}

// 為指定玩家添加分數
void PlayerManager::addPlayerScore(const std::string& id, int score) {
    if (playerScores.find(id) != playerScores.end()) { // 檢查玩家是否存在
        playerScores[id] += score; // 添加分數
    }
}
