#include <nlohmann/json.hpp>

#include <fstream>
#include <sstream>
#include <string>

#include "LevelManager.h"
#include "LevelConfig.h"
#include "LuaExecutor.h"
#include "Level.h"
#include "Cube.h"
#include "Utils.h"
#include "nlohmann/json_fwd.hpp"

void LevelManager::LoadLevel(int idx) {
        LevelFiles files { GetLevelFiles(idx) };
        Level level {};

        files.ConfigData.at("name").get_to(level.Config.Name);
        files.ConfigData.at("light_color").get_to(level.Config.LightColor);
        files.ConfigData.at("sizes").get_to(level.Config.Sizes);

        forEachVoxel(
                level.Config.Sizes[0], 
                level.Config.Sizes[1], 
                level.Config.Sizes[2], 

                [&](int x, int y, int z) {
                        LuaExecutor executor {};
                        executor.SetSourceCode(files.LuaSourceCode);
                        glm::vec3 position { x, y, z };
                        auto color = executor.GetColor(position);

                        if(color == -1) return;

                        auto colorType = static_cast<MeshColor::Type>(color);
                        MeshColor colorObj { colorType };
                        Cube cube { position, colorObj };
                        level.Cubes.push_back(cube);
                }
        );

        m_Level = level;
}

LevelManager::LevelFiles LevelManager::GetLevelFiles(int idx) const {
        LevelFiles files {};
        
        SetLevelConfigData(files, idx);
        SetLevelLuaSource(files, idx);
        
        return files;
}

void LevelManager::SetLevelLuaSource(LevelFiles& levelFiles, int idx) const {
        const std::string levelDirectory { "/home/salar/Desktop/Programming/Cpp/resources/levels/level_" + std::to_string(idx) };
        const std::string luaPath { levelDirectory + "/scene.lua" };
        std::ifstream luaFile { luaPath };

        if(!luaFile) {
                assert(false && "Trying to access level lua file data which is non existent");
        }

        std::stringstream buffer {};
        buffer << luaFile.rdbuf();
        levelFiles.LuaSourceCode = buffer.str();
}

void LevelManager::SetLevelConfigData(LevelFiles& levelFiles, int idx) const {
        const std::string levelDirectory { "/home/salar/Desktop/Programming/Cpp/resources/levels/level_" + std::to_string(idx) };
        const std::string configPath { levelDirectory + "/config.json" };
        std::ifstream configFile(configPath);
        if(!configFile) {
                assert(false && "Trying to access level json config data which is non existent");
        }
        configFile >> levelFiles.ConfigData;
}

bool LevelManager::CheckPlayerSolution(const std::vector<Cube>& playerVoxels) {
        return false;
}
