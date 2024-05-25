#include "game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

void Game::setup() {
    gameOver = false;
    ballX = width / 2;
    ballY = height / 2;
    ballDirX = -1;
    ballDirY = -1;
    paddleX = width / 2 - 2;
}

void Game::draw() {
    system("cls");

    for (int i = 0; i < width + 2; i++) cout << brick;
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << brick;

            if (i == ballY && j == ballX) cout << ball;
            else if (i == height - 1 && j >= paddleX && j < paddleX + 5) cout << paddle;
            else cout << ' ';

            if (j == width - 1) cout << brick;
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << brick;
    cout << endl;
}

void Game::input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 75: // •™Ωb¿Y
                if (paddleX > 0) paddleX--;
                break;
            case 77: // •kΩb¿Y
                if (paddleX < width - 5) paddleX++;
                break;
        }
    }
}

void Game::logic() {
    ballX += ballDirX;
    ballY += ballDirY;

    if (ballX == 0 || ballX == width - 1) ballDirX = -ballDirX;
    if (ballY == 0) ballDirY = -ballDirY;

    if (ballY == height - 1) {
        if (ballX >= paddleX && ballX < paddleX + 5) ballDirY = -ballDirY;
        else gameOver = true;
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

    cout << "Game Over!" << endl;
}
