#pragma once

#include "Constants.h"
#include "Cube.h"
#include "Direction.h"

#include <cstdint>
#include <array>

struct Face {
        glm::vec3 Position;
        Direction FaceDirection;
        MeshColor Color;
};

