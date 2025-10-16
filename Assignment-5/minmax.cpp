#include <bits/stdc++.h>
using namespace std;

const char PLAYER = 'X'; // Human
const char AI = 'O';     // Computer

// Function to print the board
void printBoard(vector<char> &board) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << board[i] << " ";
        if ((i + 1) % 3 == 0) cout << "\n";
    }
    cout << "\n";
}

// Check winner
char checkWinner(vector<char> &b) {
    int winPatterns[8][3] = {
        {0,1,2},{3,4,5},{6,7,8}, // rows
        {0,3,6},{1,4,7},{2,5,8}, // cols
        {0,4,8},{2,4,6}          // diagonals
    };
    for (auto &p : winPatterns) {
        if (b[p[0]] != '-' && b[p[0]] == b[p[1]] && b[p[1]] == b[p[2]])
            return b[p[0]];
    }
    return '-';
}

// Check if moves left
bool movesLeft(vector<char> &board) {
    return find(board.begin(), board.end(), '-') != board.end();
}

// Minimax function
int minimax(vector<char> &board, bool isMaximizing) {
    char winner = checkWinner(board);
    if (winner == AI) return +10;
    if (winner == PLAYER) return -10;
    if (!movesLeft(board)) return 0;

    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == '-') {
                board[i] = AI;
                best = max(best, minimax(board, false));
                board[i] = '-';
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == '-') {
                board[i] = PLAYER;
                best = min(best, minimax(board, true));
                board[i] = '-';
            }
        }
        return best;
    }
}

// Find best move for AI
int findBestMove(vector<char> &board) {
    int bestVal = -1000, bestMove = -1;
    for (int i = 0; i < 9; i++) {
        if (board[i] == '-') {
            board[i] = AI;
            int moveVal = minimax(board, false);
            board[i] = '-';
            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

// Main
int main() {
    vector<char> board(9, '-'); // empty board

    cout << "Tic-Tac-Toe using Minimax\n";
    printBoard(board);

    while (true) {
        int move;
        cout << "Enter your move (0-8): ";
        cin >> move;
        if (board[move] == '-') {
            board[move] = PLAYER;
        } else {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        printBoard(board);

        if (checkWinner(board) == PLAYER) {
            cout << "You win!\n";
            break;
        }
        if (!movesLeft(board)) {
            cout << "Draw!\n";
            break;
        }

        int aiMove = findBestMove(board);
        board[aiMove] = AI;
        cout << "AI chooses: " << aiMove << endl;
        printBoard(board);

        if (checkWinner(board) == AI) {
            cout << "AI wins!\n";
            break;
        }
        if (!movesLeft(board)) {
            cout << "Draw!\n";
            break;
        }
    }
    return 0;
}