#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include "Constants.h"
#include <array>

class Direction {
public:
        using FacePositionVertices = std::array<float, POSITIONAL_VALUES_PER_FACE>;

        enum Type : std::int8_t {
                Top,
                Bottom,
                Right,
                Left,
                Forward,
                Back
        };
public:
        Direction(Type type);
        Type GetType() const { return m_Type; }
        glm::vec3 GetNormal() const;
        Direction::FacePositionVertices GetVertices() const;

private:
        Type m_Type;
};
