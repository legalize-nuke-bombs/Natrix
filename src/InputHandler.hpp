#include <cstdint>
#include <optional>
#include <SFML/Graphics.hpp>
#include "BoardLayout.hpp"
#include "Move.hpp"


#pragma once


struct CellClick {
    sf::Vector2i cell;
    uint8_t promotionFlag;
};

struct InputResult {
    bool closed = false;
    std::optional<CellClick> cellClick;
};


class InputHandler {
public:
    static InputResult processEvents(sf::RenderWindow& window);
private:
    static uint8_t quadrantToPromotionFlag(uint8_t quadrant);
};
