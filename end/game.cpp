#include "game.h" // 包含game.h頭文件，定義Game類
#include "player.h" // 包含player.h頭文件，定義PlayerManager類
#include <iostream> // 包含iostream標頭檔，用於輸出
#include <conio.h> // 包含conio.h，用於非阻塞式鍵盤輸入
#include <windows.h> // 包含windows.h，用於Windows API
#include <vector> // 包含vector標頭檔，用於動態數組
#include <sstream> // 包含sstream標頭檔，用於字符串流
#include <algorithm> // 包含algorithm標頭檔，用於標準算法
#include <cstdlib> // 包含cstdlib標頭檔，用於標準庫函數
#include <ctime> // 包含ctime標頭檔，用於時間相關函數
using namespace std; // 使用標準命名空間

// Game類的構造函數，初始化PlayerManager的引用
Game::Game(PlayerManager& pm) : playerManager(pm) {}

// setup()函數，用於初始化遊戲狀態
void Game::setup() {
    srand(time(0)); // 設置隨機數生成器的種子
    gameOver = false; // 初始化遊戲結束標誌
    playerX = width / 2; // 將玩家位置設置在屏幕中間
    score = 0; // 初始化分數
    level = 1; // 初始化等級
    enemies.clear(); // 清空敵人列表
    bullets.clear(); // 清空子彈列表
    enemyBullets.clear(); // 清空敵方子彈列表

    // 初始化敵人位置
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < width; j += 5) {
            enemies.push_back({i, j}); // 添加敵人到敵人列表
        }
    }

    // 隱藏控制台光標
    CONSOLE_CURSOR_INFO cursorInfo; 
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // 獲取控制台光標信息
    cursorInfo.bVisible = false; // 設置光標不可見
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // 更新控制台光標信息
}

// nextLevel()函數，用於進入下一級
void Game::nextLevel() {
    level++; // 增加等級
    enemies.clear(); // 清空敵人列表
    bullets.clear(); // 清空子彈列表
    enemyBullets.clear(); // 清空敵方子彈列表

    // 初始化新的敵人位置，根據等級增加敵人數量
    for (int i = 0; i < 5 + level; ++i) {
        for (int j = 0; j < width; j += 5) {
            enemies.push_back({i, j}); // 添加敵人到敵人列表
        }
    }
}

// draw()函數，用於繪製遊戲界面
void Game::draw() {
    ostringstream oss; // 創建字符串流對象

    // 繪製頂部邊界
    for (int i = 0; i < width + 2; i++) oss << border;
    oss << endl;

    // 繪製遊戲區域
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) oss << border; // 繪製左邊邊界

            bool drawn = false; // 用於標記當前位置是否已繪製

            // 繪製敵人
            for (const auto &enemyPos : enemies) {
                if (enemyPos.first == i && enemyPos.second == j) {
                    oss << enemy; // 如果當前位置有敵人，繪製敵人
                    drawn = true; // 標記已繪製
                    break; // 跳出循環
                }
            }

            // 如果當前位置沒有敵人，繪製子彈
            if (!drawn) {
                for (const auto &bulletPos : bullets) {
                    if (bulletPos.first == i && bulletPos.second == j) {
                        oss << bullet; // 如果當前位置有子彈，繪製子彈
                        drawn = true; // 標記已繪製
                        break; // 跳出循環
                    }
                }
            }

            // 如果當前位置沒有敵人和子彈，繪製敵方子彈
            if (!drawn) {
                for (const auto &enemyBulletPos : enemyBullets) {
                    if (enemyBulletPos.first == i && enemyBulletPos.second == j) {
                        oss << enemyBullet; // 如果當前位置有敵方子彈，繪製敵方子彈
                        drawn = true; // 標記已繪製
                        break; // 跳出循環
                    }
                }
            }

            // 如果當前位置沒有敵人、子彈和敵方子彈，繪製玩家
            if (!drawn && i == height - 1 && j == playerX) {
                oss << player; // 如果當前位置是玩家，繪製玩家
                drawn = true; // 標記已繪製
            }

            // 如果當前位置什麼都沒有，繪製空格
            if (!drawn) oss << ' ';

            // 繪製右邊邊界
            if (j == width - 1) oss << border;
        }
        oss << endl; // 換行
    }

    // 繪製底部邊界
    for (int i = 0; i < width + 2; i++) oss << border;
    oss << endl;

    // 繪製分數和等級信息
    oss << "Score: " << score << "  Level: " << level << endl;

    // 將光標位置設置為(0, 0)，以便更新整個控制台內容
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << oss.str(); // 輸出字符串流中的內容
}

