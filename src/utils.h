#pragma once

#include <array>
#include <vector>

template<typename type>
using Triplet = std::array<type, 3>;

using Step = char;
using Choices = std::vector<Step>;
using Score = std::vector<int>;

using StrategiesIndexes = Triplet<unsigned int>;

inline const Step COOPERATION_STEP = 'C';
inline const Step DEFECTION_STEP = 'D';

enum GameMode{
    FAST,
    DETAILED,
    TOURNAMENT,
};
