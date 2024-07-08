/*TIC-TAC-TOE AI
Implement an AI agent that plays the classic game of Tic-Tac-Toeagainst a human player. You can use algorithms like Minimax withor without Alpha-Beta Pruning to make the AI player unbeatable.This project will help you understand game theory and basic searchalgorithms*/
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class TicTacToe {
public:
    TicTacToe() {
        board = vector<char>(9, ' ');
        humanPlayer = 'X';
        aiPlayer = 'O';
    }

    void printBoard() {
        cout << " " << board[0] << " | " << board[1] << " | " << board[2] << " " << endl;
        cout << "---+---+---" << endl;
        cout << " " << board[3] << " | " << board[4] << " | " << board[5] << " " << endl;
        cout << "---+---+---" << endl;
        cout << " " << board[6] << " | " << board[7] << " | " << board[8] << " " << endl;
    }

    vector<int> availableMoves() {
        vector<int> moves;
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                moves.push_back(i);
            }
        }
        return moves;
    }

    void makeMove(int index, char player) {
        board[index] = player;
    }

    bool checkWinner(char player) {
        vector<vector<int>> wins = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // rows
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // columns
            {0, 4, 8}, {2, 4, 6}  // diagonals
        };
        for (const auto& win : wins) {
            if (board[win[0]] == player && board[win[1]] == player && board[win[2]] == player) {
                return true;
            }
        }
        return false;
    }

    int evaluate() {
        if (checkWinner(aiPlayer)) {
            return 10;
        } else if (checkWinner(humanPlayer)) {
            return -10;
        } else {
            return 0;
        }
    }

    int minimax(int depth, bool isMaximizing) {
        int score = evaluate();
        if (score == 10 || score == -10) {
            return score;
        }

        if (availableMoves().empty()) {
            return 0;
        }

        if (isMaximizing) {
            int bestScore = numeric_limits<int>::min();
            for (int move : availableMoves()) {
                makeMove(move, aiPlayer);
                int score = minimax(depth + 1, false);
                makeMove(move, ' ');
                bestScore = max(bestScore, score);
            }
            return bestScore;
        } else {
            int bestScore = numeric_limits<int>::max();
            for (int move : availableMoves()) {
                makeMove(move, humanPlayer);
                int score = minimax(depth + 1, true);
                makeMove(move, ' ');
                bestScore = min(bestScore, score);
            }
            return bestScore;
        }
    }

    int alphaBetaPruning(int depth, int alpha, int beta, bool isMaximizing) {
        int score = evaluate();
        if (score == 10 || score == -10) {
            return score;
        }

        if (availableMoves().empty()) {
            return 0;
        }

        if (isMaximizing) {
            int bestScore = numeric_limits<int>::min();
            for (int move : availableMoves()) {
                makeMove(move, aiPlayer);
                int score = alphaBetaPruning(depth + 1, alpha, beta, false);
                makeMove(move, ' ');
                bestScore = max(bestScore, score);
                alpha = max(alpha, bestScore);
                if (beta <= alpha) {
                    break;
                }
            }
            return bestScore;
        } else {
            int bestScore = numeric_limits<int>::max();
            for (int move : availableMoves()) {
                makeMove(move, humanPlayer);
                int score = alphaBetaPruning(depth + 1, alpha, beta, true);
                makeMove(move, ' ');
                bestScore = min(bestScore, score);
                beta = min(beta, bestScore);
                if (beta <= alpha) {
                    break;
                }
            }
            return bestScore;
        }
    }

    int getBestMove() {
        int bestScore = numeric_limits<int>::min();
        int bestMove = -1;
        for (int move : availableMoves()) {
            makeMove(move, aiPlayer);
            int score = alphaBetaPruning(0, numeric_limits<int>::min(), numeric_limits<int>::max(), false);
            makeMove(move, ' ');
            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }
        return bestMove;
    }

    void playGame() {
        cout << "Welcome to Tic-Tac-Toe!" << endl;
        printBoard();

        while (true) {
            // Human player's turn
            cout << "Your turn." << endl;
            while (true) {
                int move;
                cout << "Enter a number (0-8) to make your move: ";
                cin >> move;
                if (move >= 0 && move < 9 && board[move] == ' ') {
                    makeMove(move, humanPlayer);
                    break;
                } else {
                    cout << "That position is already taken. Try again." << endl;
                }
            }
            printBoard();

            // Check for winner
            if (checkWinner(humanPlayer)) {
                cout << "Congratulations! You won!" << endl;
                break;
            } else if (availableMoves().empty()) {
                cout << "It's a tie!" << endl;
                break;
            }

            // AI player's turn
            cout << "AI's turn." << endl;
            int aiMove = getBestMove();
            makeMove(aiMove, aiPlayer);
            cout << "AI moved to position " << aiMove << "." << endl;
            printBoard();

            // Check for winner
            if (checkWinner(aiPlayer)) {
                cout << "AI wins!" << endl;
                break;
            }
        }
    }

private:
    vector<char> board;
    char humanPlayer;
    char aiPlayer;
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}