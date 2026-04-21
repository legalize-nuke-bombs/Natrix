#include "GUIState.hpp"


GUIState::GUIState() {
    position = Position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR", Position::NONE, true, true, true, true, 1);
    recalcStatus();
}
void GUIState::selectCell(sf::Vector2i cell) {
    selectedCell = cell;
    recalcSelectedMoves();
}
void GUIState::deselectCell() {
    selectedCell = std::nullopt;
    selectedMoves = MoveList();
}
MoveResult GUIState::tryPlayerMove(sf::Vector2i target, uint8_t promotionFlag) {
    for (int32_t i = 0; i < selectedMoves.getSize(); i++) {
        Move move = selectedMoves[i];
        bool fromMatch = move.getFrom() == selectedCell->y * 8 + selectedCell->x;
        bool toMatch = move.getTo() == target.y * 8 + target.x;
        bool isPromotion = move.getFlag() == Move::FLAG::PROMOTE_TO_KNIGHT ||
                           move.getFlag() == Move::FLAG::PROMOTE_TO_BISHOP ||
                           move.getFlag() == Move::FLAG::PROMOTE_TO_ROOK ||
                           move.getFlag() == Move::FLAG::PROMOTE_TO_QUEEN;
        bool promoMatch = !isPromotion || move.getFlag() == promotionFlag;

        if (fromMatch && toMatch && promoMatch) {
            bool capture = isCapture(move);
            position.move(move);
            deselectCell();
            recalcStatus();
            return {true, capture, isGameOver()};
        }
    }

    deselectCell();
    return {};
}
MoveResult GUIState::makeAIMove() {
    Move move = AI::getBestMove(position, SIDE::BLACK, 2000);
    bool capture = isCapture(move);
    position.move(move);
    recalcStatus();
    return {true, capture, isGameOver()};
}
const Position& GUIState::getPosition() const {
    return position;
}
std::optional<sf::Vector2i> GUIState::getSelectedCell() const {
    return selectedCell;
}
GUIState::Status GUIState::getStatus() const {
    return status;
}
const MoveList& GUIState::getSelectedMoves() const {
    return selectedMoves;
}
bool GUIState::isPlayerTurn() const {
    return status == WHITE_TO_MOVE;
}
bool GUIState::isGameOver() const {
    return status == WHITE_WON || status == BLACK_WON || status == DRAW;
}
void GUIState::recalcStatus() {
    if (position.fiftyMovesRuleDraw() || position.threefoldRepetitionDraw()) {
        status = DRAW;
        return;
    }

    const Pieces& pieces = position.getPieces();

    bool noHeavyPieces =
        !pieces.getPieceBitboard(SIDE::WHITE, PIECE::PAWN) &&
        !pieces.getPieceBitboard(SIDE::BLACK, PIECE::PAWN) &&
        !pieces.getPieceBitboard(SIDE::WHITE, PIECE::ROOK) &&
        !pieces.getPieceBitboard(SIDE::BLACK, PIECE::ROOK) &&
        !pieces.getPieceBitboard(SIDE::WHITE, PIECE::QUEEN) &&
        !pieces.getPieceBitboard(SIDE::BLACK, PIECE::QUEEN);

    if (noHeavyPieces) {
        uint8_t whiteMinors = BOp::count1(
            pieces.getPieceBitboard(SIDE::WHITE, PIECE::KNIGHT) |
            pieces.getPieceBitboard(SIDE::WHITE, PIECE::BISHOP));
        uint8_t blackMinors = BOp::count1(
            pieces.getPieceBitboard(SIDE::BLACK, PIECE::KNIGHT) |
            pieces.getPieceBitboard(SIDE::BLACK, PIECE::BISHOP));

        if (whiteMinors < 2 && blackMinors < 2) {
            status = DRAW;
            return;
        }
    }

    if (position.blackToMove()) {
        MoveList moves = LegalMoveGen::generate(position, SIDE::BLACK);
        if (moves.getSize() == 0) {
            Bitboard kingBB = pieces.getPieceBitboard(SIDE::BLACK, PIECE::KING);
            status = PsLegalMoveMaskGen::inDanger(pieces, BOp::bsf(kingBB), SIDE::BLACK) ? WHITE_WON : DRAW;
            return;
        }
        status = BLACK_TO_MOVE;
        return;
    }

    MoveList moves = LegalMoveGen::generate(position, SIDE::WHITE);
    if (moves.getSize() == 0) {
        Bitboard kingBB = pieces.getPieceBitboard(SIDE::WHITE, PIECE::KING);
        status = PsLegalMoveMaskGen::inDanger(pieces, BOp::bsf(kingBB), SIDE::WHITE) ? BLACK_WON : DRAW;
        return;
    }
    status = WHITE_TO_MOVE;
}
void GUIState::recalcSelectedMoves() {
    if (!selectedCell.has_value()) {
        selectedMoves = MoveList();
        return;
    }

    MoveList allMoves = LegalMoveGen::generate(position, SIDE::WHITE);
    selectedMoves = MoveList();
    uint8_t fromSquare = selectedCell->y * 8 + selectedCell->x;

    for (int32_t i = 0; i < allMoves.getSize(); i++) {
        if (allMoves[i].getFrom() == fromSquare) {
            selectedMoves.push(allMoves[i]);
        }
    }
}
bool GUIState::isCapture(const Move& move) {
    return move.getDefenderType() != Move::NONE || move.getFlag() == Move::FLAG::EN_PASSANT_CAPTURE;
}
