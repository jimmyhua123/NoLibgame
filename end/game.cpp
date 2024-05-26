#include "game.h"
#include "player.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <sstream> // 確保包含這個標頭檔案
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

Game::Game(PlayerManager& pm) : playerManager(pm) {}

void Game::setup() {
    srand(time(0));
    gameOver = false;
    playerX = width / 2;
    score = 0;
    level = 1;
    enemies.clear();
    bullets.clear();
    enemyBullets.clear();

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < width; j += 5) {
            enemies.push_back({i, j});
        }
    }

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false; 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void Game::nextLevel() {
    level++;
    enemies.clear();
    bullets.clear();
    enemyBullets.clear();

    for (int i = 0; i < 5 + level; ++i) {
        for (int j = 0; j < width; j += 5) {
            enemies.push_back({i, j});
        }
    }
}

void Game::draw() {
    ostringstream oss;

    for (int i = 0; i < width + 2; i++) oss << border;
    oss << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) oss << border;

            bool drawn = false;

            for (const auto &enemyPos : enemies) {
                if (enemyPos.first == i && enemyPos.second == j) {
                    oss << enemy;
                    drawn = true;
                    break;
                }
            }

            if (!drawn) {
                for (const auto &bulletPos : bullets) {
                    if (bulletPos.first == i && bulletPos.second == j) {
                        oss << bullet;
                        drawn = true;
                        break;
                    }
                }
            }

            if (!drawn) {
                for (const auto &enemyBulletPos : enemyBullets) {
                    if (enemyBulletPos.first == i && enemyBulletPos.second == j) {
                        oss << enemyBullet;
                        drawn = true;
                        break;
                    }
                }
            }

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

    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << oss.str();
}

void Game::input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == -32) {
            key = _getch();
        }
        switch (key) {
            case 75:
                if (playerX > 0) playerX -= 1;
                break;
            case 77:
                if (playerX < width - 1) playerX += 1;
                break;
            case 32:
                bullets.push_back({height - 2, playerX});
                break;
        }
    }
}

void Game::logic() {
    for (auto &bulletPos : bullets) {
        bulletPos.first--;
    }

    bullets.erase(remove_if(bullets.begin(), bullets.end(),
        [this](const std::pair<int, int> &bulletPos) {
            return bulletPos.first < 0;
        }),
        bullets.end());

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

    for (auto &enemyBulletPos : enemyBullets) {
        enemyBulletPos.first++;
    }

    enemyBullets.erase(remove_if(enemyBullets.begin(), enemyBullets.end(),
        [this](const std::pair<int, int> &enemyBulletPos) {
            return enemyBulletPos.first >= height;
        }),
        enemyBullets.end());

    for (const auto &enemyBulletPos : enemyBullets) {
        if (enemyBulletPos.first == height - 1 && enemyBulletPos.second == playerX) {
            gameOver = true;
        }
    }

    if (rand() % 10 < level) {
        if (!enemies.empty()) {
            int randomEnemy = rand() % enemies.size();
            enemyBullets.push_back({enemies[randomEnemy].first + 1, enemies[randomEnemy].second});
        }
    }

    if (enemies.empty() && !gameOver) {
        nextLevel();
    }
}

void Game::start() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100);
    }

    cout << "Game Over! Your score is: " << score << "  Level: " << level << endl;

    playerManager.addPlayerScore(playerManager.getCurrentPlayerID(), score);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
