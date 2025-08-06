#pragma once 

#include <optional>
#include <vector>

#include <glm/glm.hpp>

#include "MeshColor.h"

struct Cube {
        glm::vec3 Position;
        MeshColor Color;

        bool operator==(const Cube& other) const {
                return other.Color.GetColor() == Color.GetColor() && other.Position == Position;
        }
};

