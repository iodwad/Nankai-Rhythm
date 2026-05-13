#include "HelpScene.h"

#include "Constants.h"
#include "Game.h"
#include "raylib.h"

HelpScene::HelpScene(Game& game) : Scene(game) {}

void HelpScene::handleInput() {
    if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER)) {
        game_.goToMenu();
    }
}

void HelpScene::update(float) {}

void HelpScene::draw() {
    DrawText("HELP", 80, 70, 48, RAYWHITE);
    DrawText("Press D / F / J / K when notes reach the judgment line.", 80, 150, 24, LIGHTGRAY);
    DrawText("Perfect: <= 80ms", 80, 210, 24, Color{100, 230, 255, 255});
    DrawText("Good:    <= 160ms", 80, 250, 24, Color{120, 255, 150, 255});
    DrawText("Bad:     <= 250ms", 80, 290, 24, Color{255, 215, 80, 255});
    DrawText("Miss:    note passed the line", 80, 330, 24, Color{255, 120, 160, 255});

    DrawText("Goal: keep combo, improve accuracy, and reach Rank S.", 80, 410, 24, LIGHTGRAY);
    DrawText("[ ENTER / ESC ] Back to Menu", 80, 560, 24, RAYWHITE);
}
