#pragma once 

#include <optional>
#include <vector>

#include <glm/glm.hpp>

enum MeshColor {
        Red,
        Green,
        Blue,
        Yellow,
        Cyan,
        Magenta,
        White,
};

struct Cube {
        glm::vec3 Position;
        MeshColor Color;
};

