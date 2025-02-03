# Snake Game (Terminal-Based)

## Introduction
This is a terminal-based Snake game built using standard C++ features without any external libraries beyond basic input/output functions. The game runs in a Windows console and uses Unicode characters for graphical representation. The snake moves continuously, and the player can change its direction using the keyboard.

## Features
- Terminal-based gameplay without requiring extra graphical libraries
- Continuous snake movement without pressing Enter for each step
- Unicode-based graphics for better visual representation
- Food generation and score tracking
- Collision detection with self and walls
- Game restart and exit options upon game over

## Controls
- `W` - Move Up
- `S` - Move Down
- `A` - Move Left
- `D` - Move Right
- `R` - Restart Game (upon Game Over)
- `E` - Exit Game (upon Game Over)

## How to Run
1. Compile the C++ file using a compiler that supports Windows console applications (e.g., `g++`).
2. Run the compiled executable in a Windows terminal.
3. Control the snake using `W`, `A`, `S`, and `D` keys.
4. Avoid collisions with the walls and yourself to keep playing.
5. Collect food (`■`) to grow and increase your score.
6. Upon game over, press `R` to restart or `E` to exit.

## Data Structure Analysis
- **Snake Representation:** The snake is stored as a `vector<pair<int, int>>` where each element represents a body segment.
- **Movement Handling:** A `char` variable stores the current direction (`U`, `D`, `L`, `R`), and the snake moves automatically in this direction until changed by user input.
- **Food Positioning:** Food is generated randomly within the grid and stored as a `pair<int, int>`.
- **Collision Detection:** The game checks if the snake collides with the walls or itself before updating the state.
- **User Input Handling:** `_kbhit()` and `_getch()` are used to detect and process key inputs without waiting for Enter.

## Improvements and Next Steps
- Implementing difficulty levels with variable speed
- Adding a high-score tracking system
- Improving input handling for smoother gameplay

Enjoy the game! 🚀

