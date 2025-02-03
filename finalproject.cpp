#include <bits/stdc++.h>
#include <conio.h>  // For _kbhit() and _getch()


using namespace std;

// Unicode characters for rendering
const wchar_t SNAKE_BODY = 0x2588;  // Full Block '█'
const wchar_t FOOD = 0x25A0;        // Black Square '■'
const wchar_t EMPTY = L' ';         // Empty space
const wchar_t BORDER = 0x2593;      // Dark Shade '▓'

const int GRID_SIZE = 20;

// Function to clear the screen
void clearScreen() {
    system("cls");  // Clear screen for Windows
}

// Function to enable Unicode output in the console
void enableUnicode() {
    setlocale(LC_ALL, "");  // Enable Unicode output
}

class Snake {
public:
    vector<pair<int, int>> body;
    char direction;

    Snake() {
        body.push_back({GRID_SIZE / 2, GRID_SIZE / 2});
        body.push_back({GRID_SIZE / 2, GRID_SIZE / 2 - 1});
        body.push_back({GRID_SIZE / 2, GRID_SIZE / 2 - 2});
        direction = 'R';
    }

    void move(bool grow) {
        pair<int, int> newHead = body[0];

        if (direction == 'U') newHead.first--;
        else if (direction == 'D') newHead.first++;
        else if (direction == 'L') newHead.second--;
        else if (direction == 'R') newHead.second++;

        body.insert(body.begin(), newHead);
        if (!grow) body.pop_back();
    }

    bool checkCollision() {
        pair<int, int> head = body[0];
        if (head.first < 0 || head.first >= GRID_SIZE || head.second < 0 || head.second >= GRID_SIZE) {
            return true;
        }
        for (size_t i = 1; i < body.size(); i++) {
            if (body[i] == head) return true;
        }
        return false;
    }
};

class Game {
public:
    Snake snake;
    pair<int, int> food;
    int score;
    bool gameOver;

    Game() {
        score = 0;
        gameOver = false;
        generateFood();
    }

    void generateFood() {
        bool validPosition = false;
        while (!validPosition) {
            food.first = rand() % GRID_SIZE;
            food.second = rand() % GRID_SIZE;
            validPosition = true;
            for (auto segment : snake.body) {
                if (segment == food) {
                    validPosition = false;
                    break;
                }
            }
        }
    }

    void drawBoard() {
        clearScreen();
        wcout << L"\n";
        for (int i = 0; i <= GRID_SIZE + 1; ++i) {
            for (int j = 0; j <= GRID_SIZE + 1; ++j) {
                if (i == 0 || i == GRID_SIZE + 1 || j == 0 || j == GRID_SIZE + 1) {  
                    wcout << BORDER << BORDER;  // Draw border
                } else {
                    bool isSnake = false;
                    for (auto segment : snake.body) {
                        if (segment.first == i - 1 && segment.second == j - 1) {
                            wcout << SNAKE_BODY << SNAKE_BODY;  // Draw snake
                            isSnake = true;
                            break;
                        }
                    }
                    if (!isSnake) {
                        if (food.first == i - 1 && food.second == j - 1) wcout << FOOD << FOOD;  // Draw food
                        else wcout << EMPTY << EMPTY;
                    }
                }
            }
            wcout << L"\n";
        }
        wcout << L"\nScore: " << score;
    }

    void handleInput() {
        if (_kbhit()) {  // Check if a key was pressed
            char key = _getch();  // Get the key press without waiting for Enter

            if ((key == 'w' || key == 'W') && snake.direction != 'D') snake.direction = 'U';
            else if ((key == 's' || key == 'S') && snake.direction != 'U') snake.direction = 'D';
            else if ((key == 'a' || key == 'A') && snake.direction != 'R') snake.direction = 'L';
            else if ((key == 'd' || key == 'D') && snake.direction != 'L') snake.direction = 'R';
        }
    }

    void update() {
        handleInput();  // Read input if available

        bool grow = (snake.body[0] == food);
        if (grow) {
            score++;
            generateFood();
        }

        snake.move(grow);
        drawBoard();

        if (snake.checkCollision()) {
            if (gameOverScreen()) {
                resetGame();
            } else {
                gameOver = true;
            }
        }
    }

    bool gameOverScreen() {
    system("cls");
    cout << "#############################################\n";
    cout << "#                                           #\n";
    cout << "#                GAME OVER                  #\n";
    cout << "#                                           #\n";
    cout << "#############################################\n";
    cout << "\nFinal Score: " << score << endl;
    cout << "Press R to restart or E to exit...\n";

    while (true) {  // Loop until a valid choice is made
        char choice = _getch();  // Wait for key press

        if (choice == 'r' || choice == 'R') {
            return true;  // Restart the game
        } else if (choice == 'e' || choice == 'E') {
            return false;  // Exit the game
        } else {
            // If the key is not 'R' or 'E', ignore it and wait for a valid key
            continue;
        }
    }
}

    void resetGame() {
        snake = Snake();
        score = 0;
        gameOver = false;
        generateFood();
    }
};

void showStartScreen() {
    wcout << L"#############################################\n";
    wcout << L"#                                           #\n";
    wcout << L"#            WELCOME TO SNAKE GAME          #\n";
    wcout << L"#                                           #\n";
    wcout << L"#############################################\n";
    wcout << L"\nControls: W = Up, S = Down, A = Left, D = Right\n";
    wcout << L"Press any key to start...";
    _getch();  // Wait for key press
}

void delay() {
    for (volatile long long i = 0; i < 100000000; i++);  // Adjust for game speed
}

int main() {
    enableUnicode(); // Enable Unicode output in console
    srand(time(0));

    showStartScreen();
    Game game;

    while (true) {
        while (!game.gameOver) {
            game.update();
            delay();  // Controls game speed
        }

        if (!game.gameOverScreen()) {
            break;  // Exit the game if the player does not restart
        }

        game.resetGame();  // Restart the game
    }

    return 0;
}