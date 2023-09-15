#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>
using namespace std;

class Player
{
public:
    Player(string name) : name(name), position(0) {}

    void move(int steps)
    {
        position += steps;
    }

    int getPosition() const
    {
        return position;
    }

    string getName() const
    {
        return name;
    }

private:
    string name;
    int position;
};

class Board
{
public:
    Board(int size) : size(size), cells(size * size, 0) {}

    void addSnakeOrLadder(int start, int end)
    {
        if (start >= 0 && start < size * size && end >= 0 && end < size * size)
        {
            cells[start] = end;
        }
    }

    int getNextPosition(int currentPosition, int steps) const
    {
        int nextPosition = currentPosition + steps;
        if (nextPosition >= size * size - 1)
        {
            return size * size - 1; // End of the board. Winning Position!
        }
        if (cells[nextPosition] != 0)
        {
            // Check if the next position is a snake or a ladder
            nextPosition = cells[nextPosition];
        }
        return nextPosition;
    }

    int getSize() const
    {
        return size;
    }

private:
    int size;
    vector<int> cells; // Represents snakes and ladders
};

class SnakeAndLaddersGame
{
public:
    SnakeAndLaddersGame(int boardSize, int numPlayers)
        : board(boardSize), currentPlayer(0)
    {
        for (int i = 1; i <= numPlayers; i++)
        {
            cout << "Enter the name of Player " << i << ": ";
            string playerName;
            cin >> playerName;
            players.push_back(Player(playerName));
        }
        srand(time(0)); // Seed for random dice rolls
    }

    void info_snakes_ladders()
    {
        // Prompt the user to add snakes and ladders
        int numSnakes, numLadders;
        cout << "Enter the number of snakes: ";
        cin >> numSnakes;
        cout << "Enter the number of ladders: ";
        cin >> numLadders;

        set<int> usedPositions; // To track used positions

        for (int i = 0; i < numSnakes; i++)
        {
            int start, end;
            while (true)
            {
                cout << "Enter the start and end positions of Snake " << i + 1 << ": ";
                cin >> start >> end;
                if (start >= 2 && start <= 99 && end >= 1 && end <= 98 && usedPositions.count(start) == 0 && usedPositions.count(end) == 0 && start > end)
                {
                    usedPositions.insert(start);
                    usedPositions.insert(end);
                    board.addSnakeOrLadder(start, end);
                    break;
                }
                else
                {
                    cout << "Invalid positions or positions already used. Please try again." << endl;
                }
            }
        }

        for (int i = 0; i < numLadders; i++)
        {
            int start, end;
            while (true)
            {
                cout << "Enter the start and end positions of Ladder " << i + 1 << ": ";
                cin >> start >> end;
                if (start >= 2 && start <= 98 && end >= 3 && end <= 99 && usedPositions.count(start) == 0 && usedPositions.count(end) == 0 && start < end)
                {
                    usedPositions.insert(start);
                    usedPositions.insert(end);
                    board.addSnakeOrLadder(start, end);
                    break;
                }
                else
                {
                    cout << "Invalid positions or positions already used. Please try again." << endl;
                }
            }
        }
    }

    void play()
    {
        while (true)
        {
            Player &currentPlayerObj = players[currentPlayer];
            int diceRoll = rand() % 6 + 1; // Simulate a dice roll
            cout << currentPlayerObj.getName() << " rolled a " << diceRoll << endl;
            int newPosition = board.getNextPosition(currentPlayerObj.getPosition(), diceRoll);

            if (newPosition > board.getSize() * board.getSize() - 1)
            {
                cout << currentPlayerObj.getName() << " is at position " << currentPlayerObj.getPosition() << endl;
            }
            else
            {
                currentPlayerObj.move(newPosition - currentPlayerObj.getPosition());
                cout << currentPlayerObj.getName() << " is now at position " << newPosition << endl;
            }

            if (newPosition == board.getSize() * board.getSize() - 1)
            {
                cout << currentPlayerObj.getName() << " wins!" << endl;
                break;
            }

            currentPlayer = (currentPlayer + 1) % players.size();
        }
    }

private:
    Board board;
    vector<Player> players;
    int currentPlayer;
};

int main()
{
    int boardSize = 10;
    int numPlayers = 2;
    cout << "****************************************************************************" << endl;
    cout << "WELCOME" << endl;
    cout << "While entering Snakes positions, make sure to enter greater value first." << endl;
    cout << "While entering Ladders positions, make sure to enter smaller value first." << endl;
    cout << endl;

    SnakeAndLaddersGame game(boardSize, numPlayers);
    game.info_snakes_ladders();
    game.play();

    return 0;
}
