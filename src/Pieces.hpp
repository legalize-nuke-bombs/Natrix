#include <cctype>
#include "Bitboard.hpp"


#pragma once


enum PIECE {
    PAWN = 0,
    KNIGHT = 1,
    BISHOP = 2,
    ROOK = 3,
    QUEEN = 4,
    KING = 5
};


enum SIDE {
    WHITE = 0,
    BLACK = 1
};


class Pieces {
public:
    Pieces();
    Pieces(const std::string& shortFen);

    friend std::ostream& operator <<(std::ostream& ostream, Pieces pieces);

    void updateBitboards();

    void setPieceBitboard(uint8_t side, uint8_t piece, Bitboard bb);

    std::array<std::array<Bitboard, 6>, 2> getPieceBitboards() const;
    Bitboard getPieceBitboard(uint8_t side, uint8_t piece) const;
    Bitboard getSideBitboard(uint8_t side) const;
    Bitboard getInvSideBitboard(uint8_t side) const;
    Bitboard getAllBitboard() const;
    Bitboard getEmptyBitboard() const;

    static uint8_t inverse(uint8_t side);
private:
    std::array<std::array<Bitboard, 6>, 2> pieceBitboards{};
    std::array<Bitboard, 2> sideBitboards{};
    std::array<Bitboard, 2> invSideBitboards{};
    Bitboard all;
    Bitboard empty;
};