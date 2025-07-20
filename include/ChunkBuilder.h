#pragma once

#include "Face.h"

#include <array>
#include <glm/glm.hpp>
#include <vector>


class ChunkBuilder {
public:
        ChunkBuilder(glm::ivec2 chunkPosition) : m_ChunkPosition(chunkPosition) { }
        void AddFace(Direction direction, glm::vec3 position);
        std::vector<unsigned int> BuildChunkElementBufferData() const;
private:
        glm::ivec2 m_ChunkPosition {};
        std::vector<Face> m_Faces {};
};
