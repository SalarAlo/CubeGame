#include "Game.h"
#include "ChunkBuilder.h"
#include "Config.h"
#include "Cube.h"
#include "MeshColor.h"
#include "ScreenWindow.h"

void Game::Init() {
        // Could maybe be needed some day 
        // for now it just exists and get called where it should be called
}

void Game::RebuildChunk(LuaExecutor& executor) {
        m_ChunkBuilder.Reset();

        constexpr int chunkSizeHalfed { CHUNK_SIZE / 2 };

        for(int y = 0; y < CHUNK_HEIGHT; y++) {
                for(int z = -chunkSizeHalfed; z < chunkSizeHalfed; z++) {
                        for(int x = -chunkSizeHalfed; x < chunkSizeHalfed; x++) {
                                glm::vec3 position { x, y, z };
                                auto color = executor.GetColor(position);

                                if(color == -1) continue;
                                auto colorType = static_cast<MeshColor::Type>(color);
                                MeshColor colorObj { colorType };
                                Cube cube { position, colorObj };
                                m_ChunkBuilder.AddCube(cube);
                        }
                }
        }
}

void Game::Render(Renderer& renderer) {
        Light light {};
        light.Init(
                0.1f,
                0.8f,
                0.1f,
                {1.0f, 1.0f, 1.0f},
                {-0.2f, -1.0f, -0.3f}
        );

        renderer.SetupBufferForDraw(m_ChunkBuilder);

        renderer.DrawFrame();
        renderer.SetLight(light);
}
