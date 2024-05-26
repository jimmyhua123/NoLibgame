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
vector<pair<int, int>> enemies; // �����ĤH����m
vector<pair<int, int>> bullets; // �������a�l�u����m
vector<pair<int, int>> enemyBullets; // �����ĤH�l�u����m
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

    // ��l�ƼĤH
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < width; j += 5) {
            enemies.push_back({i, j});
        }
    }

    // �]�m����x�������
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false; // �]�m��Ф��i��
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void nextLevel() {
    level++;
    enemies.clear();
    bullets.clear();
    enemyBullets.clear();

    // �W�[�ĤH���ƶq
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

            // �e�ĤH
            for (const auto &enemyPos : enemies) {
                if (enemyPos.first == i && enemyPos.second == j) {
                    oss << enemy;
                    drawn = true;
                    break;
                }
            }

            // �e���a�l�u
            if (!drawn) {
                for (const auto &bulletPos : bullets) {
                    if (bulletPos.first == i && bulletPos.second == j) {
                        oss << bullet;
                        drawn = true;
                        break;
                    }
                }
            }

            // �e�ĤH�l�u
            if (!drawn) {
                for (const auto &enemyBulletPos : enemyBullets) {
                    if (enemyBulletPos.first == i && enemyBulletPos.second == j) {
                        oss << enemyBullet;
                        drawn = true;
                        break;
                    }
                }
            }

            // �e���a
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

    // ���ʥ��Ш쳻�ݨÿ�X�e��
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
            case 75: // ���b�Y
                if (playerX > 0) playerX -= 1; // �C�����䲾�ʤ@�Ӧ�m
                break;
            case 77: // �k�b�Y
                if (playerX < width - 1) playerX += 1; // �C�����䲾�ʤ@�Ӧ�m
                break;
            case 32: // �Ů���o�g�l�u
                bullets.push_back({height - 2, playerX});
                break;
        }
    }
}

void logic() {
    // ��s���a�l�u��m
    for (auto &bulletPos : bullets) {
        bulletPos.first--;
    }

    // �����V�ɪ����a�l�u
    bullets.erase(remove_if(bullets.begin(), bullets.end(),
                            [](const pair<int, int> &bulletPos) {
                                return bulletPos.first < 0;
                            }),
                  bullets.end());

    // �ˬd���a�l�u�O�_�����ĤH
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

    // ��s�ĤH�l�u��m
    for (auto &enemyBulletPos : enemyBullets) {
        enemyBulletPos.first++;
    }

    // �����V�ɪ��ĤH�l�u
    enemyBullets.erase(remove_if(enemyBullets.begin(), enemyBullets.end(),
                                 [](const pair<int, int> &enemyBulletPos) {
                                     return enemyBulletPos.first >= height;
                                 }),
                       enemyBullets.end());

    // �ˬd�ĤH�l�u�O�_�������a
    for (const auto &enemyBulletPos : enemyBullets) {
        if (enemyBulletPos.first == height - 1 && enemyBulletPos.second == playerX) {
            gameOver = true;
        }
    }

    // �H���ͦ��ĤH�l�u
    if (rand() % 10 < level) { // �H�����v�H���żW�[
        if (!enemies.empty()) {
            int randomEnemy = rand() % enemies.size();
            enemyBullets.push_back({enemies[randomEnemy].first + 1, enemies[randomEnemy].second});
        }
    }

    // �p�G�Ҧ��ĤH���Q���ѡA�h�i�J�U�@��
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
        Sleep(100); // �վ�FPS�M�C���t��
    }

    cout << "Game Over! Your score is: " << score << "  Level: " << level << endl;

    // ��_����x��Хi��
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    return 0;
}
