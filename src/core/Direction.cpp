#include "Direction.h"

static constexpr float VERTICES[] = {
        -0.5f, -0.5f, -0.5f, // 0
        0.5f, -0.5f, -0.5f, // 1
        0.5f,  0.5f, -0.5f, // 2
        -0.5f,  0.5f, -0.5f, // 3
        -0.5f, -0.5f,  0.5f, // 4
        0.5f, -0.5f,  0.5f, // 5
        0.5f,  0.5f,  0.5f, // 6
        -0.5f,  0.5f,  0.5f  // 7
};

static constexpr std::array<unsigned int, 6> INDICES[] = {
        std::array<unsigned int, 6>{ 7, 6, 2, 2, 3, 7 }, // Top
        std::array<unsigned int, 6>{ 4, 5, 1, 1, 0, 4 }, // Bottom
        std::array<unsigned int, 6>{ 5, 1, 2, 2, 6, 5 }, // Right
        std::array<unsigned int, 6>{ 4, 0, 3, 3, 7, 4 }, // Left
        std::array<unsigned int, 6>{ 4, 5, 6, 6, 7, 4 }, // Forward
        std::array<unsigned int, 6>{ 0, 1, 2, 2, 3, 0 }  // Back
};

static constexpr Direction::FacePositionVertices extractFaceVertices(const std::array<unsigned int, 6>& indices) {
        Direction::FacePositionVertices face{};
        for (int i = 0; i < 6; ++i) {
                unsigned int vertexIndex = indices[i];
                for (int j = 0; j < 3; ++j) {
                        face[i * 3 + j] = VERTICES[vertexIndex * 3 + j];
                }
        }
        return face;
}

static constexpr std::array<Direction::FacePositionVertices, 6> FACE_VERTEX_TABLE = {
        extractFaceVertices(INDICES[Direction::Top]),
        extractFaceVertices(INDICES[Direction::Bottom]),
        extractFaceVertices(INDICES[Direction::Right]),
        extractFaceVertices(INDICES[Direction::Left]),
        extractFaceVertices(INDICES[Direction::Forward]),
        extractFaceVertices(INDICES[Direction::Back])
};

Direction::Direction(Direction::Type type) : m_Type(type) {}

Direction::FacePositionVertices Direction::GetVertices() const {
        return FACE_VERTEX_TABLE[static_cast<int>(m_Type)];
}


glm::vec3 Direction::GetNormal() const {
        switch (m_Type) {
                case Direction::Top:     return glm::vec3(0.0f, 1.0f, 0.0f);
                case Direction::Bottom:  return glm::vec3(0.0f, -1.0f, 0.0f);
                case Direction::Right:   return glm::vec3(1.0f, 0.0f, 0.0f);
                case Direction::Left:    return glm::vec3(-1.0f, 0.0f, 0.0f);
                case Direction::Forward: return glm::vec3(0.0f, 0.0f, 1.0f);
                case Direction::Back:    return glm::vec3(0.0f, 0.0f, -1.0f);
                default:                 return glm::vec3(0.0f, 0.0f, 0.0f); 
        }
}
