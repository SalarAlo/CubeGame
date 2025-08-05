#pragma once

#include "Cube.h"
#include "Level.h"
#include "LevelConfig.h"

#include "nlohmann/json.hpp"

class LevelManager {
public:
        struct LevelFiles {
                nlohmann::json ConfigData;
                std::string LuaSourceCode;
        };
public:
        void LoadLevel(int index);
        const Level& GetCurrentLevel() const { return m_Level; };

        bool CheckPlayerSolution(const std::vector<Cube>& playerVoxels);

private:
        LevelFiles GetLevelFiles(int index) const;
        void SetLevelConfigData(LevelFiles& levelFiles, int idx) const;
        void SetLevelLuaSource(LevelFiles& levelFiles, int idx) const;

private:
        Level m_Level;
};
