/**
 * SDL Renderer cpp implementation
 *
 */

#include "renderer.h"

/* ---------- Importing ---------- */

#include <format>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <iostream>

#include "../game/setup.h"
#include "../utils/config.h"

/* ---------- Definitions ---------- */

SDLRenderer::SDLRenderer() : I_Renderer() {
}

/**
 * Mô tả: Destructor của SDLRenderer.
 * Đầu vào: Không.
 * Đầu ra: Không.
 * Tác dụng phụ: Không (việc giải phóng thực hiện trong close()).
 */
SDLRenderer::~SDLRenderer() {
}

/**
 * Mô tả: Khởi tạo SDL, window và renderer.
 * Đầu vào: config - cấu hình màn hình và layout.
 * Đầu ra: Không.
 * Tác dụng phụ:
 *   - Khởi tạo SDL subsystem.
 *   - Tạo window và renderer.
 *   - Thiết lập chế độ blend.
 * NOTE: Phải gọi trước khi render.
 */
void SDLRenderer::init(const RunConfig& config) {
    // read config
    int screenWidth = config.screenWidth;
    int screenHeight = config.screenHeight;
    w = screenWidth;
    h = screenHeight;
    // int boardPadding = config.boardPadding;
    // init(...)

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow(
        "TicTacToe Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screenWidth,
        screenHeight,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    font = TTF_OpenFont("assets/font.ttf", 17);
    invalidfont = TTF_OpenFont("assets/font.ttf", 20);
    titleFont = TTF_OpenFont("assets/font.ttf", 70);
    menuFont = TTF_OpenFont("assets/font.ttf", 32);
    normalFont = TTF_OpenFont("assets/font.ttf", 25);
    bigFont = TTF_OpenFont("assets/font.ttf", 48);
    SDL_Surface* iconSurface = IMG_Load("assets/images/icon.png");
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);
    SDL_Surface *xSurf = IMG_Load("assets/x.png");
    if (xSurf){
        xTexture = SDL_CreateTextureFromSurface(renderer, xSurf);
        SDL_FreeSurface(xSurf); 
    }    
    SDL_Surface *oSurf = IMG_Load("assets/o.png");
    if (oSurf){
        oTexture = SDL_CreateTextureFromSurface(renderer, oSurf);
        SDL_FreeSurface(oSurf); 
    }
    SDL_Surface* bgSurface = IMG_Load("assets/images/im1.png");
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
    SDL_Surface* logoSurf = IMG_Load("assets/images/logo.png");
    logo = SDL_CreateTextureFromSurface(renderer, logoSurf);
    SDL_FreeSurface(logoSurf);
    SDL_Surface* arrowSurf = IMG_Load("assets/images/im2.png");
    arrow = SDL_CreateTextureFromSurface(renderer, arrowSurf);
    SDL_FreeSurface(arrowSurf);
    SDL_Surface* starSurf = IMG_Load("assets/images/im3.png");
    star = SDL_CreateTextureFromSurface (renderer, starSurf);
    SDL_FreeSurface(starSurf);
    SDL_Surface* buttonSurf = IMG_Load("assets/images/button.png");
    button = SDL_CreateTextureFromSurface (renderer, buttonSurf);
    SDL_FreeSurface(buttonSurf);
    SDL_Surface* bgSurface2 = IMG_Load("assets/images/im4.png");
    backgroundTexture2 = SDL_CreateTextureFromSurface(renderer, bgSurface2);
    SDL_FreeSurface(bgSurface2);
    SDL_Surface* bgSurface3 = IMG_Load("assets/images/im5.png");
    backgroundTexture3 = SDL_CreateTextureFromSurface(renderer, bgSurface3);
    SDL_FreeSurface(bgSurface3);
    SDL_Surface* bgSurface4 = IMG_Load("assets/images/im6.png");
    backgroundTexture4 = SDL_CreateTextureFromSurface(renderer, bgSurface4);
    SDL_FreeSurface(bgSurface4);
    SDL_Surface* bgSurface5 = IMG_Load("assets/images/im7.png");
    backgroundTexture5 = SDL_CreateTextureFromSurface(renderer, bgSurface5);
    SDL_FreeSurface(bgSurface5);
    SDL_Surface* bgSurface6 = IMG_Load("assets/images/im8.png");
    backgroundTexture6 = SDL_CreateTextureFromSurface(renderer, bgSurface6);
    SDL_FreeSurface(bgSurface6);
    SDL_Surface*snowSurf = IMG_Load("assets/images/snow.png");
    snow = SDL_CreateTextureFromSurface(renderer, snowSurf);
    SDL_FreeSurface(snowSurf);
    SDL_Surface* boardSurf = IMG_Load("assets/images/board.png");
    boardgame = SDL_CreateTextureFromSurface(renderer, boardSurf);
    SDL_FreeSurface(boardSurf);

    // }
    // load font
    // font = TTF_OpenFont("assets/font.ttf", font_size);
}

