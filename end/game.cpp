#include "game.h" // �]�tgame.h�Y���A�w�qGame��
#include "player.h" // �]�tplayer.h�Y���A�w�qPlayerManager��
#include <iostream> // �]�tiostream���Y�ɡA�Ω��X
#include <conio.h> // �]�tconio.h�A�Ω�D���릡��L��J
#include <windows.h> // �]�twindows.h�A�Ω�Windows API
#include <vector> // �]�tvector���Y�ɡA�Ω�ʺA�Ʋ�
#include <sstream> // �]�tsstream���Y�ɡA�Ω�r�Ŧ�y
#include <algorithm> // �]�talgorithm���Y�ɡA�Ω�зǺ�k
#include <cstdlib> // �]�tcstdlib���Y�ɡA�Ω�зǮw���
#include <ctime> // �]�tctime���Y�ɡA�Ω�ɶ��������
using namespace std; // �ϥμзǩR�W�Ŷ�

// Game�����c�y��ơA��l��PlayerManager���ޥ�
Game::Game(PlayerManager& pm) : playerManager(pm) {}

// setup()��ơA�Ω��l�ƹC�����A
void Game::setup() {
    srand(time(0)); // �]�m�H���ƥͦ������ؤl
    gameOver = false; // ��l�ƹC�������лx
    playerX = width / 2; // �N���a��m�]�m�b�̹�����
    score = 0; // ��l�Ƥ���
    level = 1; // ��l�Ƶ���
    enemies.clear(); // �M�żĤH�C��
    bullets.clear(); // �M�Ťl�u�C��
    enemyBullets.clear(); // �M�żĤ�l�u�C��

    // ��l�ƼĤH��m
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < width; j += 5) {
            enemies.push_back({i, j}); // �K�[�ĤH��ĤH�C��
        }
    }

    // ���ñ���x����
    CONSOLE_CURSOR_INFO cursorInfo; 
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // �������x���ЫH��
    cursorInfo.bVisible = false; // �]�m���Ф��i��
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // ��s����x���ЫH��
}

// nextLevel()��ơA�Ω�i�J�U�@��
void Game::nextLevel() {
    level++; // �W�[����
    enemies.clear(); // �M�żĤH�C��
    bullets.clear(); // �M�Ťl�u�C��
    enemyBullets.clear(); // �M�żĤ�l�u�C��

    // ��l�Ʒs���ĤH��m�A�ھڵ��żW�[�ĤH�ƶq
    for (int i = 0; i < 5 + level; ++i) {
        for (int j = 0; j < width; j += 5) {
            enemies.push_back({i, j}); // �K�[�ĤH��ĤH�C��
        }
    }
}

// draw()��ơA�Ω�ø�s�C���ɭ�
void Game::draw() {
    ostringstream oss; // �Ыئr�Ŧ�y��H

    // ø�s�������
    for (int i = 0; i < width + 2; i++) oss << border;
    oss << endl;

    // ø�s�C���ϰ�
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) oss << border; // ø�s�������

            bool drawn = false; // �Ω�аO��e��m�O�_�wø�s

            // ø�s�ĤH
            for (const auto &enemyPos : enemies) {
                if (enemyPos.first == i && enemyPos.second == j) {
                    oss << enemy; // �p�G��e��m���ĤH�Aø�s�ĤH
                    drawn = true; // �аO�wø�s
                    break; // ���X�`��
                }
            }

            // �p�G��e��m�S���ĤH�Aø�s�l�u
            if (!drawn) {
                for (const auto &bulletPos : bullets) {
                    if (bulletPos.first == i && bulletPos.second == j) {
                        oss << bullet; // �p�G��e��m���l�u�Aø�s�l�u
                        drawn = true; // �аO�wø�s
                        break; // ���X�`��
                    }
                }
            }

            // �p�G��e��m�S���ĤH�M�l�u�Aø�s�Ĥ�l�u
            if (!drawn) {
                for (const auto &enemyBulletPos : enemyBullets) {
                    if (enemyBulletPos.first == i && enemyBulletPos.second == j) {
                        oss << enemyBullet; // �p�G��e��m���Ĥ�l�u�Aø�s�Ĥ�l�u
                        drawn = true; // �аO�wø�s
                        break; // ���X�`��
                    }
                }
            }

            // �p�G��e��m�S���ĤH�B�l�u�M�Ĥ�l�u�Aø�s���a
            if (!drawn && i == height - 1 && j == playerX) {
                oss << player; // �p�G��e��m�O���a�Aø�s���a
                drawn = true; // �аO�wø�s
            }

            // �p�G��e��m���򳣨S���Aø�s�Ů�
            if (!drawn) oss << ' ';

            // ø�s�k�����
            if (j == width - 1) oss << border;
        }
        oss << endl; // ����
    }

    // ø�s�������
    for (int i = 0; i < width + 2; i++) oss << border;
    oss << endl;

    // ø�s���ƩM���ūH��
    oss << "Score: " << score << "  Level: " << level << endl;

    // �N���Ц�m�]�m��(0, 0)�A�H�K��s��ӱ���x���e
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << oss.str(); // ��X�r�Ŧ�y�������e
}

