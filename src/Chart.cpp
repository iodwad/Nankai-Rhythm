#include "Chart.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

bool Chart::loadFromFile(const std::string& filename) {
    notes_.clear();
    lastHitTime_ = 0.0f;

    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        float hitTime = 0.0f;
        int lane = 0;
        if (!(iss >> hitTime >> lane)) {
            continue;
        }

        if (hitTime < 0.0f || lane < 0 || lane > 3) {
            continue;
        }

        notes_.emplace_back(lane, hitTime);
        lastHitTime_ = std::max(lastHitTime_, hitTime);
    }

    std::sort(notes_.begin(), notes_.end(), [](const Note& a, const Note& b) {
        return a.getHitTime() < b.getHitTime();
    });

    return !notes_.empty();
}

const std::vector<Note>& Chart::getNotes() const { return notes_; }
std::vector<Note>& Chart::getMutableNotes() { return notes_; }
int Chart::getTotalNotes() const { return static_cast<int>(notes_.size()); }
float Chart::getLastHitTime() const { return lastHitTime_; }
