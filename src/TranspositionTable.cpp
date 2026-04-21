#include "TranspositionTable.hpp"


void TranspositionTable::addEntry(ZobristHash hash, int32_t depth, uint8_t bestMoveIndex) {
    auto it = this->map.find(hash.getValue());
    if (it == this->map.end()) {
        this->map[hash.getValue()] = std::make_pair(depth, bestMoveIndex);
    }
    else if (it->second.first < depth) {
        this->map.erase(it);
        this->map[hash.getValue()] = std::make_pair(depth, bestMoveIndex);
    }
}
uint8_t TranspositionTable::getBestMoveIndex(ZobristHash hash) const {
    auto it = this->map.find(hash.getValue());
    if (it == this->map.end()) {
        return NONE;
    }
    return it->second.second;
}
TranspositionTable::TranspositionTable() {
    this->map.reserve(1024 * 1024 * 10);
}