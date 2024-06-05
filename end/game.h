#ifndef GAME_H // ����ƥ]�t���Y�ɮ�
#define GAME_H // �w�q���Y�ɮק�

#include <iostream> // �]�tiostream���Y�ɡA�Ω��X
#include <vector> // �]�tvector���Y�ɡA�Ω�ʺA�Ʋ�
#include <utility> // �]�tutility���Y�ɡA�Ω�std::pair
#include <ctime> // �]�tctime���Y�ɡA�Ω�ɶ��������
#include <conio.h> // �]�tconio.h�A�Ω�D���릡��L��J
#include <windows.h> // �]�twindows.h�A�Ω�Windows API
#include <sstream> // �]�tsstream���Y�ɡA�Ω�r�Ŧ�y

class PlayerManager; // �e�V�ŧiPlayerManager��

class Game {
public:
    Game(PlayerManager& pm); // Game�����c�y���
    void setup(); // �]�m�C��
    void nextLevel(); // �i�J�U�@��
    void draw(); // ø�s�C���ɭ�
    void input(); // �B�z���a��J
    void logic(); // ��s�C���޿�
    void start(); // �}�l�C��
private:
    const int width = 30; // �C���ϰ�e��
    const int height = 20; // �C���ϰ찪��
    char player = '^'; // ���a�Ÿ�
    char enemy = '@'; // �ĤH�Ÿ�
    char bullet = '|'; // �l�u�Ÿ�
    char enemyBullet = '!'; // �Ĥ�l�u�Ÿ�
    char border = '#'; // ��ɲŸ�
    int playerX; // ���a��m
    std::vector<std::pair<int, int>> enemies; // �ĤH��m�C��
    std::vector<std::pair<int, int>> bullets; // �l�u��m�C��
    std::vector<std::pair<int, int>> enemyBullets; // �Ĥ�l�u��m�C��
    bool gameOver; // �C�������лx
    int score; // ����
    int level; // ����
    PlayerManager& playerManager; // PlayerManager���ޥ�
};

#endif // ����GAME_H������sĶ
