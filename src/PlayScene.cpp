#include "PlayScene.h"

#include "Constants.h"
#include "Game.h"
#include "raylib.h"

#include <cmath>
#include <cstdio>
#include <limits>

namespace {
const char* judgementToText(Judgement judgement) {
    switch (judgement) {
        case Judgement::Perfect: return "PERFECT";
        case Judgement::Good: return "GOOD";
        case Judgement::Bad: return "BAD";
        case Judgement::Miss: return "MISS";
        case Judgement::None: return "";
    }
    return "";
}

Color judgementColor(Judgement judgement) {
    switch (judgement) {
        case Judgement::Perfect: return Color{100, 235, 255, 255};
        case Judgement::Good: return Color{120, 255, 150, 255};
        case Judgement::Bad: return Color{255, 220, 80, 255};
        case Judgement::Miss: return Color{255, 105, 150, 255};
        case Judgement::None: return BLANK;
    }
    return BLANK;
}
}

PlayScene::PlayScene(Game& game) : Scene(game) {
    chartLoaded_ = chart_.loadFromFile("assets/charts/easy.txt");
    score_.reset(chart_.getTotalNotes());
    lastComboMilestoneEffect_ = 0;
    comboMilestoneEffectCombo_ = 0;
    comboMilestoneEffectTimer_ = 0.0f;
    startTime_ = GetTime();
}

void PlayScene::handleInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        game_.goToMenu();
        return;
    }

    if (!chartLoaded_ || finished_) {
        return;
    }

    if (IsKeyPressed(KEY_D)) judgeLane(0);
    if (IsKeyPressed(KEY_F)) judgeLane(1);
    if (IsKeyPressed(KEY_J)) judgeLane(2);
    if (IsKeyPressed(KEY_K)) judgeLane(3);
}

void PlayScene::update(float dt) {
    for (int& flash : laneFlash_) {
        if (flash > 0) {
            flash--;
        }
    }

    if (judgementTextTimer_ > 0.0f) {
        judgementTextTimer_ -= dt;
    }

    if (comboMilestoneEffectTimer_ > 0.0f) {
        comboMilestoneEffectTimer_ -= dt;
    }

    if (!chartLoaded_ || finished_) {
        return;
    }

    const float time = currentTime();
    updateMisses(time);

    if (time > chart_.getLastHitTime() + Constants::GameEndDelay) {
        finished_ = true;
        game_.showResult(score_.makeSummary());
    }
}

void PlayScene::draw() {
    drawBackground();

    if (!chartLoaded_) {
        DrawText("Failed to load chart: assets/charts/easy.txt", 200, 300, 24, RED);
        DrawText("Press ESC to return to menu.", 300, 350, 22, LIGHTGRAY);
        return;
    }

    drawLanes();

    const float time = currentTime();
    for (const auto& note : chart_.getNotes()) {
        note.draw(time);
    }

    DrawLineEx(Vector2{Constants::LaneStartX - 40.0f, Constants::JudgeLineY},
               Vector2{Constants::LaneStartX + 4 * Constants::LaneWidth + 3 * Constants::LaneGap + 40.0f, Constants::JudgeLineY},
               comboMilestoneEffectTimer_ > 0.0f ? 10.0f : 6.0f,
               comboMilestoneEffectTimer_ > 0.0f ? Color{255, 235, 90, 255} : Color{255, 255, 255, 220});

    drawHud();
    drawJudgementText();
    drawComboMilestoneEffect();
}

float PlayScene::currentTime() const {
    return static_cast<float>(GetTime() - startTime_);
}

void PlayScene::judgeLane(int lane) {
    laneFlash_[lane] = 8;

    const float time = currentTime();
    Note* best = nullptr;
    float bestDelta = std::numeric_limits<float>::max();

    for (auto& note : chart_.getMutableNotes()) {
        if (note.isJudged() || note.getLane() != lane) {
            continue;
        }

        const float delta = std::fabs(note.getHitTime() - time);
        if (delta < bestDelta) {
            bestDelta = delta;
            best = &note;
        }
    }

    if (best == nullptr || bestDelta > Constants::BadWindow) {
        return;
    }

    Judgement judgement = Judgement::Bad;
    if (bestDelta <= Constants::PerfectWindow) {
        judgement = Judgement::Perfect;
    } else if (bestDelta <= Constants::GoodWindow) {
        judgement = Judgement::Good;
    }

    best->markJudged();
    applyJudgement(judgement);
}

