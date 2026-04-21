#include <cstdint>
#include <optional>
#include <algorithm>
#include <SFML/Graphics.hpp>


#pragma once


namespace BoardLayout {
    static constexpr int32_t MARGIN = 20;

    inline sf::Vector2f cellSize(const sf::RenderWindow& window) {
        uint32_t side = (std::min(window.getSize().x, window.getSize().y) - 2 * MARGIN) / 8;
        return {static_cast<float>(side), static_cast<float>(side)};
    }

    inline sf::Vector2f cellPosition(const sf::RenderWindow& window, int32_t x, int32_t y) {
        sf::Vector2f size = cellSize(window);
        return {MARGIN + size.x * static_cast<float>(x),
                static_cast<float>(window.getSize().y) - MARGIN - size.y * static_cast<float>(y + 1)};
    }

    inline std::optional<sf::Vector2i> cellAt(const sf::RenderWindow& window, sf::Vector2i mousePos) {
        sf::Vector2f size = cellSize(window);
        for (int32_t x = 0; x < 8; x++) {
            for (int32_t y = 0; y < 8; y++) {
                sf::Vector2f pos = cellPosition(window, x, y);
                if (mousePos.x > static_cast<int32_t>(pos.x) &&
                    mousePos.y > static_cast<int32_t>(pos.y) &&
                    mousePos.x < static_cast<int32_t>(pos.x + size.x) &&
                    mousePos.y < static_cast<int32_t>(pos.y + size.y)) {
                    return sf::Vector2i(x, y);
                }
            }
        }
        return std::nullopt;
    }

    inline uint8_t promotionQuadrant(const sf::RenderWindow& window, sf::Vector2i mousePos, sf::Vector2i cell) {
        sf::Vector2f pos = cellPosition(window, cell.x, cell.y);
        sf::Vector2f size = cellSize(window);
        float dx = static_cast<float>(mousePos.x) - pos.x;
        float dy = static_cast<float>(mousePos.y) - pos.y;
        bool left = dx < size.x / 2;
        bool top = dy < size.y / 2;

        if (left && top) return 0;
        if (left && !top) return 1;
        if (!left && top) return 2;
        return 3;
    }
}
