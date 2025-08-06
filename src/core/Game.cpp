#include "Game.h"
#include "ChunkBuilder.h"
#include "Config.h"
#include "Cube.h"
#include "LevelConfig.h"
#include "MeshColor.h"
#include "ScreenWindow.h"
#include "Utils.h"
#include <glm/fwd.hpp>
#include <iostream>
#include <ostream>

void Game::Init() {
        // i new it would have a usecase :D
        m_LevelManager.LoadLevel(1);
}

void Game::RebuildChunk(LuaExecutor& executor) {
        m_ChunkBuilder.Reset();

        auto sizes = m_LevelManager.GetCurrentLevel().Config.Sizes;

        forEachVoxel(sizes.x, sizes.y, sizes.z, [&](int x, int y, int z) {
                glm::vec3 position { x, y, z };
                auto color = executor.GetColor(position);

                if(color == -1) return;

                auto colorType = static_cast<MeshColor::Type>(color);
                MeshColor colorObj { colorType };
                Cube cube { position, colorObj };

                m_ChunkBuilder.AddCube(cube);
        });
}

void Game::Render(Renderer& renderer) {
        Light light {};
        const Level level { m_LevelManager.GetCurrentLevel() };
        
        light.Init(
                0.1f,
                0.8f,
                0.1f,
                level.Config.LightColor,
                { -0.2f, -1.0f, -0.3f }
        );

        renderer.SetupBufferForDraw(m_ChunkBuilder.BuildChunkElementBufferData());
        renderer.SetLight(light);

        renderer.DrawFrame();
}
