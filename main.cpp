#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

class TicTacToe {
private:
    char board[3][3];
    string player1;
    string player2;
    char currentToken;
    int p1Score;
    int p2Score;
    int tiesCount;
    bool vsAI;

    void clearScreen() const {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void drawBoard() const {
        cout << "\n";
        cout << "  ====================================\n";
        cout << "           TIC-TAC-TOE ARENA          \n";
        cout << "  ====================================\n";
        cout << "   " << player1 << " (X): " << p1Score 
             << "  |  " << player2 << " (O): " << p2Score 
             << "  |  Draws: " << tiesCount << "\n";
        cout << "  ------------------------------------\n\n";

        cout << "             |     |     \n";
        cout << "          " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  \n";
        cout << "        _____|_____|_____\n";
        cout << "             |     |     \n";
        cout << "          " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  \n";
        cout << "        _____|_____|_____\n";
        cout << "             |     |     \n";
        cout << "          " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  \n";
        cout << "             |     |     \n\n";
    }

    bool isWinner(char token) const {
        // Rows & Columns
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == token && board[i][1] == token && board[i][2] == token) return true;
            if (board[0][i] == token && board[1][i] == token && board[2][i] == token) return true;
        }
        // Diagonals
        if (board[0][0] == token && board[1][1] == token && board[2][2] == token) return true;
        if (board[0][2] == token && board[1][1] == token && board[2][0] == token) return true;

        return false;
    }

    bool isBoardFull() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    return false;
                }
            }
        }
        return true;
    }

    int getAIMove() {
    
        for (int i = 1; i <= 9; i++) {
            int r = (i - 1) / 3;
            int c = (i - 1) % 3;
            if (board[r][c] != 'X' && board[r][c] != 'O') {
                char temp = board[r][c];
                board[r][c] = 'O';
                if (isWinner('O')) {
                    board[r][c] = temp;
                    return i;
                }
                board[r][c] = temp;
            }
        }


        for (int i = 1; i <= 9; i++) {
            int r = (i - 1) / 3;
            int c = (i - 1) % 3;
            if (board[r][c] != 'X' && board[r][c] != 'O') {
                char temp = board[r][c];
                board[r][c] = 'X';
                if (isWinner('X')) {
                    board[r][c] = temp;
                    return i;
                }
                board[r][c] = temp;
            }
        }

        if (board[1][1] == '5') return 5;

       
        for (int i = 1; i <= 9; i++) {
            int r = (i - 1) / 3;
            int c = (i - 1) % 3;
            if (board[r][c] != 'X' && board[r][c] != 'O') {
                return i;
            }
        }
        return 1;
    }

    void makeMove() {
        int cell;
        int r, c;

        if (vsAI && currentToken == 'O') {
            cell = getAIMove();
            r = (cell - 1) / 3;
            c = (cell - 1) % 3;
            board[r][c] = currentToken;
            return;
        }

        while (true) {
            string currentName = (currentToken == 'X') ? player1 : player2;
            cout << currentName << " (" << currentToken << "), choose cell (1-9): ";
            
            if (!(cin >> cell)) {
                cout << "Invalid input! Numbers only.\n\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (cell < 1 || cell > 9) {
                cout << "Choice must be between 1 and 9!\n\n";
                continue;
            }

            r = (cell - 1) / 3;
            c = (cell - 1) % 3;

            if (board[r][c] == 'X' || board[r][c] == 'O') {
                cout << "Cell is already taken! Try another one.\n\n";
                continue;
            }

            board[r][c] = currentToken;
            break;
        }
    }

    void resetRound() {
        char val = '1';
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = val++;
            }
        }
        currentToken = 'X';
    }

public:
    TicTacToe() : p1Score(0), p2Score(0), tiesCount(0), currentToken('X'), vsAI(false) {}

    void setup() {
        clearScreen();
        cout << "=========================================\n";
        cout << "       WELCOME TO TIC-TAC-TOE PRO        \n";
        cout << "=========================================\n\n";
        cout << "Select Game Mode:\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer (AI)\n";
        cout << "Enter choice (1 or 2): ";

        int mode;
        while (!(cin >> mode) || (mode != 1 && mode != 2)) {
            cout << "Invalid selection! Enter 1 or 2: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vsAI = (mode == 2);

        cout << "\nEnter Player 1 name (X): ";
        getline(cin, player1);
        if (player1.empty()) player1 = "Player 1";

        if (vsAI) {
            player2 = "Smart Bot";
        } else {
            cout << "Enter Player 2 name (O): ";
            getline(cin, player2);
            if (player2.empty()) player2 = "Player 2";
        }
    }

    void run() {
        char playAgain;
        do {
            resetRound();

            while (true) {
                clearScreen();
                drawBoard();
                makeMove();

                if (isWinner(currentToken)) {
                    clearScreen();
                    drawBoard();
                    string winner = (currentToken == 'X') ? player1 : player2;
                    cout << "🎉 " << winner << " wins this round!\n\n";
                    
                    if (currentToken == 'X') p1Score++;
                    else p2Score++;
                    break;
                }

                if (isBoardFull()) {
                    clearScreen();
                    drawBoard();
                    cout << "🤝 It's a draw!\n\n";
                    tiesCount++;
                    break;
                }

                currentToken = (currentToken == 'X') ? 'O' : 'X';
            }

            cout << "Play another round? (y/n): ";
            cin >> playAgain;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } while (playAgain == 'y' || playAgain == 'Y');

        clearScreen();
        cout << "=========================================\n";
        cout << "               FINAL STATS               \n";
        cout << "=========================================\n";
        cout << player1 << " Score : " << p1Score << "\n";
        cout << player2 << " Score : " << p2Score << "\n";
        cout << "Draws           : " << tiesCount << "\n";
        cout << "=========================================\n";
        cout << "Thanks for playing! See you next time.\n";
    }
};

int main() {
    TicTacToe game;
    game.setup();
    game.run();
    return 0;
}