#pragma once

#include "Cube.h"
#include "Face.h"

#include <array>
#include <glm/glm.hpp>
#include <vector>


class ChunkBuilder {
public:
        ChunkBuilder(glm::ivec2 chunkPosition) : m_ChunkPosition(chunkPosition) { }
        void AddFace(Face face);
        void AddCube(const Cube& cube);
        std::vector<float> BuildChunkElementBufferData() const;
private:
        glm::ivec2 m_ChunkPosition {};
        std::vector<Face> m_Faces {};
};
