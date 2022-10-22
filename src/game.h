#pragma once

#include <vector>
#include "utils.h"
#include "strategy.h"
#include "matrix.h"

using Score = std::vector<int>;
using StrategiesVector = std::vector<Strategy>;
using StrategiesTriplet = Triplet<Strategy>;

enum GameMode{
    FAST,
    DETAILED,
    TOURNAMENT
};

class Game{
private:
    const StrategiesVector& _strategies;
    const Matrix& _matrix;
    unsigned int _steps_count;
    GameMode _mode;

    StrategiesTriplet extract_strategies_triplet(unsigned int i, unsigned int j, unsigned int k);

    Score competition(StrategiesTriplet& strategies_triplet, bool mode);

    void tournament();
public:
    Game(StrategiesVector& strategies, const Matrix& matrix, unsigned int steps_count, GameMode mode);

    void start();
};
