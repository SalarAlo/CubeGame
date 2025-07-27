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
        static LuaExecutor& GetInstance();

        void SetSourceCode(const std::string& sourceCode);
        int GetColor(glm::vec3 position);

private:
        LuaExecutor();
        ~LuaExecutor();
        LuaExecutor(const LuaExecutor&) = delete;
        LuaExecutor& operator=(const LuaExecutor&) = delete;

        bool LoadFunction(const std::string& fullCode);

private:
        static inline const std::string s_LuaFnName = "getColor";
        static inline const std::string s_LuaFnStart = "function getColor(x, y, z)\n";
        static inline const std::string s_LuaFnEnd = "\nend";

        lua_State* m_State = nullptr;
        bool m_FunctionLoaded = false;
};
