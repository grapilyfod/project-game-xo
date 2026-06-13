/**
 * SDL Interaction cpp implementation
 *
 */

#include "interaction.h"

/* ---------- Importing ---------- */

#include <format>
#include <iostream>
#include <algorithm>
#include <SDL2/SDL_ttf.h>

/* ---------- Definitions ---------- */

/**
 * Mô tả: Kiểm tra sự kiện quit từ SDL.
 * Đầu vào:
 *   - e: SDL_Event hiện tại.
 * Đầu ra:
 *   - false nếu không phải quit event.
 * Tác dụng phụ:
 *   - Ném QuitException nếu nhận được sự kiện thoát.
 */
bool SDLInteraction::waitForQuit(SDL_Event& e) {
    if (e.type == SDL_QUIT) {
        throw QuitException();
    }
    return false;
}

/**
 * Mô tả: Khởi tạo đối tượng SDLInteraction.
 * Đầu vào: Không có.
 * Đầu ra: Không có.
 * Tác dụng phụ: Không có.
 */
SDLInteraction::SDLInteraction() {
}

/**
 * Mô tả: Destructor của SDLInteraction.
 * Đầu vào: Không có.
 * Đầu ra: Không có.
 * Tác dụng phụ: Không có.
 */
SDLInteraction::~SDLInteraction() {
}

/**
 * Mô tả: Khởi tạo hệ thống interaction cho SDL.
 * Đầu vào:
 *   - config: cấu hình runtime của chương trình.
 * Đầu ra: Không có.
 * Tác dụng phụ:
 *   - Thiết lập trạng thái ban đầu cho input SDL.
 */
void SDLInteraction::init(const RunConfig& config) {
    // TODO:
    // - Khởi tạo các thành phần cần thiết cho input SDL
    // - Có thể reset event queue hoặc trạng thái input
    w = config.screenWidth;
    h = config.screenHeight;
    cell_size = 67;
}

/**
 * Mô tả: Tạm dừng chương trình trong SDL.
 *        - Nếu có timeout > 0: delay trong khoảng thời gian tương ứng.
 *        - Nếu timeout == 0: chờ người dùng tương tác (nhấn phím hoặc click chuột).
 * Đầu vào:
 *   - timeout: thời gian chờ (milliseconds). Nếu = 0 thì chờ event từ người dùng.
 * Đầu ra: Không có.
 * Tác dụng phụ:
 *   - Có thể block thread hiện tại.
 *   - Có thể ném QuitException nếu người dùng đóng cửa sổ.
 */
void SDLInteraction::pause(int timeout) {
    // Nếu có timeout cụ thể -> delay trực tiếp bằng SDL
    if (timeout > 0) {
        SDL_Delay(timeout);
        return;
    }

    bool waiting = true;
    SDL_Event event;

    // Vòng lặp chờ sự kiện từ người dùng
    while (waiting) {
        // SDL_WaitEvent sẽ block cho tới khi có event
        if (SDL_WaitEvent(&event)) {
            // Nếu người dùng đóng cửa sổ -> thoát game
            if (waitForQuit(event)) {
            }
            // tương tự
            // if (event.type == SDL_QUIT) {
            //     throw QuitException();
            // }

            // Nếu có tương tác (nhấn phím hoặc click chuột) -> kết thúc pause
            if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
                waiting = false;
            }
        }
    }
}

void drawCurrentInput(const std::string& input) {
    SDL_Window* win = SDL_GetKeyboardFocus();
    if (!win) return;

    SDL_Renderer* renderer = SDL_GetRenderer(win);
    if (!renderer) return;

    int w, h;
    SDL_GetWindowSize(win, &w, &h);

    TTF_Font* inputFont = TTF_OpenFont("assets/font.ttf", 36);
    if (!inputFont) return;

    int boxW = 620;
    int boxH = 260;
    int boxX = w / 2 - boxW / 2;
    int boxY = h / 2 - boxH / 2;

    int x = boxX + 380;
    int y = boxY + 70;

    SDL_Rect clearBox = {x, y, 180, 50};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &clearBox);

    std::string shown = input.empty() ? "_" : input;

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface* surf = TTF_RenderText_Solid(inputFont, shown.c_str(), white);

    if (surf) {
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_Rect dst = {x, y, surf->w, surf->h};

        SDL_RenderCopy(renderer, tex, NULL, &dst);

        SDL_FreeSurface(surf);
        SDL_DestroyTexture(tex);
    }

    TTF_CloseFont(inputFont);
    SDL_RenderPresent(renderer);
}

