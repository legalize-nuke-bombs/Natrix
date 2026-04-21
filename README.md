# Natrix

A chess engine with a graphical interface, written in C++.

## Features

### Engine
- Bitboard-based board representation
- Legal move generation verified with [perft tests](https://www.chessprogramming.org/Perft_Results)
- Alpha-beta pruning with iterative deepening
- Quiescence search
- Transposition table (Zobrist hashing)
- Move ordering
- Check extensions
- Time-controlled search
- Static evaluation:
  - Material
  - Mobility
  - Pawn structure (doubled, connected, passed pawns)
  - King safety
  - Endgame heuristics

### GUI
- SFML 3 based graphical interface
- Piece selection and legal move highlighting
- Promotion UI
- Sound effects
- Resizable window

## Building

**Requirements:** C++20, [vcpkg](https://github.com/microsoft/vcpkg), Visual Studio

1. Install SFML via vcpkg:
```
vcpkg install sfml:x64-windows
```

2. Open the project in Visual Studio, make sure vcpkg integration is enabled:
```
vcpkg integrate install
```

3. Set the platform to **x64** and build.

## Project structure

```
src/
├── Engine
│   ├── AI                    — search (iterative deepening, alpha-beta)
│   ├── StaticEvaluator       — position evaluation
│   ├── LegalMoveGen          — legal move generation
│   ├── PsLegalMoveMaskGen    — pseudo-legal move masks, attack detection
│   ├── MoveSorter            — move ordering for search
│   ├── TranspositionTable    — transposition table
│   ├── Position              — game state (board, castling, en passant, etc.)
│   ├── Pieces                — bitboard storage and operations
│   ├── Move / MoveList       — move representation
│   ├── ZobristHash           — incremental hashing
│   ├── RepetitionHistory     — threefold repetition detection
│   ├── SearchInterrupter     — time control for search
│   └── Bitboard              — bitboard utilities
│
├── GUI
│   ├── GUI                   — application loop, coordination
│   ├── GUIState              — game state for the interface
│   ├── Renderer              — board and piece rendering
│   ├── InputHandler          — SFML event processing
│   ├── BoardLayout           — board geometry calculations
│   └── Storage               — texture and sound management
│
├── Testing
│   └── LegalMoveGenTester    — perft testing
│
└── main.cpp
```

