#include "strategies_factory.h"

std::unique_ptr<Strategy> StrategiesFactory::create_strategy(StrategyType strategy_type){
    switch (strategy_type){
        case CONSTANT_STRATEGY:
            return std::make_unique<ConstantStrategy>();
        case RANDOM_STRATEGY:
            return std::make_unique<RandomStrategy>();
        case PERIODIC_STRATEGY:
            return std::make_unique<PeriodicStrategy>();
        default:
            return nullptr;
    }
}