// input()��ơA�Ω�B�z���a��J
void Game::input() {
    if (_kbhit()) { // �p�G����L��J
        char key = _getch(); // �������
        if (key == -32) { // �p�G�O�S�����A�~��Ū��
            key = _getch();
        }
        switch (key) {
            case 75: // ���b�Y��
                if (playerX > 0) playerX -= 1; // ���ʪ��a�쥪��
                break;
            case 77: // �k�b�Y��
                if (playerX < width - 1) playerX += 1; // ���ʪ��a��k��
                break;
            case 32: // �Ů���
                bullets.push_back({height - 2, playerX}); // �o�g�l�u
                break;
        }
    }
}

// logic()��ơA�Ω��s�C���޿�
void Game::logic() {
    // ��s�l�u��m
    for (auto &bulletPos : bullets) {
        bulletPos.first--; // �l�u�V�W����
    }

    // �R���̹��~���l�u
    bullets.erase(remove_if(bullets.begin(), bullets.end(),
        [this](const std::pair<int, int> &bulletPos) {
            return bulletPos.first < 0; // �p�G�l�u�W�X�̹��W��ɡA�R��
        }),
        bullets.end());

    // �˴��l�u�P�ĤH���I��
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
        bool hit = false; // �����O�_�������ĤH
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
            if (bulletIt->first == enemyIt->first && bulletIt->second == enemyIt->second) {
                score++; // �W�[����
                enemyIt = enemies.erase(enemyIt); // �R���Q�������ĤH
                hit = true; // �аO������
                break; // ���X���`��
            } else {
                ++enemyIt; // �_�h�A�~���ˬd�U�@�ӼĤH
            }
        }
        if (hit) {
            bulletIt = bullets.erase(bulletIt); // �R�������ĤH���l�u
        } else {
            ++bulletIt; // �_�h�A�ˬd�U�@���l�u
        }
    }

    // ��s�Ĥ�l�u��m
    for (auto &enemyBulletPos : enemyBullets) {
        enemyBulletPos.first++; // �Ĥ�l�u�V�U����
    }

    // �R���̹��~���Ĥ�l�u
    enemyBullets.erase(remove_if(enemyBullets.begin(), enemyBullets.end(),
        [this](const std::pair<int, int> &enemyBulletPos) {
            return enemyBulletPos.first >= height; // �p�G�Ĥ�l�u�W�X�̹��U��ɡA�R��
        }),
        enemyBullets.end());

    // �˴��Ĥ�l�u�P���a���I��
    for (const auto &enemyBulletPos : enemyBullets) {
        if (enemyBulletPos.first == height - 1 && enemyBulletPos.second == playerX) {
            gameOver = true; // �p�G�Ĥ�l�u�������a�A�C������
        }
    }

    // �ھڵ����H���ͦ��Ĥ�l�u
    if (rand() % 10 < level) {
        if (!enemies.empty()) { // �p�G�٦��ĤH
            int randomEnemy = rand() % enemies.size(); // �H����ܤ@�ӼĤH
            enemyBullets.push_back({enemies[randomEnemy].first + 1, enemies[randomEnemy].second}); // �q��ܪ��ĤH��m�o�g�l�u
        }
    }

    // �p�G�Ҧ��ĤH���Q�����B�C���������A�i�J�U�@��
    if (enemies.empty() && !gameOver) {
        nextLevel(); // �i�J�U�@��
    }
}

// start()��ơA�Ω�}�l�C��
void Game::start() {
    setup(); // �]�m�C��
    while (!gameOver) { // ��C��������
        draw(); // ø�s�C���ɭ�
        input(); // �B�z���a��J
        logic(); // ��s�C���޿�
        Sleep(100); // �C���t�ױ���
    }

    // �C�������A��ܤ��ƩM����
    cout << "Game Over! Your score is: " << score << "  Level: " << level << endl;

    // �K�[���a���ƨ�PlayerManager
    playerManager.addPlayerScore(playerManager.getCurrentPlayerID(), score);

    // ��_����x�������
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