/**
 * Mô tả: Xóa toàn bộ nội dung màn hình (background tối).
 * Đầu vào: Không.
 * Đầu ra: Không.
 * Tác dụng phụ: Reset frame hiện tại.
 */
void SDLRenderer::clearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // dark background
    SDL_RenderClear(renderer);
}

/**
 * Mô tả: Hiển thị frame đã render lên màn hình.
 * Đầu vào: Không.
 * Đầu ra: Không.
 * Tác dụng phụ: Swap buffer để hiển thị nội dung.
 */
void SDLRenderer::renderPresent() {
    SDL_RenderPresent(renderer);
}

/**
 * Mô tả: Vẽ hình chữ nhật lên renderer.
 * Đầu vào:
 *   - x, y: tọa độ.
 *   - w, h: kích thước.
 *   - color: màu sắc.
 *   - filled: true nếu fill, false nếu vẽ viền.
 * Đầu ra: Không.
 * Tác dụng phụ: Vẽ trực tiếp lên renderer.
 */
void SDLRenderer::drawRect(int x, int y, int w, int h, SDL_Color color, bool filled) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    if (filled)
        SDL_RenderFillRect(renderer, &rect);
    else
        SDL_RenderDrawRect(renderer, &rect);
}

/**
 * Mô tả: Hiển thị menu lựa chọn.
 * Đầu vào: selectType, context.
 * Đầu ra: Không.
 * Tác dụng phụ: Vẽ UI lên màn hình.
 * TODO:
 *   - Bước 1: Xác định loại menu.
 *   - Bước 2: Render text tương ứng.
 *   - Trường hợp biên: selectType không hợp lệ.
 */
