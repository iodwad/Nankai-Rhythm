#pragma once

#include "Scene.h"

class MenuScene : public Scene {
public:
    explicit MenuScene(Game& game);

    void handleInput() override;
    void update(float dt) override;
    void draw() override;

private:
    float elapsed_ = 0.0f;
};
