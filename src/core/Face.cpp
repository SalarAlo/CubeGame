#include "Face.h"

#include "Constants.h"

constexpr std::array<float, 18> extractPositions(const unsigned int* indices) {
    std::array<float, 18> facePositions{};
    for (int i = 0; i < INDICES_PER_FACE; ++i) {
        unsigned int vertexIndex = indices[i];
        for (int j = 0; j < 3; ++j) {
            facePositions[i * 3 + j] = VERTICES[vertexIndex * 3 + j];
        }
    }
    return facePositions;
}
