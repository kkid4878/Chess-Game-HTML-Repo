---
marp: false
---
# <center>Software Requirements Specification </center>
<center> EECS 22L - Spring 2025 </center>
<center> Project 1 - Chess Game </center>

---

**Version History**
2025-04-15  v0.0.0  Initial version
2025-04-20  v0.1.0  Added details on game loop and player switching
2025-05-18  v0.4.0  Specified requirement dependencies for Sections 1 and 2
2025-05-29  v0.7.0  Added module API specifications

---

**Client:** Adam West High School, Principal Shepherd
**Project:** Project 1 - Chess Game

--- 

## 0. About this Document
This document defines the behavioral and functional requirements for a terminal-based chess game implemented in C. The project is structured into modular components, each responsible for part of the system's operation. This document specifies the interface and behavior of each function in a given module.

```yaml
ID: REQ-FN-FEAT-0000
    Title___: Chess Game
    Parents_: --
    Children: REQ-FN-MAIN-1001,REQ-FN-MAIN-1002,REQ-FN-MAIN-1003,REQ-FN-MAIN-1004
    Description:
      - A terminal-based chess game implemented in C.
```

---

## 1. System Overview
The chess game runs in a terminal using ASCII graphics. It supports two human players taking turns. The game includes board management, move validation, turn control, and basic rule enforcement. The game can detect check and checkmate conditions. The game is played on an 8x8 board with standard chess pieces. Input is provided through standard input (keyboard), and the display is printed to standard output.

```yaml
REQ-FN-FEAT-1001:
    Title:  Terminal Chess Gameplay
    Parent: REQ-FN-FEAT-0000
    Child:  TBD
    Description: Complete chess game playable in terminal by two human players
```

```yaml
REQ-FN-FEAT-1002:
    Title:  Visuals and Input
    Parent: REQ-FN-FEAT-0000
    Child:  TBD
    Description: Players must see the board and provide moves
```

```yaml
REQ-FN-FEAT-1003:
    Title:  Rule Enforcement
    Parent: REQ-FN-FEAT-0000
    Child:  TBD
    Description: The game must validate and enforce chess rules
```

```yaml
REQ-FN-FEAT-1004:
    Title:  Game Orchestration
    Parent: REQ-FN-FEAT-0000
    Child:  TBD
    Description: The system must manage game flow from start to end
```

---

## 2. Architecture Overview (Proposed)

```
                      ┌────────────┐
                      │  main.c    │
                      └────┬───────┘
                           │
                    ┌──────▼───────┐
                    │  game.c      │
                    └──────┬───────┘
                           │
   ┌────────────┬──────────┼──────────┬──────────────┐
   │            │          │          │              │
┌──▼───┐    ┌────▼────┐ ┌──▼───┐   ┌──▼─────┐   ┌────▼─────┐
│ ui   │    │  check  │ │  io  │   │ player │   │ validator│
└──┬───┘    └────┬────┘ └──┬───┘   └────────┘   └────┬─────┘
   │             │         │                         │
   │             │         │                         │
   ▼             ▼         ▼                         ▼
────────────  ───────────────  ───────────────  ─────────────
   board.c     (Shared Data Layer: 8x8 board state, pieces)
────────────  ───────────────  ───────────────  ─────────────
```

### 2.1. Modules

```yaml
REQ-FN-ARCH-2101:
  Title:  Main Module
  Parent: REQ-FN-FEAT-1001, REQ-FN-FEAT-1002, REQ-FN-FEAT-1003, REQ-FN-FEAT-1004
  Child:  REQ-FN-ARCH-2201
  Description: The main module orchestrates the game flow, handling user input and output.
```

```yaml
REQ-FN-ARCH-2102:
  Title:  Game Loop Module
  Parent: REQ-FN-FEAT-1001, REQ-FN-FEAT-1002, REQ-FN-FEAT-1003, REQ-FN-FEAT-1004
  Child:  REQ-FN-ARCH-2201, REQ-FN-ARCH-2202
  Description: Orchestrates the overall flow of the game.
```

```yaml
REQ-FN-ARCH-2103:
  Title:  UI Module
  Parent: REQ-FN-FEAT-1001, REQ-FN-FEAT-1002,
  Child:  REQ-FN-ARCH-2202
  Description: Handles all user-facing output and interactions via the terminal.
               Depends on the `board` module to access board state for rendering.
```

```yaml
REQ-FN-ARCH-2104:
  Title:  Player Module
  Parent: REQ-FN-FEAT-1001, REQ-FN-FEAT-1004
  Child:  TBD
  Description: Tracks the current player and handles switching turns.
```

