#pragma once 

#include "LevelConfig.h"
#include <vector>
#include "Cube.h"

struct Level {
        LevelConfig Config {};
        std::vector<Cube> Cubes {};
        int idx {};
};