void SDLRenderer::showSelectMenu(SelectType selectType, int context) {
    // TODO: Render menu UI tương ứng với selectType
    // throw NotImplementedException();
    if (selectType != SelectType::PLAYER_UI) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
    SDL_RenderPresent(renderer);
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};
    SDL_Color blue = {0, 0, 255, 255};
    SDL_Color smallWhite = {220, 220, 230, 220};
    SDL_Color titleWhite = {245, 245, 255, 255};
    SDL_Color glowBlue = {170, 210, 255, 80};
    SDL_Color hintColor = {235, 245, 255, 255};
    SDL_Color buttonText = {120, 220, 255, 255};
    SDL_Color NumberShadow = {35, 75, 105, 180};
    SDL_Color NumberColor = {155, 230, 255, 255};
    int boxW = 620;
    int boxH = 260;
    int boxX = w / 2 - boxW / 2;
    int boxY = h / 2 - boxH / 2;
    auto renderText = [&](TTF_Font* useFont, const std::string& text, int x, int y, SDL_Color color, bool centered = false) {
        SDL_Surface* surf = TTF_RenderText_Blended(useFont, text.c_str(), color);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_Rect dst = {x, y, surf->w, surf->h};
        if (centered){
             dst.x -= surf->w / 2; dst.y -= surf->h / 2; 
            }
        SDL_RenderCopy(renderer, tex, NULL, &dst);
        SDL_FreeSurface(surf);
        SDL_DestroyTexture(tex);
    };
    auto renderGlowText = [&](TTF_Font* useFont, const std::string& text, int x, int y, SDL_Color mainColor, SDL_Color glowColor) {
        for (int ox = -3; ox <= 3; ox++) for (int oy = -3; oy <= 3; oy++) if (ox != 0 || oy != 0) renderText(useFont, text, x + ox, y + oy, glowColor, true);
        renderText(useFont, text, x, y, mainColor, true);
    };
    switch (selectType){
        case SelectType::TITLE_UI: {
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_RenderCopy(renderer, snow, NULL, NULL);
            SDL_SetRenderDrawColor(renderer, 0, 0, 20, 70);
            SDL_Rect overlay = {0, 0, w, h};
            SDL_RenderFillRect(renderer, &overlay);
            SDL_Color titleWhite = {245, 245, 255, 255};
            SDL_Color glowBlue   = {170, 210, 255, 80};
            renderGlowText(titleFont, "TIC TAC TOE", w / 2, 180, titleWhite, glowBlue);
            SDL_Color selectedWhite = {255, 255, 255, 255};
            SDL_Color menuWhite = {180, 185, 200, 255};
            renderText(menuFont, "START GAME", w / 2, 360, selectedWhite, true);

            SDL_Rect srcLeft = {0, 250, 768, 520};
            SDL_Rect srcRight = {768, 250, 768, 520};

            SDL_Rect dstLeft = {220, 320, 110, 75};
            SDL_Rect dstRight = {472, 320, 110, 75};
            int currentW = 0;
            int currentH = 0;
            SDL_GetWindowSize(window, &currentW, &currentH);
            renderText(font, std::to_string(currentW) + " x " + std::to_string(currentH), 20, 20, white, false);
            SDL_RenderCopy(renderer, arrow, &srcLeft, &dstLeft);
            SDL_RenderCopy(renderer, arrow, &srcRight, &dstRight);
            renderText(menuFont, "OPTIONS", w / 2, 420, menuWhite, true);
            renderText(menuFont, "QUIT GAME", w / 2, 480, menuWhite, true);
            SDL_Rect starRect = {w / 2 - 65, 475, 128, 128};
            SDL_RenderCopy(renderer, star, NULL, &starRect);
            SDL_Rect logoRect = {w - 90, h - 90, 48, 48};
            SDL_RenderCopy(renderer, logo, NULL, &logoRect);
            renderText(font, "grapily", w - 165, h - 75, smallWhite, false);
            renderText(font, "made with love", 60, h - 60, smallWhite, false);
            renderText(font, "Version 1.0", 60, h - 83, smallWhite, false);
            break;
        }
        case SelectType::SIZE_UI: {
            SDL_RenderCopy(renderer, backgroundTexture2, NULL, NULL);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_RenderCopy(renderer, snow, NULL, NULL);
            SDL_SetRenderDrawColor(renderer, 10, 25, 60, 45);
            SDL_Rect overlay = {0, 0, w, h};
            SDL_RenderFillRect(renderer, &overlay);
            renderGlowText(bigFont, "Board Size", w / 2, 160, titleWhite, glowBlue);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Rect srcLeft = {0, 250, 768, 520};
            SDL_Rect srcRight = {768, 250, 768, 520};

            SDL_Rect dstLeft = {220 - 35, 320 - 140, 110, 75};
            SDL_Rect dstRight = {472 + 35, 320 - 140, 110, 75};

            SDL_RenderCopy(renderer, arrow, &srcLeft, &dstLeft);
            SDL_RenderCopy(renderer, arrow, &srcRight, &dstRight);
            renderText(normalFont, "Choose a Board Size", w / 2, boxY - 50, hintColor, true);
            SDL_SetRenderDrawColor(renderer, 220, 235, 255, 160);
            SDL_RenderDrawLine(renderer, w / 2 - 160, boxY - 20, w / 2 + 160, boxY - 20);
            SDL_Rect starRect1 = {w / 2 - 65 + 28, 475 + 25, 128, 128};
            SDL_RenderCopy(renderer, star, NULL, &starRect1);
            SDL_Rect starRect2 = {w / 2 - 65 - 28, 475 + 25, 128, 128};
            SDL_RenderCopy(renderer, star, NULL, &starRect2);
            SDL_Rect borderOuter = {boxX, boxY, boxW, boxH};
            SDL_RenderDrawRect(renderer, &borderOuter);
            SDL_Rect borderMiddle1 = {boxX + 1, boxY + 1, boxW - 2, boxH - 2};
            SDL_RenderDrawRect(renderer, &borderMiddle1);
            SDL_Rect borderMiddle2 = {boxX + 2, boxY + 2, boxW - 4, boxH - 4};
            SDL_RenderDrawRect(renderer, &borderMiddle2);
            SDL_Rect borderInner1 = {boxX + 3, boxY + 3, boxW - 6, boxH - 6};
            SDL_RenderDrawRect(renderer, &borderInner1);
            SDL_Rect borderInner2 = {boxX + 4, boxY + 4, boxW - 8, boxH - 8};
            SDL_RenderDrawRect(renderer, &borderInner2);
            SDL_Rect borderInner3 = {boxX + 5, boxY + 5, boxW - 10, boxH - 10};
            SDL_RenderDrawRect(renderer, &borderInner3);
            SDL_Rect borderInner4 = {boxX + 6, boxY + 6, boxW - 12, boxH - 12};
            SDL_RenderDrawRect(renderer, &borderInner4);
            int buttonW = 95;
            int buttonH = 58;
            int gap = 18;
            int startX = w / 2 - (5 * buttonW + 4 * gap) / 2;
            int startY = boxY + 50;
            int mouseX, mouseY;
            for (int i = 0; i < 10; i++) {
                int value = i + 3;
                int row = i / 5;
                int col = i % 5;
                int x = startX + col * (buttonW + gap );
                int y = startY + row * (buttonH + gap + 20);
                SDL_Rect btn = {x, y, buttonW, buttonH};
                SDL_SetRenderDrawColor(renderer, 20, 35, 60, 120);
                SDL_RenderFillRect(renderer, &btn);

                SDL_SetRenderDrawColor(renderer, 230, 240, 255, 190);
                SDL_RenderDrawRect(renderer, &btn);

                renderText(menuFont, std::to_string(value), x + buttonW / 2, y + buttonH / 2, buttonText, true);
                renderText(menuFont, std::to_string(value), x + buttonW / 2 + 2, y + buttonH / 2 + 2, NumberShadow, true);
            }
            break;
        }
        case SelectType::GOAL_UI: {
            SDL_RenderCopy(renderer, backgroundTexture3, NULL, NULL);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 0, 20, 30);
            SDL_Rect overlay = {0, 0, w, h};
            SDL_RenderFillRect(renderer, &overlay);
            renderGlowText(bigFont, "Goal to win", w / 2, 160, titleWhite, glowBlue);
            renderText(normalFont, "Choose a Goal condition ", w / 2, boxY - 50, hintColor, true);
            SDL_Rect srcLeft = {0, 250, 768, 520};
            SDL_Rect srcRight = {768, 250, 768, 520};

            SDL_Rect dstLeft = {220 - 78, 320 - 140, 110, 75};
            SDL_Rect dstRight = {472 + 70, 320 - 140, 110, 75};

            SDL_RenderCopy(renderer, arrow, &srcLeft, &dstLeft);
            SDL_RenderCopy(renderer, arrow, &srcRight, &dstRight);

            SDL_Rect starRect1 = {w / 2 - 65 + 55, 475 + 25 - 260, 128, 128};
            SDL_RenderCopy(renderer, star, NULL, &starRect1);
            SDL_Rect starRect2 = {w / 2 - 65 - 55, 475 + 25 - 260, 128, 128};
            SDL_RenderCopy(renderer, star, NULL, &starRect2);
            SDL_Rect starRect3 = {w / 2 - 65, 475 + 25 - 260, 128, 128};
            SDL_RenderCopy(renderer, star, NULL, &starRect3);

            SDL_SetRenderDrawColor(renderer, 220, 235, 255, 160);
            SDL_RenderDrawLine(renderer, w / 2 - 160, boxY - 20, w / 2 + 160, boxY - 20);

            int maxGoal = context;
            int count = maxGoal - 2;
            int buttonW = 180;
            int buttonH = 88;

            int gapX = 35;
            int gapY = 28;
            int cols = 3;
            int startY = boxY + 65;
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

                SDL_Rect btn = {x, y, buttonW, buttonH};
                SDL_RenderCopy(renderer, button, NULL, &btn);

                renderText(menuFont, std::to_string(value), x + buttonW / 2, y + buttonH / 2, NumberColor, true);
                renderText(menuFont, std::to_string(value), x + buttonW / 2 + 2, y + buttonH / 2 + 2, NumberShadow, true);
            };
            break;
        }
        case SelectType::GAME_MODE_UI: {
            SDL_RenderCopy(renderer, backgroundTexture4, NULL, NULL);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_RenderCopy(renderer, snow, NULL, NULL);
            SDL_SetRenderDrawColor(renderer, 5, 12, 28, 35);
            SDL_Rect overlay = {0, 0, w, h};
            SDL_RenderFillRect(renderer, &overlay);
            renderGlowText(bigFont, "Gamemode", w / 2, 160, titleWhite, glowBlue);
            renderText(normalFont, "Choose a Mode to play ", w / 2, boxY - 50, hintColor, true);
            SDL_Rect srcLeft = {0, 250, 768, 520};
            SDL_Rect srcRight = {768, 250, 768, 520};

            SDL_Rect dstLeft = {220 - 63, 320 - 140, 110, 75};
            SDL_Rect dstRight = {472 + 55, 320 - 140, 110, 75};

            SDL_RenderCopy(renderer, arrow, &srcLeft, &dstLeft);
            SDL_RenderCopy(renderer, arrow, &srcRight, &dstRight);
            
            SDL_SetRenderDrawColor(renderer, 220, 235, 255, 160);
            SDL_RenderDrawLine(renderer, w / 2 - 160, boxY - 20, w / 2 + 160, boxY - 20);
            SDL_Rect starRect1 = {220 - 60, 320 - 225, 128, 128};
            SDL_RenderCopy(renderer, star, NULL, &starRect1);
            SDL_Rect starRect2 = {472 + 40, 320 - 225, 128, 128};
            SDL_RenderCopy(renderer, star, NULL, &starRect2);
            int buttonW = 360;
            int buttonH = 115;
            int gapY = 22;
            int startX = w / 2 - buttonW / 2;
            int startY = 270;
            std::string names[3] = {"Player vs Player", "Player vs Bot", "Bot vs Bot"};
            for (int i = 0; i < 3; i++){
                int x = startX;
                int y = startY + i * (buttonH + gapY);
                SDL_Rect btn = {x, y, buttonW, buttonH};
                SDL_RenderCopy(renderer, button, NULL, &btn);
                renderText(menuFont, names[i], x + buttonW / 2, y + buttonH / 2, NumberColor, true);
                renderText(menuFont, names[i], x + buttonW / 2 + 2, y + buttonH / 2 + 2, NumberShadow, true);
            }           
            break;
       }
        case SelectType::BOT_LEVEL_UI:{
            SDL_RenderCopy(renderer, backgroundTexture5, NULL, NULL);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_RenderCopy(renderer, snow, NULL, NULL);
            SDL_SetRenderDrawColor(renderer, 5, 12, 28, 65);
            SDL_Rect overlay = {0, 0, w, h};
            SDL_RenderFillRect(renderer, &overlay);
            renderGlowText(bigFont, "Bot Level Selection", w / 2, 160, titleWhite, glowBlue);
            renderText(normalFont, "Choose a Bot difficulty", w / 2, boxY - 50, hintColor, true);
            SDL_Rect srcLeft = {0, 250, 768, 520};
            SDL_Rect srcRight = {768, 250, 768, 520};

            SDL_Rect dstLeft = {220 - 63, 320 - 140, 110, 75};
            SDL_Rect dstRight = {472 + 60, 320 - 140, 110, 75};

            SDL_RenderCopy(renderer, arrow, &srcLeft, &dstLeft);
            SDL_RenderCopy(renderer, arrow, &srcRight, &dstRight);
            SDL_SetRenderDrawColor(renderer, 220, 235, 255, 160);
            SDL_RenderDrawLine(renderer, w / 2 - 160, boxY - 20, w / 2 + 160, boxY - 20);
            SDL_Rect starRect1 = {220 - 170, 320 - 225, 128, 128};
            SDL_RenderCopy(renderer, star, NULL, &starRect1);
            SDL_Rect starRect2 = {472 + 155, 320 - 225, 128, 128};
            SDL_RenderCopy(renderer, star, NULL, &starRect2);
            int buttonW = 360;
            int buttonH = 115;
            int gapY = 22;
            int startX = w / 2 - buttonW / 2;
            int startY = 270;
            std::string names[3] = {"Easy", "Medium", "Hard"};
            for (int i = 0; i < 3; i++){
                int x = startX;
                int y = startY + i * (buttonH + gapY);
                SDL_Rect btn = {x, y, buttonW, buttonH};
                SDL_RenderCopy(renderer, button, NULL, &btn);
                renderText(menuFont, names[i], x + buttonW / 2, y + buttonH / 2, NumberColor, true);
                renderText(menuFont, names[i], x + buttonW / 2 + 2, y + buttonH / 2 + 2, NumberShadow, true);
            }        
            break; 
        }
        case SelectType::PLAYER_UI: {
            SDL_Color move = {220, 245, 255, 255};
            renderText(invalidfont, "Move", 575, 315, move, true);
            break;
        }
        case SelectType::MUL_BOT_LEVEL_UI: {
            SDL_RenderCopy(renderer, backgroundTexture6, NULL, NULL);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_RenderCopy(renderer, snow, NULL, NULL);
            SDL_SetRenderDrawColor(renderer, 5, 12, 28, 65);
            SDL_Rect overlay = {0, 0, w, h};
            SDL_RenderFillRect(renderer, &overlay);
            renderGlowText(bigFont, "Bot Level Selection", w / 2, 160, titleWhite, glowBlue);
            renderText(normalFont, "Choose a Bot difficulty", w / 2, boxY - 50, hintColor, true);
            SDL_Rect srcLeft = {0, 250, 768, 520};
            SDL_Rect srcRight = {768, 250, 768, 520};

            SDL_Rect dstLeft = {220 - 63, 320 - 140, 110, 75};
            SDL_Rect dstRight = {472 + 60, 320 - 140, 110, 75};

            SDL_RenderCopy(renderer, arrow, &srcLeft, &dstLeft);
            SDL_RenderCopy(renderer, arrow, &srcRight, &dstRight);
            SDL_SetRenderDrawColor(renderer, 220, 235, 255, 160);
            SDL_RenderDrawLine(renderer, w / 2 - 160, boxY - 20, w / 2 + 160, boxY - 20);
            SDL_Rect starRect1 = {220 - 170, 320 - 225, 128, 128};
            SDL_RenderCopy(renderer, star, NULL, &starRect1);
            SDL_Rect starRect2 = {472 + 155, 320 - 225, 128, 128};
            SDL_RenderCopy(renderer, star, NULL, &starRect2);
            int buttonW = 360;
            int buttonH = 115;
            int gapY = 22;
            int startX = w / 2 - buttonW / 2;
            int startY = 270;
            std::string names[3] = {"Easy", "Medium", "Hard"};
            for (int i = 0; i < 3; i++){
                int x = startX;
                int y = startY + i * (buttonH + gapY);
                SDL_Rect btn = {x, y, buttonW, buttonH};
                SDL_RenderCopy(renderer, button, NULL, &btn);
                renderText(menuFont, names[i], x + buttonW / 2, y + buttonH / 2, NumberColor, true);
                renderText(menuFont, names[i], x + buttonW / 2 + 2, y + buttonH / 2 + 2, NumberShadow, true);
            }
            if (context == 0){
                renderGlowText(bigFont, "1st bot", w / 2, 110, titleWhite, glowBlue);
            }
            else if (context == 1){
                renderGlowText(bigFont, "2nd bot", w / 2, 110, titleWhite, glowBlue);
            }            
            break; 
        }
        default: 
            break;
    }
    SDL_RenderPresent(renderer);
}

