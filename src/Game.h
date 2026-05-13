#pragma once

#include "Scene.h"
#include "ScoreManager.h"

#include <memory>

class Game {
public:
    Game();
    ~Game();

    void run();

    void goToMenu();
    void goToHelp();
    void startGame();
    void showResult(const ScoreSummary& summary);
    void requestQuit();

private:
    void changeScene(std::unique_ptr<Scene> nextScene);
    void applyPendingScene();

    std::unique_ptr<Scene> currentScene_;
    std::unique_ptr<Scene> pendingScene_;
    bool shouldQuit_ = false;
};