/**
 * Mô tả: Lấy input kích thước bàn cờ từ người dùng qua SDL.
 * Đầu vào:
 *   - size: con trỏ lưu kết quả kích thước.
 * Đầu ra:
 *   - true nếu input hợp lệ, false nếu không hợp lệ.
 * Tác dụng phụ:
 *   - Cập nhật giá trị tại size nếu thành công.
 */
bool SDLInteraction::selectSize(int* size) {
    // TODO:
    // - Lắng nghe event từ SDL (keyboard/mouse)
    // - Parse input thành số nguyên
    // - Kiểm tra điều kiện hợp lệ (BOARD_N_MIN <= size <= BOARD_N_MAX)
    // - Trả về true nếu hợp lệ, ngược lại false
    // throw NotImplementedException();
    if (!waitForBoardSizeButton(size)){
        return false;
    }
    bool valid = (*size >= BOARD_N_MIN && *size <= BOARD_N_MAX);
    if (valid) {
        boardsize = *size;
    }
    return valid;
}

/**
 * Mô tả: Lấy input goal (số ô liên tiếp để thắng).
 * Đầu vào:
 *   - goal: con trỏ lưu giá trị goal.
 *   - size: kích thước bàn cờ hiện tại.
 * Đầu ra:
 *   - true nếu hợp lệ, false nếu không hợp lệ.
 * Tác dụng phụ:
 *   - Cập nhật goal nếu hợp lệ.
 */
bool SDLInteraction::selectGoal(int* goal, const int size) {
    // TODO:
    // - Lấy input từ SDL
    // - Parse thành số nguyên
    // - Kiểm tra điều kiện (3 <= goal <= size)
    // - Trả về true nếu hợp lệ
    // throw NotImplementedException();
    if (!waitForGoalButton(goal, size)){
        return false;
    }
    return (*goal >= 3 && *goal <= size);
}

/**
 * Mô tả: Lấy input chế độ chơi (PVP, PVE, EVE).
 * Đầu vào:
 *   - mode: con trỏ lưu giá trị GameMode.
 * Đầu ra:
 *   - true nếu hợp lệ, false nếu không hợp lệ.
 * Tác dụng phụ:
 *   - Cập nhật mode nếu hợp lệ.
 */
bool SDLInteraction::selectGameMode(GameMode* mode) {
    // TODO:
    // - Lắng nghe input từ SDL (phím số hoặc click)
    // - Map input sang GameMode tương ứng
    // - Validate giá trị (1-3)
    // throw NotImplementedException();
    SDL_Event event;
    while (true){
        while (SDL_PollEvent(&event)){
            waitForQuit(event);
            if (event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym){
                    case SDLK_1:
                        *mode = GameMode::PVP;
                        return true;
                    case SDLK_2:
                        *mode = GameMode::PVE;
                        return true;
                    case SDLK_3:
                        *mode = GameMode::EVE;
                        return true;
                    default:
                        return false;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int x = event.button.x;
                int y = event.button.y;

                SDL_Window* win = SDL_GetWindowFromID(event.button.windowID);

                int curW = w;
                int curH = h;
                SDL_GetWindowSize(win, &curW, &curH);

                int buttonW = 360;
                int buttonH = 115;
                int gapY = 22;
                int startX = w / 2 - buttonW / 2;
                int startY = 270;

                int x_pvp = startX;
                int y_pvp = startY;
                if (x >= x_pvp && x <= x_pvp + buttonW && y >= y_pvp && y <= y_pvp + buttonH){
                    *mode = GameMode::PVP;
                    return true;
                }
                int x_pve = startX;
                int y_pve = startY + gapY + buttonH;
                if (x >= x_pve && x <= x_pve + buttonW && y >= y_pve && y <= y_pve + buttonH){
                    *mode = GameMode::PVE;
                    return true;
                }
                int x_eve = startX;
                int y_eve = startY + 2 * (gapY + buttonH);
                if (x >= x_eve && x <= x_eve + buttonW && y >= y_eve && y <= y_eve + buttonH){
                    *mode = GameMode::EVE;
                    return true;
                }
            }
        }
        SDL_Delay(16);
    }
}

