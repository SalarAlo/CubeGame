#pragma once

#include "Constants.h"
#include <cstdint>
#include <array>

enum class Direction : std::int8_t {
        Up,
        Down,
        Right,
        Left,
        Forward,
        Back
};

struct Face {
        short Position;
        Direction FaceDirection;
};

constexpr float VERTICES[] = {
    -0.5f, -0.5f, -0.5f, // 0
     0.5f, -0.5f, -0.5f, // 1
     0.5f,  0.5f, -0.5f, // 2
    -0.5f,  0.5f, -0.5f, // 3
    -0.5f, -0.5f,  0.5f, // 4
     0.5f, -0.5f,  0.5f, // 5
     0.5f,  0.5f,  0.5f, // 6
    -0.5f,  0.5f,  0.5f  // 7
};

constexpr unsigned int INDICES_BACK[]   = { 0, 1, 2, 2, 3, 0 };
constexpr unsigned int INDICES_FRONT[]  = { 4, 5, 6, 6, 7, 4 };
constexpr unsigned int INDICES_BOTTOM[] = { 4, 5, 1, 1, 0, 4 };
constexpr unsigned int INDICES_TOP[]    = { 7, 6, 2, 2, 3, 7 };
constexpr unsigned int INDICES_LEFT[]   = { 4, 0, 3, 3, 7, 4 };
constexpr unsigned int INDICES_RIGHT[]  = { 5, 1, 2, 2, 6, 5 };

// Extract 6 vertices × 3 floats for positions only
constexpr std::array<float, 18> extractPositions(const unsigned int* indices);

constexpr std::array<std::array<float, 18>, 6> DIRECTION_TO_VERTICES = {
    extractPositions(INDICES_TOP),     
    extractPositions(INDICES_BOTTOM),  
    extractPositions(INDICES_RIGHT),   
    extractPositions(INDICES_LEFT),    
    extractPositions(INDICES_FRONT),   
    extractPositions(INDICES_BACK)     
};

