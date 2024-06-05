#include <iostream> // �]�tiostream���Y�ɡA�Ω��J��X
#include "player.h" // �]�tplayer.h���Y�ɡA�w�qPlayerManager��
#include "game.h" // �]�tgame.h���Y�ɡA�w�qGame��

using namespace std; // �ϥμзǩR�W�Ŷ�

// �w�q�D����ơA�Ω󪱮a�޲z�M�ҰʹC��
void mainMenu(PlayerManager& playerManager) {
    int choice; // �Ω�s�x�Τ���
    do {
        // ��ܵ��ﶵ
        cout << "\nPlayer Management System\n";
        cout << "1. Enter Player ID\n";
        cout << "2. Search Player ID\n";
        cout << "3. Print Score Ranking\n";
        cout << "4. Delete Player ID\n";
        cout << "5. Start the Game\n";
        cout << "6. Exit\n";
        cout << "Please choose an operation: ";
        std::cout << "\n";  // ����

        cin >> choice; // ����Τ��J
        switch (choice) { // �ھڥΤ��J��������ާ@
            case 1: // �ﶵ1�G��J���aID
                {
                    string id; // �Ω�s�x���aID
                    cout << "Enter Player ID: ";
                    cin >> id; // ������aID
                    playerManager.addPlayer(id); // �K�[���a
                    playerManager.setCurrentPlayerID(id); // �]�m��e���aID
                }
                break;
            case 2: // �ﶵ2�G�j�����aID
                {
                    string id; // �Ω�s�x�n�j�������aID
                    cout << "Enter Player ID to search: ";
                    cin >> id; // ����n�j�������aID
                    playerManager.searchPlayer(id); // �j�����a
                }
                break;
            case 3: // �ﶵ3�G���L���ƱƦW
                playerManager.printScoreRanking(); // ���L���ƱƦW
                break;
            case 4: // �ﶵ4�G�R�����aID
                {
                    string id; // �Ω�s�x�n�R�������aID
                    cout << "Enter Player ID to delete: ";
                    cin >> id; // ����n�R�������aID
                    playerManager.deletePlayer(id); // �R�����a
                }
                break;
            case 5: // �ﶵ5�G�}�l�C��
                {
                    if (playerManager.getCurrentPlayerID().empty()) { // �p�G�S���]�m��e���aID
                        cout << "Please enter a Player ID first.\n"; // ���ܥΤ����J���aID
                    } else {
                        Game game(playerManager); // �Ы�Game��H
                        game.start(); // �}�l�C��
                        // �C����������ܵ��ﶵ
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
            case 6: // �ﶵ6�G�h�X
                playerManager.savePlayers(); // �O�s���a�ƾ�
                break;
            default: // �D�k�ﶵ
                cout << "Invalid choice. Please try again.\n"; // ���ܥΤ᭫�s���
        }
    } while (choice != 6); // ��Τ��ܰh�X�ɡA�h�X�`��
}

int main() {
    PlayerManager playerManager; // �Ы�PlayerManager��H
    playerManager.loadPlayers(); // �[�����a�ƾ�
    mainMenu(playerManager); // ��ܥD���
    return 0; // ��^0�A��ܵ{�ǥ��`����
}
