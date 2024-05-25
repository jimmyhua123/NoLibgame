#include "game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

void Game::start() {
    // 遊戲邏輯
    std::cout << "Game started!\n";

    // 簡單的遊戲循環示例
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'q') {
                break; // 按 q 退出遊戲
            }
            // 處理其他按鍵
        }
        Sleep(100); // 模擬遊戲循環延遲
    }

    std::cout << "Game ended.\n";
}
