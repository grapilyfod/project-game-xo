/**
 * Bot LV2 cpp implementation
 *
 */

#include "bot_lv2.h"

/* ---------- Importing ---------- */

#include <sstream>
#include <vector>
#include <cstdlib>

#include "../../utils/logger.h"
#include "../logic.h"

/* ---------- Definitions ---------- */

/**
 * Mô tả:
 *   Constructor của BotLevel2.
 */
BotLevel2::BotLevel2(const BotLevel& _level, const char& _symbol)
    : BotLevel1(_level, _symbol) {
}

/**
 * Mô tả:
 *   Destructor của BotLevel2.
 */
BotLevel2::~BotLevel2() {
}

/**
 * Mô tả:
 *   Trả về nước đi của bot MEDIUM.
 *
 * TODO:
 *   - Gọi heuristic để chọn nước đi
 */
pII BotLevel2::getMove(char board[][BOARD_N_MAX], const int size, const int goal) {
    // TODO: gọi simple_heuristic với symbol và op_symbol
    // throw NotImplementedException();
    // return {0, 0};
    char botSymbol = symbol;
    char playerSymbol;
    if (botSymbol == 'X') {
        playerSymbol = 'O';
    } else {
        playerSymbol = 'X';
    }
    return simple_heuristic(board, size, goal, botSymbol, playerSymbol);
}

/**
 * Mô tả:
 *   Heuristic đơn giản:
 *   - Ưu tiên thắng
 *   - Chặn đối thủ
 *   - Fallback random
 *
 * TODO:
 *   - Bước 1: kiểm tra nước thắng
 *   - Bước 2: kiểm tra nước chặn
 *   - Bước 3: chọn random nếu không có
 */
pII BotLevel2::simple_heuristic(char board[][BOARD_N_MAX], const int size, const int goal, const char botSymbol, const char playerSymbol) {
    // TODO: implement heuristic
    // throw NotImplementedException();
    // return {-1, -1};
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (board[r][c] == '-') {
                board[r][c] = botSymbol;
                if (Logic::checkWin(board, size, botSymbol, goal, EndRule::NONE)) {
                    board[r][c] = '-';
                    return {r, c};
                }
                board[r][c] = '-';
            }
        }
    }
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (board[r][c] == '-') {
                board[r][c] = playerSymbol;
                if (Logic::checkWin(board, size, playerSymbol, goal, EndRule::NONE)) {
                    board[r][c] = '-';
                    return {r, c};
                }
                board[r][c] = '-';
            }
        }
    }
    std::vector <pII> emptycells;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (board[i][j] == '-'){
                emptycells.push_back({i, j});
            }
        }
    }
    if (emptycells.empty()){
        Logger::log("BotLevel1: Không ô trống", Logger::Level::WARNING);
        return {-1, -1};
    }       
    int i;
    i = rand() % emptycells.size();
    return emptycells[i];
}