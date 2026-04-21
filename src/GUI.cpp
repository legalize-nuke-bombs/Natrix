#include "GUI.hpp"


GUI::GUI() {
    Storage::get().setRoot("data");
    Storage::get().addTexture("whitePawn", "images/chessmen/white/pawn.png");
    Storage::get().addTexture("whiteKnight", "images/chessmen/white/knight.png");
    Storage::get().addTexture("whiteBishop", "images/chessmen/white/bishop.png");
    Storage::get().addTexture("whiteRook", "images/chessmen/white/rook.png");
    Storage::get().addTexture("whiteQueen", "images/chessmen/white/queen.png");
    Storage::get().addTexture("whiteKing", "images/chessmen/white/king.png");
    Storage::get().addTexture("blackPawn", "images/chessmen/black/pawn.png");
    Storage::get().addTexture("blackKnight", "images/chessmen/black/knight.png");
    Storage::get().addTexture("blackBishop", "images/chessmen/black/bishop.png");
    Storage::get().addTexture("blackRook", "images/chessmen/black/rook.png");
    Storage::get().addTexture("blackQueen", "images/chessmen/black/queen.png");
    Storage::get().addTexture("blackKing", "images/chessmen/black/king.png");
    Storage::get().addSoundBuffer("move", "sounds/move.ogg");
    Storage::get().addSoundBuffer("capture", "sounds/capture.ogg");
    Storage::get().addSoundBuffer("message", "sounds/message.ogg");

    window.create(sf::VideoMode({600, 600}), "Natrix");
    window.setFramerateLimit(60);
}
void GUI::start() {
    while (window.isOpen()) {
        InputResult input = InputHandler::processEvents(window);

        if (input.closed) {
            return;
        }

        if (input.cellClick.has_value() && state.isPlayerTurn()) {
            handleCellClick(*input.cellClick);
        }

        renderer.draw(window, state);
    }
}
void GUI::handleCellClick(const CellClick& click) {
    auto selected = state.getSelectedCell();

    if (selected.has_value() && click.cell == *selected) {
        state.deselectCell();
        playSound("move");
        return;
    }

    const Pieces& pieces = state.getPosition().getPieces();
    if (BOp::getBit(pieces.getSideBitboard(SIDE::WHITE), click.cell.y * 8 + click.cell.x)) {
        state.selectCell(click.cell);
        playSound("move");
        return;
    }

    if (selected.has_value()) {
        MoveResult result = state.tryPlayerMove(click.cell, click.promotionFlag);

        if (result.moveMade) {
            playSound(result.wasCapture ? "capture" : "move");

            if (result.gameEnded) {
                playSound("message");
                return;
            }

            renderer.draw(window, state);

            MoveResult aiResult = state.makeAIMove();
            playSound(aiResult.wasCapture ? "capture" : "move");

            if (aiResult.gameEnded) {
                playSound("message");
            }
        }
    }
}
void GUI::playSound(const std::string& name) {
    sound.emplace(Storage::get().getSoundBuffer(name));
    sound->play();
}
