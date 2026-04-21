#include <cmath>
#include "RepetitionHistory.hpp"
#include "Move.hpp"


#pragma once


class Position {
public:
    Position();
    Position(const std::string& shortFen, uint8_t enPassant, bool wlCastling, bool wsCastling, bool blCastling, bool bsCastling, float moveCtr);

    friend std::ostream& operator <<(std::ostream& ostream, const Position& position);

    void move(Move move);

    Pieces getPieces() const;
    uint8_t getEnPassant() const;
    bool getWLCastling() const;
    bool getWSCastling() const;
    bool getBLCastling() const;
    bool getBSCastling() const;
    bool whiteToMove() const;
    bool blackToMove() const;
    ZobristHash getHash() const;
    bool fiftyMovesRuleDraw() const;
    bool threefoldRepetitionDraw() const;

    static constexpr uint8_t NONE = 255;
private:
    void addPiece(uint8_t square, uint8_t type, uint8_t side);
    void removePiece(uint8_t square, uint8_t type, uint8_t side);
    void changeEnPassant(uint8_t en_passant);

    void removeWLCastling();
    void removeWSCastling();
    void removeBLCastling();
    void removeBSCastling();

    void updateMoveCtr();
    void updateFiftyMovesCtr(bool breakEvent);

    Pieces pieces;
    uint8_t enPassant;

    bool wlCastling;
    bool wsCastling;
    bool blCastling;
    bool bsCastling;

    float moveCtr;
    ZobristHash hash;
    float fiftyMovesCtr;
    RepetitionHistory repetitionHistory;
};