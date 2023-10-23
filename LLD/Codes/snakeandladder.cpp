#include <bits/stdc++.h>
using namespace std;
class SnakeLadderGame
{
private:
    int boardSize;

    std::vector<std::pair<int, int>> snakes;
    std::vector<std::pair<int, int>> ladders;
    std::vector<std::string> players;
    int currentPlayer;

public:
    SnakeLadderGame(int size) : boardSize(size), currentPlayer(0) {}

    void addSnake(int head, int tail)
    {
        snakes.push_back({head, tail});
    }

    void addLadder(int start, int end)
    {
        ladders.push_back({start, end});
    }

    void addPlayer(const std::string &playerName)
    {
        players.push_back(playerName);
    }

    bool isSnakeOrLadder(int position, int &newPosition)
    {
        for (const auto &snake : snakes)
        {
            if (position == snake.first)
            {
                newPosition = snake.second;
                return true;
            }
        }
        for (const auto &ladder : ladders)
        {
            if (position == ladder.first)
            {
                newPosition = ladder.second;
                return true;
            }
        }
        return false;
    }

    int rollDice()
    {
        return std::rand() % 6 + 1;
    }

    void play()
    {
        int currentPosition[players.size()] = {0};
        int diceRoll;

        while (true)
        {
            for (int i = 0; i < players.size(); ++i)
            {
                diceRoll = rollDice();
                int newPosition = currentPosition[i] + diceRoll;

                if (isSnakeOrLadder(newPosition, newPosition))
                {
                    std::cout << players[i] << " rolled a " << diceRoll << " and moved from " << currentPosition[i] << " to " << newPosition << std::endl;
                }
                else if (newPosition <= boardSize)
                {
                    currentPosition[i] = newPosition;
                    std::cout << players[i] << " rolled a " << diceRoll << " and moved from " << currentPosition[i] - diceRoll << " to " << currentPosition[i] << std::endl;
                }

                if (currentPosition[i] == boardSize)
                {
                    std::cout << "\n"
                              << players[i] << " wins the game" << std::endl;
                    return;
                }
            }
        }
    }
};

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int boardSize;
    std::cout << "Enter the board size: ";
    std::cin >> boardSize;

    SnakeLadderGame game(boardSize);

    int numSnakes;
    std::cout << "Enter the number of snakes: ";
    std::cin >> numSnakes;

    for (int i = 0; i < numSnakes; ++i)
    {
        int head, tail;
        std::cout << "Enter the head and tail positions of snake " << i + 1 << ": ";
        std::cin >> head >> tail;
        game.addSnake(head, tail);
    }

    int numLadders;
    std::cout << "Enter the number of ladders: ";
    std::cin >> numLadders;

    for (int i = 0; i < numLadders; ++i)
    {
        int start, end;
        std::cout << "Enter the start and end positions of ladder " << i + 1 << ": ";
        std::cin >> start >> end;
        game.addLadder(start, end);
    }

    int numPlayers;
    std::cout << "Enter the number of players: ";
    std::cin >> numPlayers;

    for (int i = 0; i < numPlayers; ++i)
    {
        std::string playerName;
        std::cout << "Enter the name of player " << i + 1 << ": ";
        std::cin >> playerName;
        game.addPlayer(playerName);
    }

    game.play();

    return 0;
}
