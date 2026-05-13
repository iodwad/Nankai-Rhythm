#pragma once

#include "Chart.h"
#include "Scene.h"
#include "ScoreManager.h"
#include "Judgement.h"

#include <string>

class PlayScene : public Scene {
public:
    explicit PlayScene(Game& game);

    void handleInput() override;
    void update(float dt) override;
    void draw() override;

private:
    float currentTime() const;
    void judgeLane(int lane);
    void applyJudgement(Judgement judgement);
    void updateMisses(float time);
    void drawBackground() const;
    void drawLanes() const;
    void drawHud() const;
    void drawJudgementText() const;
    void drawComboMilestoneEffect() const;

    Chart chart_;
    ScoreManager score_;
    double startTime_ = 0.0;
    bool chartLoaded_ = false;
    bool finished_ = false;

    Judgement lastJudgement_ = Judgement::None;
    float judgementTextTimer_ = 0.0f;
    int lastComboMilestoneEffect_ = 0;
    int comboMilestoneEffectCombo_ = 0;
    float comboMilestoneEffectTimer_ = 0.0f;
    int laneFlash_[4] = {0, 0, 0, 0};
};
