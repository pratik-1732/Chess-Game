# Chess Game

## Overview

The Chess Game project is a C++ implementation of a basic text-based chess game. It allows two players to make moves by inputting coordinates on a virtual chessboard. The program implements the standard rules of chess using object-oriented programming concepts, with classes representing different chess pieces and a board representation.

## Features

- **Text-Based Interface:** Players interact with the game through a command-line interface (CLI) by inputting coordinates to make moves.
- **Chess Piece Classes:** Utilizes classes for each type of chess piece (e.g., Pawn, Knight, Bishop, Rook, Queen, King) to manage movement and rules specific to each piece.
- **Board Representation:** Implements a virtual chessboard using data structures like arrays or matrices to maintain the state of the game and validate moves.
- **Turn-Based Gameplay:** Alternates turns between two players, validating moves according to the rules of chess (e.g., legal moves, check, checkmate).
- **Game State Management:** Tracks game progress, including check, checkmate, stalemate conditions, and captures.

## Implementation Details

### Classes and Responsibilities

- **Piece Class Hierarchy:** Base class for all chess pieces with derived classes implementing specific piece behaviors and movements.
- **Board Class:** Manages the chessboard state, including initializing the board, validating moves, and checking game conditions.
- **Player Class:** Represents each player in the game, managing their moves and interactions with the board.

### Rules Enforcement

- Implements standard chess rules such as castling, pawn promotion, en passant, and special conditions for check and checkmate.
- Handles edge cases and error conditions like invalid input, illegal moves, and game-ending scenarios.

## Installation and Usage

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/pratik-1732/Chess-Game.git
   ```

2. **Navigate to the Project Directory:**
   ```bash
   cd chess-game
   ```

3. **Compile the Program:**
   Ensure you have a C++ compiler installed that supports C++11 or higher.
   ```bash
   g++ -o chess_game main.cpp
   ```

4. **Run the Program:**
   ```bash
   ./chess_game
   ```

5. **Follow On-Screen Instructions:**
   - Use standard chess notation (e.g., A1, B2) to specify moves for each player.
   - The game will validate moves, update the board state, and announce check, checkmate, or stalemate conditions.

## Contribution

Contributions are welcome! Here are some ideas for contributions:

- Implement additional chess variants or advanced rules (e.g., chess960, three-check chess).
- Improve the user interface with ASCII art for the chess pieces and board visualization.
- Optimize move validation algorithms and board state management.
- Add support for saving and loading game states.

If you'd like to contribute, please fork the repository and create a pull request. Feel free to open an issue to discuss any new features or improvements.
