#include "Game.h"
#include "ChunkBuilder.h"
#include "Config.h"
#include "Cube.h"
#include "MeshColor.h"
#include "ScreenWindow.h"
#include "Utils.h"

void Game::Init() {
        // Could maybe be needed some day 
        // for now it just exists and get called where it should be called
}

void Game::RebuildChunk(LuaExecutor& executor) {
        m_ChunkBuilder.Reset();

        m_LevelManager.LoadLevel(1);
        const auto& cubes = m_LevelManager.GetCurrentLevel().Cubes;
        for(const auto& cube : cubes) {
                m_ChunkBuilder.AddCube(cube);
        }

        if(false) {
        forEachVoxel(CHUNK_SIZE, CHUNK_HEIGHT, CHUNK_SIZE, [&](int x, int y, int z) {
                glm::vec3 position { x, y, z };
                auto color = executor.GetColor(position);

                if(color == -1) return;

                auto colorType = static_cast<MeshColor::Type>(color);
                MeshColor colorObj { colorType };
                Cube cube { position, colorObj };

                m_ChunkBuilder.AddCube(cube);
        });
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

        renderer.SetupBufferForDraw(m_ChunkBuilder.BuildChunkElementBufferData());

        renderer.DrawFrame();
        renderer.SetLight(light);
}
