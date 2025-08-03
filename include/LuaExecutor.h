#pragma once

#include <string>
#include <glm/vec3.hpp>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class LuaExecutor {
public:
        void SetSourceCode(const std::string& sourceCode);
        int GetColor(glm::vec3 position);

        LuaExecutor();
        ~LuaExecutor();
private:

        bool LoadFunction(const std::string& fullCode);
        bool IsFunctionReadyForUse();

private:
        static const std::string s_LuaFnName;
        lua_State* m_State = nullptr;
        bool m_FunctionLoaded = false;
};
