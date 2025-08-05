#pragma once

#include "Camera.h"
#include "ChunkBuilder.h"
#include "Config.h"
#include "Cube.h"
#include "LevelManager.h"
#include "LuaExecutor.h"
#include "Renderer.h"

enum class GameState {
        None,
        Playing,
};


class Game {
public:
        void Init();
        void Render(Renderer& renderer);
        void RebuildChunk(LuaExecutor& executor);

private:
        LevelManager m_LevelManager {};
        ChunkBuilder m_ChunkBuilder {};
        GameState m_GameState {};
};
