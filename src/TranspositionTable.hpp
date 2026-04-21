#include <unordered_map>
#include "ZobristHash.hpp"


#pragma once


class TranspositionTable {
public:
    static TranspositionTable& get() {
        static TranspositionTable inst;
        return inst;
    }
    TranspositionTable(const TranspositionTable &donor) = delete;

    void addEntry(ZobristHash hash, int32_t depth, uint8_t bestMoveIndex);
    uint8_t getBestMoveIndex(ZobristHash hash) const;

    static constexpr uint8_t NONE = 255;
private:
    TranspositionTable();

    std::unordered_map<uint64_t, std::pair<int32_t, uint8_t>> map;
};