```yaml
REQ-FN-ARCH-2105:
  Title:  IO Module
  Parent: REQ-FN-FEAT-1001, REQ-FN-FEAT-1002
  Child:  TBD
  Description: Reads and parses user input into structured moves.
```

```yaml
REQ-FN-ARCH-2106:
  Title:  Move Validator Module
  Parent: REQ-FN-FEAT-1003, REQ-FN-FEAT-1004
  Child:  TBD
  Description: Validates if a move is legal based on piece rules.
```

```yaml
REQ-FN-ARCH-2107:
  Title:  Check Module
  Parent: REQ-FN-FEAT-1003, REQ-FN-FEAT-1004
  Child:  TBD
  Description: Determines whether a player is in check or checkmate.
```

```yaml
REQ-FN-ARCH-2108:
  Title:  Board Module
  Parent: REQ-FN-FEAT-1001, REQ-FN-FEAT-1002, REQ-FN-FEAT-1003, REQ-FN-FEAT-1004
  Child:  TBD
  Description: Manages the chess board state, including piece positions and legal move generation.
```

```yaml
REQ-FN-ARCH-2109:
  Title:  Board Data Layer
  Parent: TBD
  Child:  TBD
  Description: Manages the raw 8x8 board data structure and provides access to piece positions.
```

### 2.2. Module Dependencies

```yaml
REQ-FN-ARCH-2201:
  Title:  Main <- Game Loop
  Parent: REQ-FN-ARCH-2101, REQ-FN-ARCH-2102
  Child:  TBD
  Description: The main module depends on the game loop module to manage the game flow.
```

```yaml
REQ-FN-ARCH-2202:
  Title:  Game Loop <- UI, Player, IO, Move Validator, Check
  Parent: REQ-FN-ARCH-2102, REQ-FN-ARCH-2103, REQ-FN-ARCH-2104, REQ-FN-ARCH-2105, REQ-FN-ARCH-2106, REQ-FN-ARCH-2107
  Child:  TBD
  Description: The game loop module depends on the UI, Player, IO, Move Validator, and Check modules.
```

```yaml
REQ-FN-ARCH-2203:
  Title:  IO <- Board
  Parent: REQ-FN-ARCH-2105, REQ-FN-ARCH-2108
  Child:  TBD
  Description: The IO module depends on the Board module to access the board state for rendering.
```

---

## 4. Functional Requirements

### 3.1 UI Module

- Description: Handles all user-facing output and interactions via the terminal. Depends on the `board` module to access board state for rendering.
- Depends on: `board`
- Used by: `game`

```yaml
REQ-UI-MAIN-0001:
Title: void ui_init()
Parent: REQ-MOD-UI__-9000
Child: 
Description: 
- Initializes any UI-specific settings or state (e.g., terminal styling). Must be called once at the start of the game.
```

```yaml
REQ-UI-MAIN-0002:
Title: void ui_draw_board()
Parent: REQ-MOD-UI__-9000
Child: 
Description: 
- Renders the current board state to the terminal using ASCII graphics.
```

```yaml
REQ-UI-MAIN-0003:
Title: void ui_show_message(const char* msg)
Parent: REQ-MOD-UI__-9000
Child: 
Description: 
- Prints a message string to the terminal. Used for prompts, errors, and status updates.
```

```yaml
REQ-UI-MAIN-0004:
Title: void ui_cleanup()
Parent: REQ-MOD-UI__-9000
Child: 
Description: 
- Performs any necessary cleanup of UI resources before exiting. Can be left empty.
```

