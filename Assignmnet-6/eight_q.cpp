#include <bits/stdc++.h>
using namespace std;

#define N 8  // Board size

// Function to print the chessboard
void printBoard(vector<int> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j) cout << "Q ";
            else cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

// Check if placing queen at row r, col c is safe
bool isSafe(vector<int> &board, int row, int col) {
    for (int i = 0; i < row; i++) {
        int qCol = board[i];
        if (qCol == col || abs(qCol - col) == abs(i - row))
            return false;
    }
    return true;
}

// Backtracking function
bool solveNQueens(vector<int> &board, int row) {
    if (row == N) {
        printBoard(board);
        return true; // Found a solution
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            if (solveNQueens(board, row + 1)) return true;
            board[row] = -1; // backtrack
        }
    }
    return false;
}

int main() {
    vector<int> board(N, -1); // board[i] = column of queen in row i
    if (!solveNQueens(board, 0))
        cout << "No solution exists." << endl;
    return 0;
}
