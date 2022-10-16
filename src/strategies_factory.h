#pragma once

#include <memory>
#include "strategy.h"

class StrategiesFactory{
public:
    std::unique_ptr<Strategy> create_strategy(StrategyType strategy_type);
};