/**
 * Mô tả: Lấy input cấp độ bot.
 * Đầu vào:
 *   - levels: mảng lưu cấp độ bot.
 *   - index: vị trí bot cần gán.
 * Đầu ra:
 *   - true nếu hợp lệ, false nếu không hợp lệ.
 * Tác dụng phụ:
 *   - Cập nhật levels[index] nếu hợp lệ.
 */
bool SDLInteraction::selectBotLevel(BotLevel* levels, const int index) {
    // TODO:
    // - Kiểm tra index hợp lệ (0 hoặc 1)
    // - Lấy input từ SDL
    // - Map sang BotLevel (EASY, MEDIUM, HARD)
    // - Trả về true nếu hợp lệ
    // throw NotImplementedException();
    SDL_Event event;
    while (true){
        while (SDL_PollEvent(&event)){
            waitForQuit(event);
            if (event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym){
                    case SDLK_1:
                        levels[index] = BotLevel::EASY;
                        return true;
                    case SDLK_2:
                        levels[index] = BotLevel::MEDIUM;
                        return true;
                    case SDLK_3:
                        levels[index] = BotLevel::HARD;
                        return true;
                    default:
                        return false;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int x = event.button.x;
                int y = event.button.y;

                SDL_Window* win = SDL_GetWindowFromID(event.button.windowID);

                int curW = w;
                int curH = h;
                SDL_GetWindowSize(win, &curW, &curH);

                int buttonW = 360;
                int buttonH = 115;
                int gapY = 22;
                int startX = w / 2 - buttonW / 2;
                int startY = 270;

                int x_pvp = startX;
                int y_pvp = startY;
                if (x >= x_pvp && x <= x_pvp + buttonW && y >= y_pvp && y <= y_pvp + buttonH){
                    levels[index] = BotLevel::EASY;
                    return true;
                }
                int x_pve = startX;
                int y_pve = startY + gapY + buttonH;
                if (x >= x_pve && x <= x_pve + buttonW && y >= y_pve && y <= y_pve + buttonH){
                    levels[index] = BotLevel::MEDIUM;
                    return true;
                }
                int x_eve = startX;
                int y_eve = startY + 2 * (gapY + buttonH);
                if (x >= x_eve && x <= x_eve + buttonW && y >= y_eve && y <= y_eve + buttonH){
                    levels[index] = BotLevel::HARD;
                    return true;
                }
            }
        }
        SDL_Delay(16);
    }
}

bool SDLInteraction::waitForBoardSizeButton(int* val) {
    SDL_Event event;

    int boxW = 620;
    int boxH = 260;
    int boxX = 800 / 2 - boxW / 2;
    int boxY = 800 / 2 - boxH / 2;
    int buttonW = 95;
    int buttonH = 58;
    int gapX = 25;
    int gapY = 38;
    int totalW = 5 * buttonW + 4 * gapX;
    int startX = boxX + (boxW - totalW) / 2;
    int startY = boxY + 60;
    while (true) {
        while (SDL_PollEvent(&event)) {
            waitForQuit(event);
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mx = event.button.x;
                int my = event.button.y;
                for (int i = 0; i < 10; i++) {
                    int value = i + 3;
                    int row = i / 5;
                    int col = i % 5;
                    int x = startX + col * (buttonW + gapX);
                    int y = startY + row * (buttonH + gapY);
                    if (mx >= x && mx <= x + buttonW && my >= y && my <= y + buttonH) {
                        *val = value;
                        return true;
                    }
                }
            }
        }
        SDL_Delay(16);
    }
}

