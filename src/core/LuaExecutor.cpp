#include "LuaExecutor.h"
#include "MeshColor.h"
#include "magic_enum/magic_enum.hpp"

#include <iostream>
#include <cassert>
#include <string>

const std::string LuaExecutor::s_LuaFnName = "getColor";

LuaExecutor::LuaExecutor() {
        m_State = luaL_newstate();
        luaL_openlibs(m_State);
}

LuaExecutor::~LuaExecutor() {
        if (m_State) {
                lua_close(m_State);
                m_State = nullptr;
        }
}

bool LuaExecutor::LoadFunction(const std::string& fullCode) {
        if (luaL_loadstring(m_State, fullCode.c_str()) != LUA_OK) {
                std::cerr << "Lua load error: " << lua_tostring(m_State, -1) << std::endl;
                lua_pop(m_State, 1);
                return false;
        }

        if (lua_pcall(m_State, 0, 0, 0) != LUA_OK) {
                std::cerr << "Lua runtime error: " << lua_tostring(m_State, -1) << std::endl;
                lua_pop(m_State, 1);
                return false;
        }

        return true;
}

void LuaExecutor::SetSourceCode(const std::string& sourceCode) {
        const std::string luaFnStart = "function " + s_LuaFnName + "(x, y, z) \n";
        const std::string luaFnEnd = "\nend";
        std::string luaColorDecl {"Nothing = -1\n"};
        for(auto color : magic_enum::enum_values<MeshColor::Type>()) {
                auto colorName = std::string(magic_enum::enum_name(color));
                auto colorIdxStr = std::to_string(static_cast<int>(color));
                luaColorDecl += ("local " + colorName + " = " + colorIdxStr + "\n");
        }

        std::string fullCode = luaFnStart + luaColorDecl + sourceCode + luaFnEnd;

        m_FunctionLoaded = LoadFunction(fullCode);
}

bool LuaExecutor::IsFunctionReadyForUse() {
        if (!m_FunctionLoaded) {
                std::cerr << "Lua function not loaded." << std::endl;
                return false;
        }

        lua_getglobal(m_State, s_LuaFnName.c_str());

        if (!lua_isfunction(m_State, -1)) {
                std::cerr << "Function '" << s_LuaFnName << "' not found." << std::endl;
                lua_pop(m_State, 1);
                return false;
        }

        return true;
}

int LuaExecutor::GetColor(glm::vec3 position) {
        if(!IsFunctionReadyForUse()) return -1;

        lua_pushnumber(m_State, position.x);
        lua_pushnumber(m_State, position.y);
        lua_pushnumber(m_State, position.z);

        if (lua_pcall(m_State, 3, 1, 0) != LUA_OK) {
                std::cerr << "Error calling Lua function: " << lua_tostring(m_State, -1) << std::endl;
                lua_pop(m_State, 1);
                return -1;
        }

        if (!lua_isnumber(m_State, -1)) {
                std::cerr << "Unexpected return type from Lua function." << std::endl;
                lua_pop(m_State, 1);
                return -1;
        }

        int result = static_cast<int>(lua_tonumber(m_State, -1));
        lua_pop(m_State, 1);
        return result;
}
