#pragma once

#include "LuaExecutor.h"
#include "Renderer.h"
#include "Game.h"
#include "ScreenWindow.h"

class App {
public:
        void Run();
private:
        void OnCompilePressed();
private:
        Renderer m_Renderer {};
        Game m_Game {};
        LuaExecutor m_Executor {};
};
