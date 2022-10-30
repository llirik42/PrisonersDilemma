#pragma once

#include <string>
#include <map>
#include "utils.h"
#include "strategies/abstract_strategy.h"

class StrategiesFactory{
public:
    StrategiesFactory();

    [[nodiscard]] Strategy create_strategy(const std::string& title) const;

    [[nodiscard]] StrategiesDescription get_strategies_description() const;
private:
    struct StrategyInfo{
        std::string description;
        Strategy (*create)();
    };

    mutable std::map<const std::string, StrategyInfo> _info;
};
