#pragma once

#include "Note.h"

#include <string>
#include <vector>

class Chart {
public:
    bool loadFromFile(const std::string& filename);

    const std::vector<Note>& getNotes() const;
    std::vector<Note>& getMutableNotes();

    int getTotalNotes() const;
    float getLastHitTime() const;

private:
    std::vector<Note> notes_;
    float lastHitTime_ = 0.0f;
};
