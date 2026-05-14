#include "Game.h"

#include "Constants.h"
#include "HelpScene.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "raylib.h"

Game::Game() {
    InitWindow(Constants::ScreenWidth, Constants::ScreenHeight, "Nankai Rhythm");
    InitAudioDevice();
    SetExitKey(0);
    SetTargetFPS(60);
    goToMenu();
}

Game::~Game() {
    currentScene_.reset();
    if (IsAudioDeviceReady()) {
        CloseAudioDevice();
    }
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose() && !shouldQuit_) {
        const float dt = GetFrameTime();

        currentScene_->handleInput();
        currentScene_->update(dt);
        applyPendingScene();

        BeginDrawing();
        ClearBackground(Color{10, 12, 24, 255});
        currentScene_->draw();
        EndDrawing();
    }
}

void Game::goToMenu() {
    changeScene(std::make_unique<MenuScene>(*this));
}

void Game::goToHelp() {
    changeScene(std::make_unique<HelpScene>(*this));
}

void Game::startGame() {
    changeScene(std::make_unique<PlayScene>(*this));
}

void Game::showResult(const ScoreSummary& summary) {
    changeScene(std::make_unique<ResultScene>(*this, summary));
}

void Game::requestQuit() {
    shouldQuit_ = true;
}

void Game::changeScene(std::unique_ptr<Scene> nextScene) {
    if (currentScene_) {
        pendingScene_ = std::move(nextScene);
    } else {
        currentScene_ = std::move(nextScene);
    }
}

void Game::applyPendingScene() {
    if (pendingScene_) {
        currentScene_ = std::move(pendingScene_);
    }
}
