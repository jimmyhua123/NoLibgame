#ifndef GAME_H // 防止重複包含標頭檔案
#define GAME_H // 定義標頭檔案宏

#include <iostream> // 包含iostream標頭檔，用於輸出
#include <vector> // 包含vector標頭檔，用於動態數組
#include <utility> // 包含utility標頭檔，用於std::pair
#include <ctime> // 包含ctime標頭檔，用於時間相關函數
#include <conio.h> // 包含conio.h，用於非阻塞式鍵盤輸入
#include <windows.h> // 包含windows.h，用於Windows API
#include <sstream> // 包含sstream標頭檔，用於字符串流

class PlayerManager; // 前向宣告PlayerManager類

class Game {
public:
    Game(PlayerManager& pm); // Game類的構造函數
    void setup(); // 設置遊戲
    void nextLevel(); // 進入下一級
    void draw(); // 繪製遊戲界面
    void input(); // 處理玩家輸入
    void logic(); // 更新遊戲邏輯
    void start(); // 開始遊戲
private:
    const int width = 30; // 遊戲區域寬度
    const int height = 20; // 遊戲區域高度
    char player = '^'; // 玩家符號
    char enemy = '@'; // 敵人符號
    char bullet = '|'; // 子彈符號
    char enemyBullet = '!'; // 敵方子彈符號
    char border = '#'; // 邊界符號
    int playerX; // 玩家位置
    std::vector<std::pair<int, int>> enemies; // 敵人位置列表
    std::vector<std::pair<int, int>> bullets; // 子彈位置列表
    std::vector<std::pair<int, int>> enemyBullets; // 敵方子彈位置列表
    bool gameOver; // 遊戲結束標誌
    int score; // 分數
    int level; // 等級
    PlayerManager& playerManager; // PlayerManager的引用
};

#endif // 結束GAME_H的條件編譯
