#pragma once

class Game;

class Scene {
public:
    explicit Scene(Game& game) : game_(game) {}
    virtual ~Scene() = default;

    virtual void handleInput() = 0;
    virtual void update(float dt) = 0;
    virtual void draw() = 0;

protected:
    Game& game_;
};