/**
 * Mô tả: Hiển thị thông báo lựa chọn không hợp lệ.
 * Đầu vào: selectType, context.
 * Đầu ra: Không.
 * Tác dụng phụ: Hiển thị thông báo lỗi.
 * TODO:
 *   - Bước 1: Xác định loại lỗi.
 *   - Bước 2: Render text cảnh báo.
 */
void SDLRenderer::showInvalidSelect(SelectType selectType, int context) {
    // TODO: Render thông báo lỗi
    // throw NotImplementedException();
    SDL_Color red = {255, 80, 80, 255};
    SDL_Surface *surf = TTF_RenderText_Solid(invalidfont, "INVALID SELECTION", red);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_Rect dst = {20, h-40, surf->w, surf->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(renderer);
}

/**
 * Mô tả: Hiển thị thông báo lựa chọn hợp lệ.
 * Đầu vào: selectType, context.
 * Đầu ra: Không.
 * Tác dụng phụ: Hiển thị xác nhận.
 * TODO:
 *   - Bước 1: Xác định loại selection.
 *   - Bước 2: Render thông báo thành công.
 */
void SDLRenderer::showValidSelect(SelectType selectType, int context) {
    // TODO: Render thông báo thành công
    // throw NotImplementedException();
    SDL_Color green = {0, 255, 0, 255};
    SDL_Surface *surf = TTF_RenderText_Solid(font, "Valid selection", green);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_Rect dst = {20, h-40, surf->w, surf->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(renderer);
}

/**
 * Mô tả: Vẽ bàn cờ lên màn hình.
 * Đầu vào: board, size.
 * Đầu ra: Không.
 * Tác dụng phụ: Render grid và ký hiệu.
 * TODO:
 *   - Bước 1: Tính toán layout ô.
 *   - Bước 2: Vẽ grid.
 *   - Bước 3: Vẽ X/O.
 */
void SDLRenderer::displayBoard(const char board[][BOARD_N_MAX], const int size) {
    clearScreen();
    SDL_Rect dst = {0, 0, w, h};
    SDL_Color blue = {75, 70, 210, 255};
    SDL_Color red  = {255, 0, 20, 255};
    SDL_RenderCopy(renderer, boardgame, NULL, NULL);
    SDL_Surface *surf1 = TTF_RenderText_Solid(invalidfont, "P1", red);
    SDL_Texture *texture1 = SDL_CreateTextureFromSurface(renderer, surf1);
    SDL_Surface *surf2 = TTF_RenderText_Solid(invalidfont, "P2", blue);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, surf2);

    SDL_Rect dst1 = {565, 175, surf1->w, surf1->h};
    SDL_Rect dst2 = {565, 240, surf2->w, surf2->h};

    SDL_RenderCopy(renderer, texture1, NULL, &dst1);
    SDL_RenderCopy(renderer, texture2, NULL, &dst2);

    SDL_Rect boardArea = {157, 190, 329, 329};
    int boardMaxPx = std::min(boardArea.w, boardArea.h);
    int cellSize = boardArea.w / size;
    int boardPx = cellSize * size;
    int boardX = boardArea.x + (boardArea.w - boardPx) / 2;
    int boardY = boardArea.y + (boardArea.h - boardPx) / 2;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 170, 225, 255, 255);
    for (int i = 1; i < size; i++){
        int lineThickness = 4;
        int x = boardX + i * cellSize;
        SDL_Rect vLine = {x - lineThickness / 2, boardY, lineThickness, boardPx};
        SDL_RenderFillRect(renderer, &vLine);
        int y = boardY + i * cellSize;
        SDL_Rect hLine = {boardX, y - lineThickness / 2, boardPx, lineThickness};
        SDL_RenderFillRect(renderer, &hLine);
    }
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            int x = boardX + c * cellSize;
            int y = boardY + r * cellSize;

            int pad = std::max(6, cellSize / 7);

            SDL_Rect pieceRect = {
                x + pad,
                y + pad,
                cellSize - 2 * pad,
                cellSize - 2 * pad
            };

            if (board[r][c] == 'X') {
                if (xTexture) {
                    SDL_RenderCopy(renderer, xTexture, NULL, &pieceRect);
                }
            }
            else if (board[r][c] == 'O') {
                if (oTexture) {
                    SDL_RenderCopy(renderer, oTexture, NULL, &pieceRect);
                }
            }
        }
    }

    SDL_RenderPresent(renderer);
}

