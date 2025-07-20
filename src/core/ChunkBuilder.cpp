#include "ChunkBuilder.h"

#include "Face.h"
#include "Utils.h"
#include "Constants.h"
#include <vector>

void ChunkBuilder::AddFace(Direction direction, glm::vec3 position) {
        short idx { static_cast<short>(positionToIndex(position)) };
        Face face { .FaceDirection = direction, .Position = position };
        m_Faces.push_back(face);
}

std::vector<unsigned int> ChunkBuilder::BuildChunkElementBufferData() const {
        std::vector<unsigned int> indices {};
        indices.reserve(m_Faces.size() * INDICES_PER_FACE);

        for (auto face : m_Faces) {

        }
}
