#pragma once

#include "Scene.h"

class HelpScene : public Scene {
public:
    explicit HelpScene(Game& game);

    void handleInput() override;
    void update(float dt) override;
    void draw() override;
};
