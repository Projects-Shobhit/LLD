#include <iostream>
#include <limits>
using namespace std;

class TicTacToe
{
private:
    char board[3][3];
    char currentPlayer;
    int moveCount;
    string player1Name;
    string player2Name;

    bool checkWin()
    {
        // Check rows, columns, and diagonals for a win
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer)
            {
                return true;
            }
            if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)
            {
                return true;
            }
        }
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer)
        {
            return true;
        }
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)
        {
            return true;
        }

        return false;
    }

    bool isTie()
    {
        return moveCount == 9;
    }

public:
    int c = 48;
    TicTacToe() : currentPlayer('X'), moveCount(0)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = (char)++c;
            }
        }
    }

    void displayBoard()
    {
        cout << "\n\n";
        cout << "-------------" << endl;
        cout << "| ";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << board[i][j] << " | ";
            }
            cout << endl;
            cout << "-------------" << endl;
            if (i != 2)
                cout << "| ";
        }
        cout << endl;
    }

    bool makeMove(int cell)
    {
        int row = (cell - 1) / 3;
        int col = (cell - 1) % 3;

        if (row < 0 || row >= 3 || col < 0 || col >= 3 || (!isdigit(board[row][col])))
        {
            cout << "Invalid move. Please try again." << endl;
            return false;
        }

        board[row][col] = currentPlayer;
        moveCount++;
        return true;
    }

    void play()
    {
        getPlayerNames();

        while (true)
        {
            displayBoard();
            cout << currentPlayer << "'s turn (" << (currentPlayer == 'X' ? player1Name : player2Name) << ")" << endl;

            int cell;
            while (true)
            {
                cout << "Enter a cell number (1-9) to mark your input: ";
                if (cin >> cell && cell >= 1 && cell <= 9)
                {
                    if (makeMove(cell))
                    {
                        break;
                    }
                }
                else
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please try again." << endl;
                }
            }

            if (checkWin())
            {
                displayBoard();
                cout << currentPlayer << " (" << (currentPlayer == 'X' ? player1Name : player2Name) << ") wins!" << endl;
                break;
            }
            else if (isTie())
            {
                displayBoard();
                cout << "It's a tie!" << endl;
                break;
            }

            currentPlayer = (currentPlayer == 'X' ? 'O' : 'X');
        }
    }

    void getPlayerNames()
    {
        cout << "Enter the name of Player 1 (X): ";
        cin >> player1Name;
        cout << "Enter the name of Player 2 (O): ";
        cin >> player2Name;
    }
};

int main()
{
    TicTacToe game;
    game.play();

    return 0;
}
