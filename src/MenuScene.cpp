#include "MenuScene.h"

#include "Constants.h"
#include "Game.h"
#include "raylib.h"

#include <cmath>

MenuScene::MenuScene(Game& game) : Scene(game) {}

void MenuScene::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        game_.startGame();
    }
    if (IsKeyPressed(KEY_H)) {
        game_.goToHelp();
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        game_.requestQuit();
    }
}

void MenuScene::update(float dt) {
    elapsed_ += dt;
}

void MenuScene::draw() {
    for (int i = 0; i < 32; ++i) {
        const int y = i * 24;
        DrawLine(0, y, Constants::ScreenWidth, y, Fade(Color{80, 100, 160, 255}, 0.08f));
    }

    for (int lane = 0; lane < 4; ++lane) {
        const float x = Constants::laneCenterX(lane);
        const float pulse = 0.35f + 0.15f * std::sin(elapsed_ * 2.0f + lane);
        DrawRectangleRounded(Rectangle{x - 34.0f, 160.0f, 68.0f, 360.0f}, 0.45f, 16, Fade(Color{90, 180, 255, 255}, pulse));
    }

    const char* title = "NANKAI RHYTHM";
    const int titleFontSize = 56;
    const int titleWidth = MeasureText(title, titleFontSize);
    DrawText(title, (Constants::ScreenWidth - titleWidth) / 2 + 4, 116, titleFontSize, Fade(BLACK, 0.45f));
    DrawText(title, (Constants::ScreenWidth - titleWidth) / 2, 110, titleFontSize, RAYWHITE);

    const char* subtitle = "C++ Graphical Rhythm Game";
    const int subtitleWidth = MeasureText(subtitle, 24);
    DrawText(subtitle, (Constants::ScreenWidth - subtitleWidth) / 2, 184, 24, Fade(RAYWHITE, 0.72f));

    DrawText("[ ENTER ] Start Game", 350, 310, 28, Color{130, 230, 255, 255});
    DrawText("[ H ] Help", 409, 360, 24, LIGHTGRAY);
    DrawText("[ ESC ] Quit", 395, 400, 24, LIGHTGRAY);

    DrawText("D", static_cast<int>(Constants::laneCenterX(0)) - 10, 550, 30, Color{80, 200, 255, 255});
    DrawText("F", static_cast<int>(Constants::laneCenterX(1)) - 10, 550, 30, Color{130, 255, 130, 255});
    DrawText("J", static_cast<int>(Constants::laneCenterX(2)) - 10, 550, 30, Color{255, 210, 80, 255});
    DrawText("K", static_cast<int>(Constants::laneCenterX(3)) - 10, 550, 30, Color{255, 100, 170, 255});
}
