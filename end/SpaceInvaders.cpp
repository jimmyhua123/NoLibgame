#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

const int width = 30;
const int height = 20;
char player = '^';
char enemy = '@';
char bullet = '|';
char enemyBullet = '!';
char border = '#';
int playerX;
vector<pair<int, int>> enemies; // 紀錄敵人的位置
vector<pair<int, int>> bullets; // 紀錄玩家子彈的位置
vector<pair<int, int>> enemyBullets; // 紀錄敵人子彈的位置
bool gameOver;
int score;
int level;

void setup() {
    srand(time(0));
    gameOver = false;
    playerX = width / 2;
    score = 0;
    level = 1;
    enemies.clear();
    bullets.clear();
    enemyBullets.clear();

    // 初始化敵人
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < width; j += 5) {
            enemies.push_back({i, j});
        }
    }

    // 設置控制台游標隱藏
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false; // 設置游標不可見
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void nextLevel() {
    level++;
    enemies.clear();
    bullets.clear();
    enemyBullets.clear();

    // 增加敵人的數量
    for (int i = 0; i < 5 + level; ++i) {
        for (int j = 0; j < width; j += 5) {
            enemies.push_back({i, j});
        }
    }
}

void draw() {
    ostringstream oss;

    for (int i = 0; i < width + 2; i++) oss << border;
    oss << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) oss << border;

            bool drawn = false;

            // 畫敵人
            for (const auto &enemyPos : enemies) {
                if (enemyPos.first == i && enemyPos.second == j) {
                    oss << enemy;
                    drawn = true;
                    break;
                }
            }

            // 畫玩家子彈
            if (!drawn) {
                for (const auto &bulletPos : bullets) {
                    if (bulletPos.first == i && bulletPos.second == j) {
                        oss << bullet;
                        drawn = true;
                        break;
                    }
                }
            }

            // 畫敵人子彈
            if (!drawn) {
                for (const auto &enemyBulletPos : enemyBullets) {
                    if (enemyBulletPos.first == i && enemyBulletPos.second == j) {
                        oss << enemyBullet;
                        drawn = true;
                        break;
                    }
                }
            }

            // 畫玩家
            if (!drawn && i == height - 1 && j == playerX) {
                oss << player;
                drawn = true;
            }

            if (!drawn) oss << ' ';

            if (j == width - 1) oss << border;
        }
        oss << endl;
    }

    for (int i = 0; i < width + 2; i++) oss << border;
    oss << endl;

    oss << "Score: " << score << "  Level: " << level << endl;

    // 移動光標到頂端並輸出畫面
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << oss.str();
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == -32) { // special key (like arrow keys)
            key = _getch(); // get the actual key code
        }
        switch (key) {
            case 75: // 左箭頭
                if (playerX > 0) playerX -= 1; // 每次按鍵移動一個位置
                break;
            case 77: // 右箭頭
                if (playerX < width - 1) playerX += 1; // 每次按鍵移動一個位置
                break;
            case 32: // 空格鍵發射子彈
                bullets.push_back({height - 2, playerX});
                break;
        }
    }
}

void logic() {
    // 更新玩家子彈位置
    for (auto &bulletPos : bullets) {
        bulletPos.first--;
    }

    // 移除越界的玩家子彈
    bullets.erase(remove_if(bullets.begin(), bullets.end(),
                            [](const pair<int, int> &bulletPos) {
                                return bulletPos.first < 0;
                            }),
                  bullets.end());

    // 檢查玩家子彈是否擊中敵人
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool hit = false;
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
            if (bulletIt->first == enemyIt->first && bulletIt->second == enemyIt->second) {
                score++;
                enemyIt = enemies.erase(enemyIt);
                hit = true;
                break;
            } else {
                ++enemyIt;
            }
        }
        if (hit) {
            bulletIt = bullets.erase(bulletIt);
        } else {
            ++bulletIt;
        }
    }

    // 更新敵人子彈位置
    for (auto &enemyBulletPos : enemyBullets) {
        enemyBulletPos.first++;
    }

    // 移除越界的敵人子彈
    enemyBullets.erase(remove_if(enemyBullets.begin(), enemyBullets.end(),
                                 [](const pair<int, int> &enemyBulletPos) {
                                     return enemyBulletPos.first >= height;
                                 }),
                       enemyBullets.end());

    // 檢查敵人子彈是否擊中玩家
    for (const auto &enemyBulletPos : enemyBullets) {
        if (enemyBulletPos.first == height - 1 && enemyBulletPos.second == playerX) {
            gameOver = true;
        }
    }

    // 隨機生成敵人子彈
    if (rand() % 10 < level) { // 隨機概率隨等級增加
        if (!enemies.empty()) {
            int randomEnemy = rand() % enemies.size();
            enemyBullets.push_back({enemies[randomEnemy].first + 1, enemies[randomEnemy].second});
        }
    }

    // 如果所有敵人都被擊敗，則進入下一關
    if (enemies.empty() && !gameOver) {
        nextLevel();
    }
}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100); // 調整FPS和遊戲速度
    }

    cout << "Game Over! Your score is: " << score << "  Level: " << level << endl;

    // 恢復控制台游標可見
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    return 0;
}
