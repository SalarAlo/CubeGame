#include "ChunkBuilder.h"

#include <array>
#include <cstddef>
#include <vector>

#include "Face.h"
#include "Utils.h"
#include "Constants.h"

void ChunkBuilder::AddFace(Direction direction, glm::vec3 position) {
        short idx { static_cast<short>(positionToIndex(position)) };
        Face face {  .Position = idx, .FaceDirection = direction };
        m_Faces.push_back(face);
}

std::vector<float> ChunkBuilder::BuildChunkElementBufferData() const {
        std::vector<float> finalVertices {};
        finalVertices.reserve(m_Faces.size() * VALUES_PER_FACE);

        for (auto face : m_Faces) {
                FaceVertices vertices { DIRECTION_TO_VERTICES[static_cast<std::size_t>(face.FaceDirection)] };
                auto position { indexToPosition(static_cast<int>(face.Position)) };
                std::array<float, VALUES_PER_VERTEX> offsets = { position.x, position.y, position.z };

                for(int i {}; i < VALUES_PER_FACE; i++) {
                        finalVertices.push_back(vertices[i] + offsets[i % VALUES_PER_VERTEX]);
                }
        }

        return finalVertices;
}
