/**
 * Logic cpp implementation
 *
 */

#include "logic.h"

/* ---------- Importing ---------- */

#include <format>
#include <limits>
#include <sstream>

#include "../utils/logger.h"

/* ---------- Definitions ---------- */

/**
 * Mô tả: Khởi tạo bàn cờ với ký tự mặc định.
 * Đầu vào: board, size
 * Đầu ra: Không có
 * Tác dụng phụ: Ghi dữ liệu vào board
 * TODO:
 */
void Logic::initBoard(char board[][BOARD_N_MAX], const int size) {
    // TODO: implement
    // throw NotImplementedException();
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            board[i][j] = '-';
        }
    }
}

/**
 * Mô tả: Kiểm tra nước đi có hợp lệ không.
 * Đầu vào: board, size, row, col
 * Đầu ra: true nếu hợp lệ
 * Tác dụng phụ: Không có
 * TODO:
 */
bool Logic::isValidMove(const char board[][BOARD_N_MAX], const int size, const int row, const int col) {
    // TODO: implement
    // throw NotImplementedException();
    if (row < 0 || row > size - 1 || col < 0 || col > size - 1 ){
        return false;
    }
    if (board[row][col] == '-'){
        return true;
    }
    return false;
}

/**
 * Mô tả: Thực hiện một nước đi.
 * Đầu vào: board, row, col, symbol
 * Đầu ra: Không có
 * Tác dụng phụ: Ghi vào board
 * TODO:
 */
void Logic::makeMove(char board[][BOARD_N_MAX], const int row, const int col, const char symbol) {
    // TODO: implement
    // throw NotImplementedException();
    board[row][col] = symbol;
}

/**
 * Mô tả: Kiểm tra một ô có phải là đầu mở hay không.
 * Đầu vào: board, size, x, y, symbol
 * Đầu ra: true nếu là đầu mở
 * Tác dụng phụ: Không có
 * TODO:
 */
bool Logic::isEmptyHead(const char board[][BOARD_N_MAX], const int size, int x, int y, const char symbol) {
    // TODO: implement
    // throw NotImplementedException();
    if (board[x][y] == '-'){
        return true;
    }
    if (board[x][y] == symbol){
        return true;
    }
    if (x < 0 || y < 0 || x >= size || y >= size){
        return true;
    }
    return false;
}

/**
 * Mô tả: Kiểm tra điều kiện thắng.
 * Đầu vào: board, size, symbol, goal, rule
 * Đầu ra: true nếu thắng
 * Tác dụng phụ: Có thể log debug
 * TODO:
 */
bool Logic::checkWin(char board[][BOARD_N_MAX], const int size, const char symbol, const int goal, EndRule rule) {
    // TODO: implement
    // throw NotImplementedException();
    int dr[] = {0, 1, 1, 1};
    int dc[] = {1, 0, 1, -1};
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            for (int dir = 0; dir < 4; dir++) {
                int count = 0;
                for (int step = 0; step < size; step++) {
                    int currR = r + step * dr[dir];
                    int currC = c + step * dc[dir];
                    if (currR >= 0 && currR < size && currC >= 0 && currC < size) {
                        if (board[currR][currC] == symbol) {
                            count++;
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        break;
                    }
                }
                if (count >= goal){
                    int prevRow = r - dr[dir];
                    int prevCol = c - dc[dir];
                    int nextRow = r + dr[dir] * count;
                    int nextCol = c + dc[dir] * count;
                    bool prevOpen;
                    bool nextOpen;
                    if (prevRow < 0 || prevRow >= size || prevCol < 0 || prevCol >= size){
                        prevOpen = true;
                    }
                    else {
                        if (board[prevRow][prevCol] == '-'){
                            prevOpen = true;
                        }
                        else {
                            prevOpen = false;
                        }
                    }
                    if (nextRow < 0 || nextRow >= size || nextCol < 0 || nextCol >= size){
                        nextOpen = true;
                    }
                    else {
                        if (board[nextRow][nextCol] == '-'){
                            nextOpen = true;
                        }
                        else {
                            nextOpen = false;
                        }
                    }
                    if (rule == EndRule::NONE){
                        return true;
                    }
                    if (rule == EndRule::OPEN_ONE && (prevOpen || nextOpen)){
                        return true;
                    }
                    if (rule == EndRule::OPEN_TWO && prevOpen && nextOpen){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/**
 * Mô tả: Kiểm tra trạng thái hòa.
 * Đầu vào: board, size
 * Đầu ra: true nếu hòa
 * Tác dụng phụ: Không có
 * TODO:
 */
bool Logic::checkDraw(char board[][BOARD_N_MAX], const int size) {
    // TODO: implement
    // throw NotImplementedException();
    for (int i = 0; i < size; i++){
        for (int j =0; j < size; j++){
            if (board[i][j] == '-'){
                return false;
            }
        }
    }
    return true;
}

/**
 * Mô tả: Lấy đường thắng nếu tồn tại.
 * Đầu vào: board, size, symbol, goal, rule
 * Đầu ra: optional WinLine
 * Tác dụng phụ: Không có
 * TODO:
 */
std::optional<WinLine> Logic::getWinLine(
    const char board[][BOARD_N_MAX],
    const int size,
    const char symbol,
    const int goal,
    EndRule rule) {
    // TODO: implement
    return std::nullopt;
}