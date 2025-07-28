#pragma once

#include "Camera.h"
#include "ChunkBuilder.h"
#include "Config.h"
#include "Cube.h"
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
        ChunkBuilder m_ChunkBuilder {};
        GameState m_GameState {};
};
