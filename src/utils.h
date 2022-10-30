#pragma once

#include <array>
#include <vector>
#include <map>
#include <string>

template<typename type>
using Triplet = std::array<type, 3>;

using Step = char;
using Choices = std::vector<Step>;
using Score = std::vector<int>;

using StrategiesIndexes = Triplet<unsigned int>;

using StrategiesDescription = std::map<std::string, std::string>;

inline const Step COOPERATION_STEP = 'C';
inline const Step DEFECTION_STEP = 'D';

inline int char_to_digit(char c){
    return c - '0';
}

enum GameMode{
    FAST,
    DETAILED,
    TOURNAMENT,
};
