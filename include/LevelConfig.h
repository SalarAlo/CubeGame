#pragma once

#include <string>
#include <array>

struct LevelConfig {
    std::string Name {};
    std::array<float, 3> LightColor {};
    std::array<int, 3> Sizes {};
};

