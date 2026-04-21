#include "MoveList.hpp"
#include "StaticEvaluator.hpp"


#pragma once


class MoveSorter {
public:
    static MoveList sort(Pieces pieces, MoveList moves);
private:
    static int32_t evaluateMove(Pieces pieces, Move move);
};