#include <iostream>
using namespace std;

class TicTacToe {
private:
    char board[9];
    char currentPlayer;

public:
    TicTacToe() {
        resetBoard();
        currentPlayer = 'X';
    }

    void resetBoard() {
        for (int i = 0; i < 9; ++i)
            board[i] = '1' + i;
    }

    void displayBoard() {
        cout << "\n== Tic Tac Toe == CSIE@CGU" << endl;
        cout << "Player 1 (X)  -  Player 2 (O)\n\n";

        for (int i = 0; i < 9; i += 3) {
            cout << " " << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << endl;
            if (i < 6) cout << "-----------" << endl;
        }
        cout << endl;
    }

    bool makeMove(int pos) {
        if (pos < 1 || pos > 9) {
            cout << "輸入錯誤，請輸入 1~9 的數字。\n";
            return false;
        }
        if (board[pos - 1] == 'X' || board[pos - 1] == 'O') {
            cout << "該位置已被佔用，請重新輸入。\n";
            return false;
        }

        board[pos - 1] = currentPlayer;
        return true;
    }

    bool checkWin() {
        int wins[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // 橫排
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // 直排
            {0, 4, 8}, {2, 4, 6}             // 斜線
        };

        for (auto &w : wins) {
            if (board[w[0]] == currentPlayer &&
                board[w[1]] == currentPlayer &&
                board[w[2]] == currentPlayer)
                return true;
        }
        return false;
    }

    bool isDraw() {
        for (int i = 0; i < 9; ++i) {
            if (board[i] != 'X' && board[i] != 'O')
                return false;
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    void play() {
        int move;
        displayBoard();

        while (true) {
            cout << "Player " << (currentPlayer == 'X' ? "1" : "2") << "，請輸入 [1~9] 的數字：";
            cin >> move;

            if (!cin) { // 錯誤輸入處理（如字母）
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "輸入錯誤，請重新輸入數字。\n";
                continue;
            }

            if (!makeMove(move)) {
                displayBoard();
                continue;
            }

            displayBoard();

            if (checkWin()) {
                cout << "==> Player " << (currentPlayer == 'X' ? "1" : "2") << " win" << endl;
                break;
            }

            if (isDraw()) {
                cout << "==> Game draw" << endl;
                break;
            }

            switchPlayer();
        }
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}
