#include "ChunkBuilder.h"

#include <array>
#include <cstddef>
#include <vector>
#include <iostream>

#include "Face.h"
#include "Utils.h"
#include "Constants.h"
#include "Direction.h"

void ChunkBuilder::Reset(){
        m_Faces = {};
}

void ChunkBuilder::AddFace(Face face) {
        m_Faces.push_back(face);
}

void ChunkBuilder::AddCube(const Cube& cube) { constexpr int directionCount { 6 };
        for(int i = 0; i < directionCount; i++) {
                Face face { 
                        .Position { cube.Position}, 
                        .FaceDirection { static_cast<Direction::Type>(i) }, 
                        .Color { cube.Color } 
                };
                AddFace(face);
        }
}


std::vector<float> ChunkBuilder::BuildChunkElementBufferData() const {
        std::vector<float> finalVertices {};
        finalVertices.reserve(m_Faces.size() * VALUES_PER_FACE);


        for (const auto& face : m_Faces) {
                Direction::FacePositionVertices vertices { face.FaceDirection.GetVertices() };
                auto position = face.Position; 
                std::array<float, VALUES_PER_VERTEX> offsets = { position.x, position.y, position.z };

                for(int i {}; i < POSITIONAL_VALUES_PER_FACE; i++) {
                        int vertexCoordinateIdx = i % POSITION_VALUES_PER_VERTEX;
                        finalVertices.push_back(vertices[i] + offsets[vertexCoordinateIdx]);

                        auto doneWithPositionInsertion = vertexCoordinateIdx == POSITION_VALUES_PER_VERTEX-1;

                        if(doneWithPositionInsertion) {
                                glm::vec3 rgb = face.Color.GetRgb();
                                finalVertices.push_back(rgb.r);
                                finalVertices.push_back(rgb.g);
                                finalVertices.push_back(rgb.b);

                                glm::vec3 normal = face.FaceDirection.GetNormal();
                                finalVertices.push_back(normal.x);
                                finalVertices.push_back(normal.y);
                                finalVertices.push_back(normal.z);
                        }
                }
        }

        std::cout << std::flush;
        return finalVertices;
}


