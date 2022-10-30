#pragma once

#include <vector>
#include "utils.h"
#include "strategies/abstract_strategy.h"
#include "matrix.h"
#include "viewer.h"

using StrategiesTriplet = Triplet<Strategy>;
using StrategiesVector = std::vector<Strategy>;

class Game{
public:
    Game(StrategiesVector& strategies, const Matrix& matrix, unsigned int steps_count, GameMode mode);

    void start();
private:
    GameViewer _viewer;
    const StrategiesVector& _strategies;
    const Matrix& _matrix;
    unsigned int _steps_count;
    GameMode _mode;

    [[nodiscard]] StrategiesTriplet extract_strategies_triplet(StrategiesIndexes indexes) const;

    Score competition(StrategiesTriplet& strategies_triplet) const;

    Score tournament();
};
