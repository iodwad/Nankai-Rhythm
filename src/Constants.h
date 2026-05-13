#pragma once

namespace Constants {
constexpr int ScreenWidth = 960;
constexpr int ScreenHeight = 720;

constexpr float JudgeLineY = 580.0f;
constexpr float NoteSpeed = 420.0f;
constexpr float LaneWidth = 110.0f;
constexpr float LaneGap = 18.0f;
constexpr float LaneStartX = 250.0f;
constexpr float LaneCenterOffset = LaneWidth * 0.5f;

constexpr float PerfectWindow = 0.080f;
constexpr float GoodWindow = 0.160f;
constexpr float BadWindow = 0.250f;

constexpr float NoteRadius = 24.0f;
constexpr float GameEndDelay = 1.2f;

inline float laneCenterX(int lane) {
    return LaneStartX + lane * (LaneWidth + LaneGap) + LaneCenterOffset;
}
}