void PlayScene::applyJudgement(Judgement judgement) {
    score_.apply(judgement);
    const int combo = score_.getCombo();
    if (combo >= 10 && combo % 10 == 0 && combo > lastComboMilestoneEffect_) {
        lastComboMilestoneEffect_ = combo;
        comboMilestoneEffectCombo_ = combo;
        comboMilestoneEffectTimer_ = 1.0f;
    }
    lastJudgement_ = judgement;
    judgementTextTimer_ = 0.45f;
}

void PlayScene::updateMisses(float time) {
    for (auto& note : chart_.getMutableNotes()) {
        if (!note.isJudged() && time - note.getHitTime() > Constants::BadWindow) {
            note.markJudged();
            applyJudgement(Judgement::Miss);
        }
    }
}

void PlayScene::drawBackground() const {
    for (int i = 0; i < 36; ++i) {
        const int y = i * 22;
        DrawLine(0, y, Constants::ScreenWidth, y, Fade(Color{80, 110, 170, 255}, 0.06f));
    }
    DrawCircleGradient(Constants::ScreenWidth / 2, 120, 420, Fade(Color{70, 120, 255, 255}, 0.25f), BLANK);
}

void PlayScene::drawLanes() const {
    const Color laneColors[4] = {
        Color{80, 200, 255, 255},
        Color{130, 255, 130, 255},
        Color{255, 210, 80, 255},
        Color{255, 100, 170, 255},
    };

    const char* keys[4] = {"D", "F", "J", "K"};

    for (int lane = 0; lane < 4; ++lane) {
        const float x = Constants::LaneStartX + lane * (Constants::LaneWidth + Constants::LaneGap);
        const float alpha = laneFlash_[lane] > 0 ? 0.45f : 0.20f;

        DrawRectangleRounded(Rectangle{x, 80.0f, Constants::LaneWidth, 560.0f}, 0.15f, 16,
                             Fade(laneColors[lane], alpha));
        DrawRectangleLinesEx(Rectangle{x, 80.0f, Constants::LaneWidth, 560.0f}, 2.0f,
                             Fade(laneColors[lane], 0.55f));

        DrawText(keys[lane], static_cast<int>(Constants::laneCenterX(lane)) - 11, 640, 32, laneColors[lane]);
    }
}

void PlayScene::drawHud() const {
    char buffer[128];

    std::snprintf(buffer, sizeof(buffer), "Score: %d", score_.getScore());
    DrawText(buffer, 32, 26, 26, RAYWHITE);

    std::snprintf(buffer, sizeof(buffer), "Combo: %d", score_.getCombo());
    DrawText(buffer, 32, 62, 24, Color{130, 230, 255, 255});

    std::snprintf(buffer, sizeof(buffer), "Accuracy: %.1f%%", score_.getAccuracy() * 100.0f);
    DrawText(buffer, 720, 26, 24, LIGHTGRAY);

    std::snprintf(buffer, sizeof(buffer), "Rank: %c", score_.getRank());
    DrawText(buffer, 720, 62, 24, LIGHTGRAY);
}

void PlayScene::drawJudgementText() const {
    if (judgementTextTimer_ <= 0.0f || lastJudgement_ == Judgement::None) {
        return;
    }

    const char* text = judgementToText(lastJudgement_);
    const int fontSize = 42;
    const int width = MeasureText(text, fontSize);
    const float scale = 1.0f + judgementTextTimer_ * 0.25f;
    const int x = (Constants::ScreenWidth - width) / 2;
    const int y = 470 - static_cast<int>(judgementTextTimer_ * 20.0f);

    (void)scale;
    DrawText(text, x + 3, y + 3, fontSize, Fade(BLACK, 0.35f));
    DrawText(text, x, y, fontSize, judgementColor(lastJudgement_));
}

void PlayScene::drawComboMilestoneEffect() const {
    if (comboMilestoneEffectTimer_ <= 0.0f) {
        return;
    }

    char text[32];
    std::snprintf(text, sizeof(text), "%d COMBO!", comboMilestoneEffectCombo_);

    const float remaining = comboMilestoneEffectTimer_;
    const float scale = 1.0f + remaining * 0.35f;
    const int fontSize = static_cast<int>(56.0f * scale);
    const int width = MeasureText(text, fontSize);
    const int x = (Constants::ScreenWidth - width) / 2;
    const int y = Constants::ScreenHeight / 2 - fontSize / 2;
    const Color textColor = Fade(Color{255, 235, 90, 255}, remaining);

    DrawText(text, x + 4, y + 4, fontSize, Fade(BLACK, 0.45f * remaining));
    DrawText(text, x, y, fontSize, textColor);
}
