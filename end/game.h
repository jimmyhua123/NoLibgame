#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <utility> // �K�[�o�Ӽ��Y�ɮ�
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <sstream> // �K�[�o�Ӽ��Y�ɮ�

class PlayerManager; // �e�V�ŧi

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
