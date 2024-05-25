#ifndef GAME_H
#define GAME_H

class Game {
public:
    void start();
private:
    void setup();
    void draw();
    void input();
    void logic();
    bool gameOver;

    int ballX, ballY, ballDirX, ballDirY, paddleX;
    static const int width = 20;
    static const int height = 10;
    char ball = 'O';
    char paddle = '=';
    char brick = '#';
};

#endif // GAME_H
