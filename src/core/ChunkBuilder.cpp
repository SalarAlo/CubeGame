#include "ChunkBuilder.h"

#include <array>
#include <cstddef>
#include <vector>
#include <iostream>

#include "Face.h"
#include "Utils.h"
#include "Constants.h"

void ChunkBuilder::AddFace(Face face) {
        m_Faces.push_back(face);
        std::cout << "Added Face at " << directionToString(face.FaceDirection) << "\n";
        std::cout << std::flush;
}

void ChunkBuilder::AddCube(const Cube& cube) {
        constexpr int directionCount { 6 };
        for(int i = 0; i < directionCount; i++) {
                Face face { 
                        .Position { cube.Position}, 
                        .FaceDirection { static_cast<Direction>(i) }, 
                        .Color { cube.Color } 
                };
                AddFace(face);
        }
}


std::vector<float> ChunkBuilder::BuildChunkElementBufferData() const {
        std::vector<float> finalVertices {};
        finalVertices.reserve(m_Faces.size() * VALUES_PER_FACE);


        for (const auto& face : m_Faces) {
                FacePositionVertices vertices { DIRECTION_TO_VERTICES[static_cast<std::size_t>(face.FaceDirection)] };
                auto position = face.Position; 
                std::array<float, VALUES_PER_VERTEX> offsets = { position.x, position.y, position.z };

                for(int i {}; i < POSITIONAL_VALUES_PER_FACE; i++) {
                        int vertexCoordinateIdx = i % POSITION_VALUES_PER_VERTEX;
                        finalVertices.push_back(vertices[i] + offsets[vertexCoordinateIdx]);

                        auto doneWithPositionInsertion = vertexCoordinateIdx == POSITION_VALUES_PER_VERTEX-1;
                        if(doneWithPositionInsertion) {
                                auto rgb = getRgbForColor(face.Color);
                                finalVertices.push_back(rgb.r);
                                finalVertices.push_back(rgb.g);
                                finalVertices.push_back(rgb.b);
                        }
                }
        }

        std::cout << std::flush;
        return finalVertices;
}


