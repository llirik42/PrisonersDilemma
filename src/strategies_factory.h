#pragma once

#include <string>
#include <map>
#include "strategy.h"

using StrategiesDescription = std::map<std::string, std::string>;

struct StrategyInfo{
    std::string description;
    Strategy (*create)();
};

class StrategiesFactory{
private:
    mutable std::map<const std::string, StrategyInfo> _info;
public:
    StrategiesFactory();

    [[nodiscard]] Strategy create_strategy(const std::string& title) const;

    [[nodiscard]] StrategiesDescription get_strategies_description() const;
};
