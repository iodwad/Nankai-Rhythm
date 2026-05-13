#include "Note.h"

#include "Constants.h"
#include "raylib.h"

#include <algorithm>

Note::Note(int lane, float hitTime)
    : lane_(std::clamp(lane, 0, 3)), hitTime_(hitTime) {}

int Note::getLane() const { return lane_; }
float Note::getHitTime() const { return hitTime_; }
bool Note::isJudged() const { return judged_; }
void Note::markJudged() { judged_ = true; }

float Note::getY(float currentTime) const {
    return Constants::JudgeLineY - (hitTime_ - currentTime) * Constants::NoteSpeed;
}

void Note::draw(float currentTime) const {
    if (judged_) {
        return;
    }

    const float x = Constants::laneCenterX(lane_);
    const float y = getY(currentTime);

    if (y < -50.0f || y > Constants::ScreenHeight + 50.0f) {
        return;
    }

    const Color laneColors[4] = {
        Color{80, 200, 255, 255},
        Color{130, 255, 130, 255},
        Color{255, 210, 80, 255},
        Color{255, 100, 170, 255},
    };

    DrawCircleV(Vector2{x, y}, Constants::NoteRadius + 7.0f, Fade(laneColors[lane_], 0.25f));
    DrawCircleV(Vector2{x, y}, Constants::NoteRadius, laneColors[lane_]);
    DrawCircleV(Vector2{x - 7.0f, y - 7.0f}, 6.0f, Fade(WHITE, 0.55f));
}
