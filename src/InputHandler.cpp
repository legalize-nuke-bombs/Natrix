#include "InputHandler.hpp"


InputResult InputHandler::processEvents(sf::RenderWindow& window) {
    InputResult result;

    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            result.closed = true;
            return result;
        }

        if (auto* resized = event->getIf<sf::Event::Resized>()) {
            sf::FloatRect visibleArea({0, 0}, {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)});
            window.setView(sf::View(visibleArea));
        }

        if (auto* mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
            auto cell = BoardLayout::cellAt(window, mouseBtn->position);
            if (cell.has_value()) {
                uint8_t quadrant = BoardLayout::promotionQuadrant(window, mouseBtn->position, *cell);
                result.cellClick = CellClick{*cell, quadrantToPromotionFlag(quadrant)};
            }
        }
    }

    return result;
}
uint8_t InputHandler::quadrantToPromotionFlag(uint8_t quadrant) {
    static constexpr uint8_t FLAGS[] = {
        Move::FLAG::PROMOTE_TO_KNIGHT,
        Move::FLAG::PROMOTE_TO_BISHOP,
        Move::FLAG::PROMOTE_TO_ROOK,
        Move::FLAG::PROMOTE_TO_QUEEN
    };
    return FLAGS[quadrant];
}
