#pragma once

#include <vector>
#include "utils.h"
#include "strategy.h"
#include "matrix.h"
#include "viewer.h"

using StrategiesTriplet = Triplet<Strategy>;
using StrategiesVector = std::vector<Strategy>;

enum GameMode{
    FAST,
    DETAILED,
    TOURNAMENT
};

class Game{
private:
    Viewer _viewer;
    const StrategiesVector& _strategies;
    const Matrix& _matrix;
    unsigned int _steps_count;
    GameMode _mode;

    StrategiesTriplet extract_strategies_triplet(StrategiesIndexes indexes);

    Score competition(StrategiesTriplet& strategies_triplet);

    Score tournament();
public:
    Game(StrategiesVector& strategies, const Matrix& matrix, unsigned int steps_count, GameMode mode);

    void start();
};
