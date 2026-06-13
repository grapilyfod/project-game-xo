/**
 * Ternimal Renderer cpp implementation
 *
 */

#include "renderer.h"

/* ---------- Importing ---------- */

#include <format>
#include <iostream>
// library tự thêm vào để vẽ bàn cờ 
#include <iomanip>

#include "../game/setup.h"
#include "../utils/config.h"

/* ---------- Definitions ---------- */

/**
 * Mô tả:
 *   Constructor của TerminalRenderer.
 *
 * TODO:
 *   - Khởi tạo trạng thái ban đầu nếu cần
 */
TerminalRenderer::TerminalRenderer() : I_Renderer() {
    // TODO: init state
}

/**
 * Mô tả:
 *   Destructor của TerminalRenderer.
 *
 * TODO:
 *   - Giải phóng tài nguyên nếu có
 */
TerminalRenderer::~TerminalRenderer() {
    // TODO: cleanup nếu cần
}

/**
 * Mô tả:
 *   Khởi tạo renderer với config.
 *
 * TODO:
 *   - Đọc config
 *   - Thiết lập môi trường hiển thị
 */
void TerminalRenderer::init(const RunConfig& config) {
    // TODO: init renderer theo config
    // throw NotImplementedException();
    std::cout << "Terminal Renderer initialized" << std::endl;
}

/**
 * Mô tả:
 *   Xóa màn hình terminal.
 *
 * TODO:
 *   - Sử dụng ANSI escape sequence để clear screen
 */
void TerminalRenderer::clearScreen() {
    // TODO: clear screen
    // throw NotImplementedException();
    std::cout << "\n"
              << "\x1B[2J\x1B[H"
              << "\n";
    return;
}

/**
 * Mô tả:
 *   Hiển thị menu lựa chọn.
 *
 * TODO:
 *   - Bước 1: kiểm tra selectType
 *   - Bước 2: in menu tương ứng
 *   - Trường hợp biên: selectType không hợp lệ
 */
void TerminalRenderer::showSelectMenu(SelectType selectType, int context) {
    // TODO: render menu theo loại
    // throw NotImplementedException();
    switch (selectType) {
        case SelectType::TITLE_UI:
            std::cout << ">----- Tic-tac-toe [Console v" << VERSION << "] -----<\n\n";
            break;

        case SelectType::SIZE_UI:
            std::cout << "==================================" << std::endl;
            std::cout << "--------Enter a Board Size--------" << std::endl;
            std::cout << "==================================" << std::endl;
            break;

        case SelectType::GOAL_UI:
            std::cout << "==============================" << std::endl;
            std::cout << "--------Choose a Goal --------" << std::endl;
            std::cout << "==============================" << std::endl;
            break;

        case SelectType::GAME_MODE_UI:
            std::cout << "-----Select a Gamemode-----" << std::endl;
            std::cout << "(1) PvP | (2) PvE | (3) EvE" << std::endl;
            break;

        case SelectType::BOT_LEVEL_UI:
            std::cout << "-----Select a Bot Difficulty-----" << std::endl;
            std::cout << "(1) EASY | (2) MEDIUM | (3) HARD" << std::endl;
            break;

        case SelectType::PLAYER_UI:
            std::cout << "-----------------" << std::endl;
            std::cout << "Enter Your Move: " << std::endl;
            break;

        case SelectType::MUL_BOT_LEVEL_UI:
            std::cout << "-------------------" << std::endl;
            std::cout << "Bot Level: ";
            break;
        default:
            break;
    }
    return;
}

/**
 * Mô tả:
 *   Hiển thị thông báo lựa chọn không hợp lệ.
 *
 * TODO:
 *   - Bước 1: xác định loại lỗi
 *   - Bước 2: in thông báo tương ứng
 */
void TerminalRenderer::showInvalidSelect(SelectType selectType, int context) {
    // TODO: render invalid message
    // throw NotImplementedException();
    switch (selectType){
        case SelectType::SIZE_UI:
            std::cout << "Size choice is Invalid" << std::endl;
            std::cout << "Please choose again" << std::endl;
            break;
        case SelectType::GOAL_UI:
            std::cout << "Goal choice is Invalid" << std::endl;
            std::cout << "Please choose again" << std::endl;
            break;
        case SelectType::GAME_MODE_UI:
            std::cout << "Gamemode choice is Invalid" << std::endl;
            std::cout << "Please choose again" << std::endl;
            break;
        case SelectType::BOT_LEVEL_UI:
            std::cout << "Bot level choice is Invalid" << std::endl; 
            std::cout << "Please choose again" << std::endl;
            break;
        case SelectType::PLAYER_UI:
            std::cout << "Move is Invalid" << std::endl;
            std::cout << "Please choose again" << std::endl;
            break;
        case SelectType::MUL_BOT_LEVEL_UI:
            std::cout << "Bot level choice is Invalid" << std::endl;
            std::cout << "Please choose again" << std::endl;
            break;
        default:
            break;
    }
}