/**
 * Mô tả: Hiển thị nước đi vừa thực hiện.
 * Đầu vào: row, col.
 * Đầu ra: Không.
 * Tác dụng phụ: Highlight ô.
 * TODO:
 *   - Bước 1: Xác định vị trí ô.
 *   - Bước 2: Vẽ highlight.
 */
void SDLRenderer::showMove(const int row, const int col) {
    // TODO: Highlight move
    // throw NotImplementedException();
}

/**
 * Mô tả: Hiển thị thông báo nước đi không hợp lệ.
 * Đầu vào: Không.
 * Đầu ra: Không.
 * Tác dụng phụ: Hiển thị lỗi.
 * TODO:
 *   - Bước 1: Render thông báo lỗi.
 */
void SDLRenderer::showInvalidMove() {
    // TODO: Render invalid move message
    // throw NotImplementedException();
    SDL_Color red = {255, 80, 80, 255};
    SDL_Surface *surf = TTF_RenderText_Solid(invalidfont, "invalid move", red);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_Rect dst = {460, 630, surf->w, surf->h};

    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(renderer);
}

/**
 * Mô tả: Hiển thị người chơi hiện tại.
 * Đầu vào: player, is_bot.
 * Đầu ra: Không.
 * Tác dụng phụ: Hiển thị thông tin turn.
 * TODO:
 *   - Bước 1: Xác định text.
 *   - Bước 2: Render lên màn hình.
 */
