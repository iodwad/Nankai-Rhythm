#pragma once

#include "Judgement.h"

class Note {
public:
    Note(int lane, float hitTime);

    int getLane() const;
    float getHitTime() const;
    bool isJudged() const;
    void markJudged();

    float getY(float currentTime) const;
    void draw(float currentTime) const;

private:
    int lane_ = 0;
    float hitTime_ = 0.0f;
    bool judged_ = false;
};
