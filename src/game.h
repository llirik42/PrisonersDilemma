#pragma once

#include <vector>
#include <memory>
#include "strategy.h"
#include "matrix.h"

using StrategiesVector = std::vector<std::unique_ptr<Strategy>>;

enum GameMode{
    FAST,
    DETAILED,
    TOURNAMENT
};

void game(StrategiesVector& strategies, const Matrix& matrix, unsigned int steps_count, GameMode mode);
