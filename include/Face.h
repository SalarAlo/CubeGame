#pragma once

#include <cstdint>

enum class Direction : std::int8_t {
        Up,
        Down,
        Right,
        Left,
        Forward,
        Back
}

struct Face {
        Direction Direction;
        short Position;
}


