#ifndef PLAYER_H // 防止重複包含標頭檔案
#define PLAYER_H // 定義PLAYER_H宏

#include <string> // 包含string標頭檔，用於字符串操作
#include <unordered_map> // 包含unordered_map標頭檔，用於哈希映射
#include <fstream> // 包含fstream標頭檔，用於文件操作
#include <vector> // 包含vector標頭檔，用於動態數組
#include <algorithm> // 包含algorithm標頭檔，用於標準算法
#include <iostream> // 包含iostream標頭檔，用於輸入輸出
#include <utility> // 包含utility標頭檔，用於std::pair

class PlayerManager {
private:
    std::unordered_map<std::string, int> playerScores; // 存儲玩家ID和分數的哈希映射
    std::string currentPlayerID; // 當前玩家的ID

public:
    void addPlayer(const std::string& id); // 添加玩家ID
    void deletePlayer(const std::string& id); // 刪除玩家ID
    void searchPlayer(const std::string& id); // 搜索玩家ID
    void printScoreRanking(); // 打印分數排名
    void savePlayers(); // 保存玩家數據到文件
    void loadPlayers(); // 從文件加載玩家數據
    void setCurrentPlayerID(const std::string& id); // 設置當前玩家ID
    std::string getCurrentPlayerID(); // 獲取當前玩家ID
    void addPlayerScore(const std::string& id, int score); // 添加玩家分數
};

#endif // 結束PLAYER_H的條件編譯
