#pragma once

#include <string>
#include <map>
#include "strategies/abstract_strategy.h"

using StrategiesDescription = std::map<std::string, std::string>;

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
