#pragma once

#include <array>
#include <vector>

using Step = char;

template<typename Type>
using Triplet = std::array<Type, 3>; // 3 values in one row

using Score = std::vector<int>;

using StrategiesIndexes = std::array<unsigned int, 3>;

enum GameMode{
    FAST,
    DETAILED,
    TOURNAMENT,
};
