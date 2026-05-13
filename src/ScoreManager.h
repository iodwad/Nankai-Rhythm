#pragma once

#include "Judgement.h"

struct ScoreSummary {
    int score = 0;
    int combo = 0;
    int maxCombo = 0;
    int perfect = 0;
    int good = 0;
    int bad = 0;
    int miss = 0;
    int totalNotes = 0;
    float accuracy = 0.0f;
    char rank = 'D';
};

class ScoreManager {
public:
    explicit ScoreManager(int totalNotes = 0);

    void reset(int totalNotes);
    void apply(Judgement judgement);

    int getScore() const;
    int getCombo() const;
    int getMaxCombo() const;
    int getPerfect() const;
    int getGood() const;
    int getBad() const;
    int getMiss() const;
    int getTotalNotes() const;
    float getAccuracy() const;
    char getRank() const;

    ScoreSummary makeSummary() const;

private:
    int score_ = 0;
    int combo_ = 0;
    int maxCombo_ = 0;
    int perfect_ = 0;
    int good_ = 0;
    int bad_ = 0;
    int miss_ = 0;
    int totalNotes_ = 0;
};