```yaml
REQ-MOD-UI__-9000:
Title: UI Module
Parent: REQ-MOD-ARCH-0000
Child: REQ-UI-MAIN-0001, REQ-UI-MAIN-0002, REQ-UI-MAIN-0003, REQ-UI-MAIN-0004
Description: Handles all user-facing output and interactions via the terminal. Depends on the `board` module to access board state for rendering.
### 3.2 Board Module

- Description: Manages the underlying board data structure and piece positions.
- Depends on: None
- Used by: `ui`, `move_validator`, `check`, `game`


REQ-BRD-MAIN-0001:
Title: void board_init()
Parent: REQ-MOD-BOARD-9001
Child: 
Description: 
- Initializes the internal 8x8 board with the standard chess starting positions.


REQ-BRD-MAIN-0002:
Title: char board_get(int row, int col)
Parent: REQ-MOD-BOARD-9001
Child: 
Description: 
- Returns the character representing the piece at a given board location. Returns `'.'` if the square is empty.


REQ-BRD-MAIN-0003:
Title: void board_set(int row, int col, char piece)
Parent: REQ-MOD-BOARD-9001
Child: 
Description: 
- Places the given piece character at the specified location on the board.


REQ-MOD-BOARD-9001:
Title: Board Module
Parent: REQ-MOD-ARCH-0000
Child: REQ-BRD-MAIN-0001, REQ-BRD-MAIN-0002, REQ-BRD-MAIN-0003
Description: Manages the underlying board data structure and piece positions.
### 3.3 Player Module

- Description: Tracks the current player and handles switching turns.
- Depends on: None
- Used by: `game`, `check`, `move_validator`


REQ-PLY-MAIN-0001:
Title: char player_get_current()
Parent: REQ-MOD-PLYR-9002
Child: 
Description: 
- Returns `'W'` or `'B'` to indicate which player's turn it is.


REQ-PLY-MAIN-0002:
Title: void player_switch()
Parent: REQ-MOD-PLYR-9002
Child: 
Description: 
- Toggles the current player between `'W'` and `'B'`.


REQ-MOD-PLYR-9002:
Title: Player Module
Parent: REQ-MOD-ARCH-0000
Child: REQ-PLY-MAIN-0001, REQ-PLY-MAIN-0002
Description: Tracks the current player and handles switching turns.
### 3.4 IO Module

- Description: Reads and parses user input into structured moves.
- Depends on: None
- Used by: `game`


REQ-IO-MAIN-0001:
Title: typedef struct { int from_row, from_col, to_row, to_col; } Move;
Parent: REQ-MOD-IO__-9003
Child: 
Description: 
- Represents a move from one board position to another.


REQ-IO-MAIN-0002:
Title: bool io_get_move(Move* move)
Parent: REQ-MOD-IO__-9003
Child: 
Description: 
- Prompts the user for input (e.g., `e2 e4`), parses it into the `Move` struct, and returns `true` if valid.


REQ-MOD-IO__-9003:
Title: IO Module
Parent: REQ-MOD-ARCH-0000
Child: REQ-IO-MAIN-0001, REQ-IO-MAIN-0002
Description: Reads and parses user input into structured moves.
### 3.5 Move Validator Module

- Description: Validates if a move is legal based on piece rules.
- Depends on: `board`, `player`
- Used by: `game`, `check`


REQ-VAL-MAIN-0001:
Title: bool is_valid_move(Move move, char player)
Parent: REQ-MOD-VALD-9004
Child: 
Description: 
- Returns `true` if the move is legal for the specified player and piece, according to simplified chess rules.


REQ-MOD-VALD-9004:
Title: Move Validator Module
Parent: REQ-MOD-ARCH-0000
Child: REQ-VAL-MAIN-0001
Description: Validates if a move is legal based on piece rules.
### 3.6 Check Module

- Description: Determines whether a player is in check or checkmate.
REQ-UI-MAIN-0003:
Title: void ui_show_message(const char* msg)
Parent: REQ-MOD-UI__-9000
Child: 
Description: 
- Prints a message string to the terminal. Used for prompts, errors, and status updates.


`REQ-UI-MAIN-0004:`
Title: void ui_cleanup()
Parent: REQ-MOD-UI__-9000
Child: 
Description: 
Parent: [REQ-FNC-001]
Children: [REQ-FNC-010][REQ-FNC-011]
- Performs any necessary cleanup of UI resources before exiting. Can be left empty.


REQ-MOD-UI__-9000:
Title: UI Module
Parent: REQ-MOD-ARCH-0000
Child: REQ-UI-MAIN-0001, REQ-UI-MAIN-0002, REQ-UI-MAIN-0003, REQ-UI-MAIN-0004
Description: Handles all user-facing output and interactions via the terminal. Depends on the `board` module to access board state for rendering.
### 3.2 Board Module

- Description: Manages the underlying board data structure and piece positions.
- Depends on: None
- Used by: `ui`, `move_validator`, `check`, `game`


REQ-BRD-MAIN-0001:
Title: void board_init()
Parent: REQ-MOD-BOARD-9001
Child: 
Description: 
- Initializes the internal 8x8 board with the standard chess starting positions.


REQ-BRD-MAIN-0002:
Title: char board_get(int row, int col)
Parent: REQ-MOD-BOARD-9001
Child: 
Description: 
- Returns the character representing the piece at a given board location. Returns `'.'` if the square is empty.


REQ-BRD-MAIN-0003:
Title: void board_set(int row, int col, char piece)
Parent: REQ-MOD-BOARD-9001
Child: 
Description: 
- Places the given piece character at the specified location on the board.


REQ-MOD-BOARD-9001:
Title: Board Module
Parent: REQ-MOD-ARCH-0000
Child: REQ-BRD-MAIN-0001, REQ-BRD-MAIN-0002, REQ-BRD-MAIN-0003
Description: Manages the underlying board data structure and piece positions.
### 3.3 Player Module

- Description: Tracks the current player and handles switching turns.
- Depends on: None
- Used by: `game`, `check`, `move_validator`


REQ-PLY-MAIN-0001:
Title: char player_get_current()
Parent: REQ-MOD-PLYR-9002
Child: 
Description: 
- Returns `'W'` or `'B'` to indicate which player's turn it is.


REQ-PLY-MAIN-0002:
Title: void player_switch()
Parent: REQ-MOD-PLYR-9002
Child: 
Description: 
- Toggles the current player between `'W'` and `'B'`.


REQ-MOD-PLYR-9002:
Title: Player Module
Parent: REQ-MOD-ARCH-0000
Child: REQ-PLY-MAIN-0001, REQ-PLY-MAIN-0002
Description: Tracks the current player and handles switching turns.
### 3.4 IO Module

- Description: Reads and parses user input into structured moves.
- Depends on: None
- Used by: `game`


REQ-IO-MAIN-0001:
Title: typedef struct { int from_row, from_col, to_row, to_col; } Move;
Parent: REQ-MOD-IO__-9003
Child: 
Description: 
- Represents a move from one board position to another.


REQ-IO-MAIN-0002:
Title: bool io_get_move(Move* move)
Parent: REQ-MOD-IO__-9003
Child: 
Description: 
- Prompts the user for input (e.g., `e2 e4`), parses it into the `Move` struct, and returns `true` if valid.


REQ-MOD-IO__-9003:
Title: IO Module
Parent: REQ-MOD-ARCH-0000
Child: REQ-IO-MAIN-0001, REQ-IO-MAIN-0002
Description: Reads and parses user input into structured moves.
### 3.5 Move Validator Module

- Description: Validates if a move is legal based on piece rules.
- Depends on: `board`, `player`
- Used by: `game`, `check`


REQ-VAL-MAIN-0001:
Title: bool is_valid_move(Move move, char player)
Parent: REQ-MOD-VALD-9004
Child: 
Description: 
- Returns `true` if the move is legal for the specified player and piece, according to simplified chess rules.


REQ-MOD-VALD-9004:
Title: Move Validator Module
Parent: REQ-MOD-ARCH-0000
Child: REQ-VAL-MAIN-0001
Description: Validates if a move is legal based on piece rules.
### 3.6 Check Module

- Description: Determines whether a player is in check or checkmate.
- Depends on: `board`, `move_validator`, `player`
- Used by: `game`


REQ-CHK-MAIN-0001:
Title: bool is_in_check(char player)
Parent: REQ-MOD-CHCK-9005
Child: 
Description: 
- Returns `true` if the current player's king is under attack.


REQ-CHK-MAIN-0002:
Title: bool is_checkmate(char player)
Parent: REQ-MOD-CHCK-9005
Child: 
Description: 
- Returns `true` if the player is in check and has no valid moves to escape.


REQ-MOD-CHCK-9005:
Title: Check Module
Parent: REQ-MOD-ARCH-0000
Child: REQ-CHK-MAIN-0001, REQ-CHK-MAIN-0002
Description: Determines whether a player is in check or checkmate.
### 3.7 Game Loop Module

- Description: Orchestrates the overall flow of the game.
- Depends on: All other modules
- Used by: `main`


REQ-GME-MAIN-0001:
Title: void game_loop()
Parent: REQ-MOD-GAME-9006
Child: 
Description: 
- Controls the main game flow: displays the board, gets input, validates and applies moves, checks win condition, and switches players.

## 4. Constraints
- Only standard C libraries may be used.
- The program must compile and run on a terminal environment.
- No graphical libraries or external dependencies allowed.

## 5. Assumptions
- The game will be played by two human players on the same machine.
- No pawn promotion, castling, or en passant are required.
- Draw conditions (like threefold repetition or stalemate) are not implemented.
- One game per execution.


REQ-MOD-GAME-9006:
Title: Game Loop Module
Parent: REQ-MOD-ARCH-0000
Child: REQ-GME-MAIN-0001
Description: Orchestrates the overall flow of the game.