#include <bits/stdc++.h>
#include <conio.h>

using namespace std;

int highScore = 0;

const wchar_t SNAKE_BODY = 0x2588;
const wchar_t FOOD       = 0x25A0;
const wchar_t EMPTY      = L' ';
const wchar_t BORDER     = 0x2593;

const int GRID_SIZE = 20;

void clearScreen() {
    system("cls");
}

void enableUnicode() {
    setlocale(LC_ALL, "");
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

        if (direction == 'U')      newHead.first--;
        else if (direction == 'D') newHead.first++;
        else if (direction == 'L') newHead.second--;
        else if (direction == 'R') newHead.second++;

        body.insert(body.begin(), newHead);
        if (!grow) {
            body.pop_back();
        }
    }

    bool checkCollision() {
        pair<int, int> head = body[0];
        if (head.first < 0 || head.first >= GRID_SIZE ||
            head.second < 0 || head.second >= GRID_SIZE) {
            return true;
        }
        for (size_t i = 1; i < body.size(); i++) {
            if (body[i] == head) {
                return true;
            }
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
            food.first  = rand() % GRID_SIZE;
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
                if (i == 0 || i == GRID_SIZE + 1 ||
                    j == 0 || j == GRID_SIZE + 1) {
                    wcout << BORDER << BORDER;
                } else {
                    bool isSnake = false;
                    for (auto segment : snake.body) {
                        if (segment.first == i - 1 && segment.second == j - 1) {
                            wcout << SNAKE_BODY << SNAKE_BODY;
                            isSnake = true;
                            break;
                        }
                    }
                    if (!isSnake) {
                        if (food.first == i - 1 && food.second == j - 1) {
                            wcout << FOOD << FOOD;
                        } else {
                            wcout << EMPTY << EMPTY;
                        }
                    }
                }
            }
            wcout << L"\n";
        }
        wcout << L"\nScore: " << score
              << L"   High Score: " << highScore;
    }

    void handleInput() {
        if (_kbhit()) {
            char key = _getch();

            if ((key == 'w' || key == 'W') && snake.direction != 'D') snake.direction = 'U';
            else if ((key == 's' || key == 'S') && snake.direction != 'U') snake.direction = 'D';
            else if ((key == 'a' || key == 'A') && snake.direction != 'R') snake.direction = 'L';
            else if ((key == 'd' || key == 'D') && snake.direction != 'L') snake.direction = 'R';
        }
    }

    void update() {
        handleInput();

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

        if (score > highScore) {
            highScore = score;
        }

        cout << "#############################################\n";
        cout << "#                                           #\n";
        cout << "#                GAME OVER                  #\n";
        cout << "#                                           #\n";
        cout << "#############################################\n";
        cout << "\nFinal Score: " << score << endl;
        cout << "High Score: " << highScore << endl;
        cout << "Press R to restart or E to exit...\n";

        while (true) {
            char choice = _getch();
            if (choice == 'r' || choice == 'R') {
                return true;
            } else if (choice == 'e' || choice == 'E') {
                return false;
            } else {
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
    _getch();
}

void delay() {
    for (volatile long long i = 0; i < 100000000; i++);
}

int main() {
    enableUnicode();
    srand(time(0));

    showStartScreen();
    Game game;

    while (true) {
        while (!game.gameOver) {
            game.update();
            delay();
        }

        if (!game.gameOverScreen()) {
            break;
        }

        game.resetGame();
    }

    return 0;
}