/**
 * Mô tả:
 *   Hiển thị thông báo lựa chọn hợp lệ.
 *
 * TODO:
 *   - Bước 1: xác định loại select
 *   - Bước 2: in thông báo xác nhận
 */
void TerminalRenderer::showValidSelect(SelectType selectType, int context) {
    // TODO: render success message
    // throw NotImplementedException();
    switch (selectType){
        case SelectType::SIZE_UI:
            std::cout << "Size choice is Valid" << std::endl;
            break;
        case SelectType::GOAL_UI:
            std::cout << "Goal choice is Valid" << std::endl;
            break;
        case SelectType::GAME_MODE_UI:
            std::cout << "Gamemode choice is Valid" << std::endl;
            break;
        case SelectType::BOT_LEVEL_UI:
            std::cout << "Bot level choice is Valid" << std::endl; 
            break;
        case SelectType::PLAYER_UI:
            std::cout << "Move is Valid" << std::endl;
            break;
        case SelectType::MUL_BOT_LEVEL_UI:
            std::cout << "Bot level choice is Valid" << std::endl;
            break;
        default:
            break;
    }
}

/**
 * Mô tả:
 *   Hiển thị bàn cờ.
 *
 * TODO:
 *   - Bước 1: in header
 *   - Bước 2: in trục tọa độ
 *   - Bước 3: duyệt board và in từng ô
 */
void TerminalRenderer::displayBoard(const char board[][BOARD_N_MAX], const int size) {
    // TODO: render board
    // throw NotImplementedException();
    std::cout << "      "; 
    for (int j = 0; j < size; j++) {
        std::cout << std::setw(2) << j << "  "; 
    }
    std::cout << "\n";
    std::cout << "    ";
    for (int j = 0; j < size; j++) {
        std::cout << "----";
    }
    std::cout << "\n";
    for (int i = 0; i < size; i++) {
        std::cout << std::setw(2) << i << "  | ";
        for (int j = 0; j < size; j++) {
            std::cout << board[i][j] << " | ";
        }
        std::cout << "\n";
    }
}

/**
 * Mô tả:
 *   Hiển thị thông tin player hiện tại.
 *
 * TODO:
 *   - In player index
 *   - Nếu là bot thì thêm label "(Bot)"
 */
void TerminalRenderer::showPlayer(int player, bool is_bot) {
    // TODO: render player info
    // throw NotImplementedException();
    if (!is_bot){
        std::cout << "Player " << player << "'s turn!" << std::endl;
    }
    else {
        std:: cout << "Bot" << "(Player " << player << ") is making a move!" << std::endl;
    }
}

/**
 * Mô tả:
 *   Hiển thị nước đi vừa thực hiện.
 *
 * TODO:
 *   - In ra tọa độ (row, col)
 */
void TerminalRenderer::showMove(const int row, const int col) {
    // TODO: render move
    // throw NotImplementedException();
    std::cout << "Move placed at " << row << ", " << col << std::endl;
}

/**
 * Mô tả:
 *   Hiển thị thông báo nước đi không hợp lệ.
 *
 * TODO:
 *   - In message lỗi
 */
void TerminalRenderer::showInvalidMove() {
    // TODO: render invalid move message
    // throw NotImplementedException();
    std::cout << "This move is illegal" << std::endl;
}

/**
 * Mô tả:
 *   Hiển thị kết quả game.
 *
 * TODO:
 *   - Bước 1: kiểm tra draw hoặc winner
 *   - Bước 2: in kết quả
 *   - Trường hợp biên: winner = -1
 */
void TerminalRenderer::showResult(const int winner, const bool is_bot, const WinLine* winLine) {
    // TODO: render result
    // throw NotImplementedException();
    if (winner == -1){
        std::cout << "It's a draw!" << std::endl;
    }
    else if (is_bot){
        std::cout << "Bot wins!" << std::endl;
    }
    else {
        std::cout << "Player " << winner + 1 << " wins!" << std::endl;
    }
}

/**
 * Mô tả:
 *   In kết quả đơn giản (judge mode).
 *
 * TODO:
 *   - In winner và số lượt
 */
void TerminalRenderer::printResult(const GameResult& gameResult) {
    // TODO: print result đơn giản
    // throw NotImplementedException();
    std::cout << gameResult.winner << " " << gameResult.turns << std::endl;
}

/**
 * Mô tả:
 *   Đóng renderer.
 *
 * TODO:
 *   - Giải phóng tài nguyên nếu có
 */
void TerminalRenderer::close() {
    // TODO: cleanup renderer
}