bool SDLInteraction::waitForGoalButton(int* val, const int size) {
    SDL_Event event;

    int boxW = 620;
    int boxH = 260;

    int currentW = w;
    int currentH = h;

    int boxX = currentW / 2 - boxW / 2;
    int boxY = currentH / 2 - boxH / 2;

    int maxGoal = size;

    if (maxGoal < 3) {
        maxGoal = 3;
    }

    if (maxGoal > 12) {
        maxGoal = 12;
    }

    int count = maxGoal - 2;

    int buttonW = 170;
    int buttonH = 82;

    int gapX = 45;
    int gapY = 35;

    int cols = 3;
    int startY = boxY + 65;

    while (true) {
        while (SDL_PollEvent(&event)) {
            waitForQuit(event);

            if (event.type == SDL_MOUSEBUTTONDOWN &&
                event.button.button == SDL_BUTTON_LEFT) {

                int mx = event.button.x;
                int my = event.button.y;

                SDL_Window* win = SDL_GetWindowFromID(event.button.windowID);
                if (win) {
                    SDL_GetWindowSize(win, &currentW, &currentH);

                    boxX = currentW / 2 - boxW / 2;
                    boxY = currentH / 2 - boxH / 2;
                    startY = boxY + 65;
                }

                for (int i = 0; i < count; i++) {
                    int value = i + 3;

                    int row = i / cols;
                    int col = i % cols;

                    int remaining = count - row * cols;
                    int itemsInThisRow = std::min(cols, remaining);

                    int rowTotalW = itemsInThisRow * buttonW + (itemsInThisRow - 1) * gapX;
                    int rowStartX = boxX + (boxW - rowTotalW) / 2;

                    int x = rowStartX + col * (buttonW + gapX);
                    int y = startY + row * (buttonH + gapY);

                    if (mx >= x && mx <= x + buttonW &&
                        my >= y && my <= y + buttonH) {

                        *val = value;
                        return true;
                    }
                }
            }
        }

        SDL_Delay(16);
    }
}
/**
 * Mô tả: Lấy nước đi từ người chơi (row, col) qua SDL.
 * Đầu vào:
 *   - row: con trỏ lưu hàng.
 *   - col: con trỏ lưu cột.
 * Đầu ra:
 *   - true nếu lấy được input hợp lệ, false nếu không.
 * Tác dụng phụ:
 *   - Cập nhật row, col nếu hợp lệ.
 */
bool SDLInteraction::getPlayerMove(int* row, int* col) {
    // TODO:
    // - Lắng nghe mouse click hoặc keyboard input
    // - Chuyển đổi tọa độ click thành (row, col)
    // - Validate phạm vi hợp lệ
    // throw NotImplementedException();
    SDL_Event event;
    SDL_Rect boardArea = {157, 190, 329, 329};

    while (true) {
        while (SDL_PollEvent(&event)) {
            waitForQuit(event);
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                return false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                int boardMaxPx = std::min(boardArea.w, boardArea.h);
                int cellSize = boardMaxPx / boardsize;
                int boardPx = cellSize * boardsize;

                int boardX = boardArea.x + (boardArea.w - boardPx) / 2;
                int boardY = boardArea.y + (boardArea.h - boardPx) / 2;
                if (mouseX < boardX || mouseX >= boardX + boardPx || mouseY < boardY || mouseY >= boardY + boardPx) {
                    return false;
                }
                *col = (mouseX - boardX) / cellSize;
                *row = (mouseY - boardY) / cellSize;
                return true;
            }
        }
        SDL_Delay(16);
    }
}
/**
 * Mô tả: Dọn dẹp tài nguyên liên quan đến SDL interaction.
 * Đầu vào: Không có.
 * Đầu ra: Không có.
 * Tác dụng phụ:
 *   - Giải phóng hoặc reset trạng thái input nếu cần.
 */
void SDLInteraction::close() {
    // TODO:
    // - Dọn dẹp trạng thái, nếu có resource thì giải phóng
}