void SDLRenderer::showPlayer(const int player, const bool is_bot) {
    // TODO: Render player info
    // throw NotImplementedException();
    std::string text;
    SDL_Color color;
    if (is_bot){
        text = "Bot move";
        color = {220, 245, 255, 255};
    }
    else if (player == 0) {
        text = "Player 1";
        color = {255, 0, 20, 255};
    }
    else {
        text = "Player 2";
        color = {75, 70, 210, 255};
    }
    SDL_Surface *surf = TTF_RenderText_Solid(invalidfont, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_Rect dst = {225, 630, surf->w, surf->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
    
    SDL_RenderPresent(renderer);
}

/**
 * Mô tả: Hiển thị kết quả game.
 * Đầu vào: winner, is_bot, winLine.
 * Đầu ra: Không.
 * Tác dụng phụ: Hiển thị kết quả và highlight đường thắng.
 * TODO:
 *   - Bước 1: Kiểm tra draw hoặc win.
 *   - Bước 2: Render text.
 *   - Bước 3: Highlight winLine nếu có.
 */
void SDLRenderer::showResult(const int winner, const bool is_bot, const WinLine* winLine) {
    // TODO: Render result
    // throw NotImplementedException();
    if (winLine != nullptr){
        int cell_size = (w -2 * padding) / boardSize;
        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 180);
        auto start = winLine->cells.front();
        auto end = winLine->cells.back();
        int x1 = padding + start.second * cell_size + cell_size / 2;
        int y1 = padding + start.first * cell_size + cell_size / 2;
        int x2 = padding + end.second * cell_size + cell_size / 2;
        int y2 = padding + end.first * cell_size + cell_size / 2;
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
    std::string text;
    SDL_Color color;
    if (winner == DRAW_RESULT){
        text = "It's a draw";
        color = {255, 120, 220, 255};
    }
    else if (is_bot){
        text = "Bot wins gggg";
        color = {100, 200, 255, 255};
    }
    else {
        text = "Player " + std::to_string(winner + 1) + " wins";
        color = {255, 200, 50,  255};
    }
    SDL_Surface* surf = TTF_RenderText_Solid(menuFont, text.c_str(), color);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
    int background_w = surf->w + 40;
    int background_h = surf->h + 40;
    SDL_Rect background = {w/2 -background_w / 2, h/2 - background_h / 2, background_w, background_h};
    SDL_RenderFillRect(renderer, &background);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_Rect dst = {w/2 - surf->w/2, h/2 - surf->h/2, surf->w, surf->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
    SDL_RenderPresent(renderer);
}

/**
 * Mô tả: In kết quả ra stdout (judge mode).
 * Đầu vào: gameResult.
 * Đầu ra: Không.
 * Tác dụng phụ: In console.
 * TODO:
 *   - Bước 1: Format output.
 *   - Bước 2: In ra std::cout.
 */
void SDLRenderer::printResult(const GameResult& gameResult) {
    // TODO: Print result
    // throw NotImplementedException();
    std::cout << gameResult.winner << " " << gameResult.turns;
}

/**
 * Mô tả: Giải phóng tài nguyên SDL.
 * Đầu vào: Không.
 * Đầu ra: Không.
 * Tác dụng phụ:
 *   - Destroy renderer và window.
 *   - Shutdown SDL subsystem.
 */
void SDLRenderer::close() {
    // if (font) {
    //     TTF_CloseFont(font);
    //     font = nullptr;
    // }
    if (font){
        TTF_CloseFont(font);
        font = nullptr;
    }
    if (xTexture){
        SDL_DestroyTexture(xTexture);
        xTexture = nullptr;
    }
    if (oTexture){
        SDL_DestroyTexture(oTexture);
        oTexture = nullptr;
    }
    if (bigFont && bigFont != font) {
        TTF_CloseFont(bigFont);
        bigFont = nullptr;
    }
    if (logo) {
        SDL_DestroyTexture(logo);
        logo = nullptr;
    }
    if (arrow) {
        SDL_DestroyTexture(arrow);
        arrow = nullptr;
    }
    if (star) {
        SDL_DestroyTexture(star);
        star = nullptr;
    }
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}