#include "ScoreManager.h"

#include <algorithm>

ScoreManager::ScoreManager(int totalNotes) {
    reset(totalNotes);
}

void ScoreManager::reset(int totalNotes) {
    score_ = 0;
    combo_ = 0;
    maxCombo_ = 0;
    perfect_ = 0;
    good_ = 0;
    bad_ = 0;
    miss_ = 0;
    totalNotes_ = std::max(0, totalNotes);
}

void ScoreManager::apply(Judgement judgement) {
    switch (judgement) {
        case Judgement::Perfect:
            score_ += 1000 + combo_ * 5;
            combo_++;
            perfect_++;
            break;
        case Judgement::Good:
            score_ += 600 + combo_ * 3;
            combo_++;
            good_++;
            break;
        case Judgement::Bad:
            score_ += 200;
            combo_++;
            bad_++;
            break;
        case Judgement::Miss:
            combo_ = 0;
            miss_++;
            break;
        case Judgement::None:
            break;
    }
    maxCombo_ = std::max(maxCombo_, combo_);
}

int ScoreManager::getScore() const { return score_; }
int ScoreManager::getCombo() const { return combo_; }
int ScoreManager::getMaxCombo() const { return maxCombo_; }
int ScoreManager::getPerfect() const { return perfect_; }
int ScoreManager::getGood() const { return good_; }
int ScoreManager::getBad() const { return bad_; }
int ScoreManager::getMiss() const { return miss_; }
int ScoreManager::getTotalNotes() const { return totalNotes_; }

float ScoreManager::getAccuracy() const {
    if (totalNotes_ <= 0) {
        return 0.0f;
    }

    const float weighted = perfect_ * 1.0f + good_ * 0.7f + bad_ * 0.3f;
    return weighted / static_cast<float>(totalNotes_);
}

char ScoreManager::getRank() const {
    const float accuracy = getAccuracy();
    if (accuracy >= 0.95f) return 'S';
    if (accuracy >= 0.90f) return 'A';
    if (accuracy >= 0.80f) return 'B';
    if (accuracy >= 0.70f) return 'C';
    return 'D';
}

ScoreSummary ScoreManager::makeSummary() const {
    ScoreSummary summary;
    summary.score = score_;
    summary.combo = combo_;
    summary.maxCombo = maxCombo_;
    summary.perfect = perfect_;
    summary.good = good_;
    summary.bad = bad_;
    summary.miss = miss_;
    summary.totalNotes = totalNotes_;
    summary.accuracy = getAccuracy();
    summary.rank = getRank();
    return summary;
}
