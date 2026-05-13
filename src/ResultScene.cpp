#include "ResultScene.h"

#include "Constants.h"
#include "Game.h"
#include "raylib.h"

#include <cstdio>
#include <fstream>
#include <string>

ResultScene::ResultScene(Game& game, ScoreSummary summary)
    : Scene(game), summary_(summary) {
    loadAndSaveHighScore();
}

void ResultScene::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        game_.startGame();
        return;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        game_.goToMenu();
        return;
    }
}

void ResultScene::update(float) {}

void ResultScene::draw() {
    DrawCircleGradient(Constants::ScreenWidth / 2, Constants::ScreenHeight / 2, 520,
                       Fade(Color{80, 120, 255, 255}, 0.26f), BLANK);

    DrawText("RESULT", 370, 70, 56, RAYWHITE);

    char buffer[128];
    std::snprintf(buffer, sizeof(buffer), "Rank %c", summary_.rank);
    DrawText(buffer, 398, 145, 48, Color{130, 230, 255, 255});

    std::snprintf(buffer, sizeof(buffer), "Score: %d", summary_.score);
    DrawText(buffer, 330, 230, 30, RAYWHITE);

    std::snprintf(buffer, sizeof(buffer), "High Score: %d", highScore_);
    DrawText(buffer, 330, 270, 26, LIGHTGRAY);

    std::snprintf(buffer, sizeof(buffer), "Accuracy: %.1f%%", summary_.accuracy * 100.0f);
    DrawText(buffer, 330, 315, 26, LIGHTGRAY);

    std::snprintf(buffer, sizeof(buffer), "Max Combo: %d", summary_.maxCombo);
    DrawText(buffer, 330, 350, 26, LIGHTGRAY);

    std::snprintf(buffer, sizeof(buffer), "Perfect: %d", summary_.perfect);
    DrawText(buffer, 330, 405, 24, Color{100, 235, 255, 255});

    std::snprintf(buffer, sizeof(buffer), "Good:    %d", summary_.good);
    DrawText(buffer, 330, 435, 24, Color{120, 255, 150, 255});

    std::snprintf(buffer, sizeof(buffer), "Bad:     %d", summary_.bad);
    DrawText(buffer, 330, 465, 24, Color{255, 220, 80, 255});

    std::snprintf(buffer, sizeof(buffer), "Miss:    %d", summary_.miss);
    DrawText(buffer, 330, 495, 24, Color{255, 105, 150, 255});

    DrawText("[ ENTER ] Retry", 350, 590, 24, RAYWHITE);
    DrawText("[ ESC ] Menu", 376, 625, 24, LIGHTGRAY);
}

void ResultScene::loadAndSaveHighScore() {
    const std::string path = "assets/save/highscore.txt";

    std::ifstream in(path);
    if (in.is_open()) {
        in >> highScore_;
    }

    if (summary_.score > highScore_) {
        highScore_ = summary_.score;
        std::ofstream out(path, std::ios::trunc);
        if (out.is_open()) {
            out << highScore_ << '\n';
        }
    }
}
