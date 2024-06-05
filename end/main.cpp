#include <iostream> // 包含iostream標頭檔，用於輸入輸出
#include "player.h" // 包含player.h標頭檔，定義PlayerManager類
#include "game.h" // 包含game.h標頭檔，定義Game類

using namespace std; // 使用標準命名空間

// 定義主菜單函數，用於玩家管理和啟動遊戲
void mainMenu(PlayerManager& playerManager) {
    int choice; // 用於存儲用戶選擇
    do {
        // 顯示菜單選項
        cout << "\nPlayer Management System\n";
        cout << "1. Enter Player ID\n";
        cout << "2. Search Player ID\n";
        cout << "3. Print Score Ranking\n";
        cout << "4. Delete Player ID\n";
        cout << "5. Start the Game\n";
        cout << "6. Exit\n";
        cout << "Please choose an operation: ";
        std::cout << "\n";  // 換行

        cin >> choice; // 獲取用戶輸入
        switch (choice) { // 根據用戶輸入執行對應操作
            case 1: // 選項1：輸入玩家ID
                {
                    string id; // 用於存儲玩家ID
                    cout << "Enter Player ID: ";
                    cin >> id; // 獲取玩家ID
                    playerManager.addPlayer(id); // 添加玩家
                    playerManager.setCurrentPlayerID(id); // 設置當前玩家ID
                }
                break;
            case 2: // 選項2：搜索玩家ID
                {
                    string id; // 用於存儲要搜索的玩家ID
                    cout << "Enter Player ID to search: ";
                    cin >> id; // 獲取要搜索的玩家ID
                    playerManager.searchPlayer(id); // 搜索玩家
                }
                break;
            case 3: // 選項3：打印分數排名
                playerManager.printScoreRanking(); // 打印分數排名
                break;
            case 4: // 選項4：刪除玩家ID
                {
                    string id; // 用於存儲要刪除的玩家ID
                    cout << "Enter Player ID to delete: ";
                    cin >> id; // 獲取要刪除的玩家ID
                    playerManager.deletePlayer(id); // 刪除玩家
                }
                break;
            case 5: // 選項5：開始遊戲
                {
                    if (playerManager.getCurrentPlayerID().empty()) { // 如果沒有設置當前玩家ID
                        cout << "Please enter a Player ID first.\n"; // 提示用戶先輸入玩家ID
                    } else {
                        Game game(playerManager); // 創建Game對象
                        game.start(); // 開始遊戲
                        // 遊戲結束後顯示菜單選項
                        cout << "\nPlayer Management System\n";
                        cout << "1. Enter Player ID\n";
                        cout << "2. Search Player ID\n";
                        cout << "3. Print Score Ranking\n";
                        cout << "4. Delete Player ID\n";
                        cout << "5. Start the Game\n";
                        cout << "6. Exit\n";
                        cout << "Please choose an operation: ";
                    }
                }
                break;
            case 6: // 選項6：退出
                playerManager.savePlayers(); // 保存玩家數據
                break;
            default: // 非法選項
                cout << "Invalid choice. Please try again.\n"; // 提示用戶重新選擇
        }
    } while (choice != 6); // 當用戶選擇退出時，退出循環
}

int main() {
    PlayerManager playerManager; // 創建PlayerManager對象
    playerManager.loadPlayers(); // 加載玩家數據
    mainMenu(playerManager); // 顯示主菜單
    return 0; // 返回0，表示程序正常結束
}
