#pragma once

#include "Scene.h"
#include "ScoreManager.h"

class ResultScene : public Scene {
public:
    ResultScene(Game& game, ScoreSummary summary);

    void handleInput() override;
    void update(float dt) override;
    void draw() override;

private:
    ScoreSummary summary_;
    int highScore_ = 0;

    void loadAndSaveHighScore();
};
