#include "game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

void Game::start() {
    // �C���޿�
    std::cout << "Game started!\n";

    // ²�檺�C���`���ܨ�
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'q') {
                break; // �� q �h�X�C��
            }
            // �B�z��L����
        }
        Sleep(100); // �����C���`������
    }

    std::cout << "Game ended.\n";
}
