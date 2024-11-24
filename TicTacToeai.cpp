#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> board(3, vector<char>(3, ' '));
char currentPlayer = 'X';

void displayBoard()
{
    cout << "  0 1 2\n";
    for (int i = 0; i < 3; ++i)
    {
        cout << i << " ";
        for (int j = 0; j < 3; ++j)
        {
            cout << board[i][j] << (j < 2 ? "|" : "");
        }
        cout << "\n"
             << (i < 2 ? "  -----\n" : "");
    }
}

bool isWin(char player)
{
    for (int i = 0; i < 3; ++i)
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
           (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

bool isDraw()
{
    for (auto &row : board)
        for (char cell : row)
            if (cell == ' ')
                return false;
    return true;
}

int minimax(bool isMaximizing)
{
    if (isWin('O'))
        return 1;
    if (isWin('X'))
        return -1;
    if (isDraw())
        return 0;

    int bestScore = isMaximizing ? -1000 : 1000;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = isMaximizing ? 'O' : 'X';
                int score = minimax(!isMaximizing);
                board[i][j] = ' ';
                bestScore = isMaximizing ? max(score, bestScore) : min(score, bestScore);
            }
        }
    }
    return bestScore;
}

pair<int, int> findBestMove()
{
    int bestScore = -1000;
    pair<int, int> bestMove = {-1, -1};
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                int score = minimax(false);
                board[i][j] = ' ';
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

void play()
{
    while (true)
    {
        displayBoard();
        if (currentPlayer == 'X')
        {
            int row, col;
            cout << "Player X, enter your move (row and column): ";
            cin >> row >> col;
            if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ')
            {
                cout << "Invalid move! Try again.\n";
                continue;
            }
            board[row][col] = 'X';
        }
        else
        {
            cout << "AI is making a move...\n";
            auto [row, col] = findBestMove();
            board[row][col] = 'O';
        }

        if (isWin(currentPlayer))
        {
            displayBoard();
            cout << "Player " << currentPlayer << " wins!\n";
            break;
        }
        if (isDraw())
        {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main()
{
    play();
    return 0;
}