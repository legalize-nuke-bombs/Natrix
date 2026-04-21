#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>
#include "BoardLayout.hpp"
#include "Storage.hpp"
#include "GUIState.hpp"


#pragma once


class Renderer {
public:
    void draw(sf::RenderWindow& window, const GUIState& state);
private:
    void drawBoard(sf::RenderWindow& window);
    void drawPieces(sf::RenderWindow& window, const GUIState& state);
    void drawMoveHighlights(sf::RenderWindow& window, const GUIState& state);
    void drawPromotionOptions(sf::RenderWindow& window, const std::string& side, sf::Vector2i cell);
    void drawMoveGhost(sf::RenderWindow& window, const std::string& textureName, sf::Vector2i cell);

    static std::string textureName(const Pieces& pieces, int32_t x, int32_t y);

    static constexpr std::array<const char*, 6> PIECE_NAMES = {"Pawn", "Knight", "Bishop", "Rook", "Queen", "King"};
    static constexpr std::array<const char*, 2> SIDE_NAMES = {"white", "black"};
};
