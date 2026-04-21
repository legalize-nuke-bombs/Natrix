#include "Renderer.hpp"


void Renderer::draw(sf::RenderWindow& window, const GUIState& state) {
    window.clear(sf::Color(22, 21, 18));
    drawBoard(window);
    drawPieces(window, state);
    if (state.getSelectedCell().has_value()) {
        drawMoveHighlights(window, state);
    }
    window.display();
}
void Renderer::drawBoard(sf::RenderWindow& window) {
    sf::Vector2f size = BoardLayout::cellSize(window);
    for (int32_t x = 0; x < 8; x++) {
        for (int32_t y = 0; y < 8; y++) {
            sf::RectangleShape cell(size);
            cell.setPosition(BoardLayout::cellPosition(window, x, y));
            if ((x + y) % 2 == 0) {
                cell.setFillColor(sf::Color(181, 136, 99));
            }
            else {
                cell.setFillColor(sf::Color(240, 217, 181));
            }
            window.draw(cell);
        }
    }
}
void Renderer::drawPieces(sf::RenderWindow& window, const GUIState& state) {
    sf::Vector2f size = BoardLayout::cellSize(window);
    auto selected = state.getSelectedCell();

    for (int32_t x = 0; x < 8; x++) {
        for (int32_t y = 0; y < 8; y++) {
            std::string name = textureName(state.getPosition().getPieces(), x, y);
            if (name.empty()) {
                continue;
            }
            sf::Sprite sprite(Storage::get().getTexture(name));
            sf::Vector2f pos = BoardLayout::cellPosition(window, x, y);
            sf::FloatRect bounds = sprite.getLocalBounds();

            if (selected.has_value() && sf::Vector2i(x, y) == *selected) {
                float scale = size.x / bounds.size.x * 1.2f;
                sprite.setScale({scale, scale});
                sf::Vector2f scaledSize(bounds.size.x * scale, bounds.size.y * scale);
                sprite.setPosition({pos.x - (scaledSize.x - size.x) / 2, pos.y - (scaledSize.y - size.y) / 2});
            }
            else {
                sprite.setScale({size.x / bounds.size.x, size.y / bounds.size.y});
                sprite.setPosition(pos);
            }
            window.draw(sprite);
        }
    }
}
void Renderer::drawMoveHighlights(sf::RenderWindow& window, const GUIState& state) {
    auto selected = state.getSelectedCell();
    if (!selected.has_value()) {
        return;
    }

    std::string name = textureName(state.getPosition().getPieces(), selected->x, selected->y);
    if (name.empty()) {
        return;
    }

    std::string side = name.substr(0, 5);
    const MoveList& moves = state.getSelectedMoves();

    for (int32_t i = 0; i < moves.getSize(); i++) {
        uint8_t toX = moves[i].getTo() % 8;
        uint8_t toY = moves[i].getTo() / 8;

        if (moves[i].getAttackerType() == PIECE::PAWN && (toY == 0 || toY == 7)) {
            drawPromotionOptions(window, side, {toX, toY});
        }
        else {
            drawMoveGhost(window, name, {toX, toY});
        }
    }
}
void Renderer::drawPromotionOptions(sf::RenderWindow& window, const std::string& side, sf::Vector2i cell) {
    sf::Vector2f size = BoardLayout::cellSize(window);
    sf::Vector2f pos = BoardLayout::cellPosition(window, cell.x, cell.y);

    static constexpr std::array<const char*, 4> PROMO_PIECES = {"Knight", "Bishop", "Rook", "Queen"};
    static constexpr float OFFSETS_X[] = {0.0f, 0.0f, 0.5f, 0.5f};
    static constexpr float OFFSETS_Y[] = {0.0f, 0.5f, 0.0f, 0.5f};

    for (int32_t i = 0; i < 4; i++) {
        sf::Sprite sprite(Storage::get().getTexture(side + PROMO_PIECES[i]));
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setScale({size.x / bounds.size.x * 0.5f, size.y / bounds.size.y * 0.5f});
        sprite.setColor(sf::Color(255, 255, 255, 63));
        sprite.setPosition({pos.x + size.x * OFFSETS_X[i], pos.y + size.y * OFFSETS_Y[i]});
        window.draw(sprite);
    }
}
void Renderer::drawMoveGhost(sf::RenderWindow& window, const std::string& textureName, sf::Vector2i cell) {
    sf::Vector2f size = BoardLayout::cellSize(window);
    sf::Vector2f pos = BoardLayout::cellPosition(window, cell.x, cell.y);
    sf::Sprite sprite(Storage::get().getTexture(textureName));
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setScale({size.x / bounds.size.x, size.y / bounds.size.y});
    sprite.setPosition(pos);
    sprite.setColor(sf::Color(255, 255, 255, 63));
    window.draw(sprite);
}
std::string Renderer::textureName(const Pieces& pieces, int32_t x, int32_t y) {
    int32_t id = y * 8 + x;
    auto bbs = pieces.getPieceBitboards();
    for (uint8_t side = 0; side < 2; side++) {
        for (uint8_t piece = 0; piece < 6; piece++) {
            if (BOp::getBit(bbs[side][piece], id)) {
                return std::string(SIDE_NAMES[side]) + PIECE_NAMES[piece];
            }
        }
    }
    return "";
}
