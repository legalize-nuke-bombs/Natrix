#include <cstdint>
#include <optional>
#include <SFML/System.hpp>
#include "Position.hpp"
#include "LegalMoveGen.hpp"
#include "PsLegalMoveMaskGen.hpp"
#include "AI.hpp"


#pragma once


struct MoveResult {
    bool moveMade = false;
    bool wasCapture = false;
    bool gameEnded = false;
};


class GUIState {
public:
    enum Status : uint8_t {
        WHITE_TO_MOVE,
        BLACK_TO_MOVE,
        WHITE_WON,
        BLACK_WON,
        DRAW
    };

    GUIState();

    void selectCell(sf::Vector2i cell);
    void deselectCell();
    MoveResult tryPlayerMove(sf::Vector2i target, uint8_t promotionFlag);
    MoveResult makeAIMove();

    const Position& getPosition() const;
    std::optional<sf::Vector2i> getSelectedCell() const;
    Status getStatus() const;
    const MoveList& getSelectedMoves() const;
    bool isPlayerTurn() const;
    bool isGameOver() const;
private:
    void recalcStatus();
    void recalcSelectedMoves();

    static bool isCapture(const Move& move);

    Position position;
    std::optional<sf::Vector2i> selectedCell;
    Status status;
    MoveList selectedMoves;
};
