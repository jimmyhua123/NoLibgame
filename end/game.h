#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <utility> // 添加這個標頭檔案
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <sstream> // 添加這個標頭檔案

class PlayerManager; // 前向宣告

class Game {
public:
    Game(PlayerManager& pm);
    void setup();
    void nextLevel();
    void draw();
    void input();
    void logic();
    void start();
private:
    const int width = 30;
    const int height = 20;
    char player = '^';
    char enemy = '@';
    char bullet = '|';
    char enemyBullet = '!';
    char border = '#';
    int playerX;
    std::vector<std::pair<int, int>> enemies;
    std::vector<std::pair<int, int>> bullets;
    std::vector<std::pair<int, int>> enemyBullets;
    bool gameOver;
    int score;
    int level;
    PlayerManager& playerManager;
};

#endif
