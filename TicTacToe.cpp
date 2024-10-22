#include <iostream>
#include <vector>

using namespace std;

class TicTacToe
{
private:
    vector<vector<char>> board;
    char currentPlayer;

public:
    TicTacToe()
    {
        board = vector<vector<char>>(3, vector<char>(3, ' '));
        currentPlayer = 'X';
    }

    void displayBoard()
    {
        cout << "  0 1 2\n";
        for (int i = 0; i < 3; ++i)
        {
            cout << i << " ";
            for (int j = 0; j < 3; ++j)
            {
                cout << board[i][j];
                if (j < 2)
                    cout << "|";
            }
            cout << "\n";
            if (i < 2)
                cout << "  -----\n";
        }
    }

    bool checkWin()
    {
        for (int i = 0; i < 3; ++i)
        {
            if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
                (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer))
            {
                return true;
            }
        }
        if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
            (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer))
        {
            return true;
        }
        return false;
    }

    bool checkDraw()
    {
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                if (board[i][j] == ' ')
                    return false;
            }
        }
        return true;
    }

    void play()
    {
        int row, col;
        while (true)
        {
            displayBoard();
            cout << "Player " << currentPlayer << ", enter your move (row and column): ";
            cin >> row >> col;

            if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ')
            {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            board[row][col] = currentPlayer;

            if (checkWin())
            {
                displayBoard();
                cout << "Player " << currentPlayer << " wins!\n";
                break;
            }
            else if (checkDraw())
            {
                displayBoard();
                cout << "It's a draw!\n";
                break;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
};

int main()
{
    TicTacToe game;
    game.play();
    return 0;
}