// input()函數，用於處理玩家輸入
void Game::input() {
    if (_kbhit()) { // 如果有鍵盤輸入
        char key = _getch(); // 獲取按鍵
        if (key == -32) { // 如果是特殊按鍵，繼續讀取
            key = _getch();
        }
        switch (key) {
            case 75: // 左箭頭鍵
                if (playerX > 0) playerX -= 1; // 移動玩家到左邊
                break;
            case 77: // 右箭頭鍵
                if (playerX < width - 1) playerX += 1; // 移動玩家到右邊
                break;
            case 32: // 空格鍵
                bullets.push_back({height - 2, playerX}); // 發射子彈
                break;
        }
    }
}

// logic()函數，用於更新遊戲邏輯
void Game::logic() {
    // 更新子彈位置
    for (auto &bulletPos : bullets) {
        bulletPos.first--; // 子彈向上移動
    }

    // 刪除屏幕外的子彈
    bullets.erase(remove_if(bullets.begin(), bullets.end(),
        [this](const std::pair<int, int> &bulletPos) {
            return bulletPos.first < 0; // 如果子彈超出屏幕上邊界，刪除
        }),
        bullets.end());

    // 檢測子彈與敵人的碰撞
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool hit = false; // 紀錄是否有擊中敵人
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
            if (bulletIt->first == enemyIt->first && bulletIt->second == enemyIt->second) {
                score++; // 增加分數
                enemyIt = enemies.erase(enemyIt); // 刪除被擊中的敵人
                hit = true; // 標記為擊中
                break; // 跳出內循環
            } else {
                ++enemyIt; // 否則，繼續檢查下一個敵人
            }
        }
        if (hit) {
            bulletIt = bullets.erase(bulletIt); // 刪除擊中敵人的子彈
        } else {
            ++bulletIt; // 否則，檢查下一顆子彈
        }
    }

    // 更新敵方子彈位置
    for (auto &enemyBulletPos : enemyBullets) {
        enemyBulletPos.first++; // 敵方子彈向下移動
    }

    // 刪除屏幕外的敵方子彈
    enemyBullets.erase(remove_if(enemyBullets.begin(), enemyBullets.end(),
        [this](const std::pair<int, int> &enemyBulletPos) {
            return enemyBulletPos.first >= height; // 如果敵方子彈超出屏幕下邊界，刪除
        }),
        enemyBullets.end());

    // 檢測敵方子彈與玩家的碰撞
    for (const auto &enemyBulletPos : enemyBullets) {
        if (enemyBulletPos.first == height - 1 && enemyBulletPos.second == playerX) {
            gameOver = true; // 如果敵方子彈擊中玩家，遊戲結束
        }
    }

    // 根據等級隨機生成敵方子彈
    if (rand() % 10 < level) {
        if (!enemies.empty()) { // 如果還有敵人
            int randomEnemy = rand() % enemies.size(); // 隨機選擇一個敵人
            enemyBullets.push_back({enemies[randomEnemy].first + 1, enemies[randomEnemy].second}); // 從選擇的敵人位置發射子彈
        }
    }

    // 如果所有敵人都被消滅且遊戲未結束，進入下一級
    if (enemies.empty() && !gameOver) {
        nextLevel(); // 進入下一級
    }
}

// start()函數，用於開始遊戲
void Game::start() {
    setup(); // 設置遊戲
    while (!gameOver) { // 當遊戲未結束
        draw(); // 繪製遊戲界面
        input(); // 處理玩家輸入
        logic(); // 更新遊戲邏輯
        Sleep(100); // 遊戲速度控制
    }

    // 遊戲結束，顯示分數和等級
    cout << "Game Over! Your score is: " << score << "  Level: " << level << endl;

    // 添加玩家分數到PlayerManager
    playerManager.addPlayerScore(playerManager.getCurrentPlayerID(), score);

    // 恢復控制台光標顯示
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
