#include <iostream>
#include "player.h"
#include "game.h"

using namespace std;

void mainMenu(PlayerManager& playerManager) {
    int choice;
    do {
        cout << "\nPlayer Management System\n";
        cout << "1. Enter Player ID\n";
        cout << "2. Search Player ID\n";
        cout << "3. Print Score Ranking\n";
        cout << "4. Delete Player ID\n";
        cout << "5. Start the Game\n";
        cout << "6. Exit\n";
        cout << "Please choose an operation: ";
        std::cout << "\n";  // 添加空行

        cin >> choice;
        switch (choice) {
            case 1:
                {
                    string id;
                    cout << "Enter Player ID: ";
                    cin >> id;
                    playerManager.addPlayer(id);
                    playerManager.setCurrentPlayerID(id);
                }
                break;
            case 2:
                {
                    string id;
                    cout << "Enter Player ID to search: ";
                    cin >> id;
                    playerManager.searchPlayer(id);
                }
                break;
            case 3:
                playerManager.printScoreRanking();
                break;
            case 4:
                {
                    string id;
                    cout << "Enter Player ID to delete: ";
                    cin >> id;
                    playerManager.deletePlayer(id);
                }
                break;
            case 5:
                {
                    if (playerManager.getCurrentPlayerID().empty()) {
                        cout << "Please enter a player ID first.\n";
                    } else {
                        Game game;
                        game.start();
                    }
                }
                break;
            case 6:
                playerManager.savePlayers();
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

int main() {
    PlayerManager playerManager;
    mainMenu(playerManager);
    return 0;
}
