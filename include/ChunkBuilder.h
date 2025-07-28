#pragma once

#include "Cube.h"
#include "Face.h"

#include <array>
#include <glm/glm.hpp>
#include <vector>


class ChunkBuilder {
public:
        void Reset();
        void AddFace(Face face);
        void AddCube(const Cube& cube);
        std::vector<float> BuildChunkElementBufferData() const;
private:
        std::vector<Face> m_Faces {};
};
