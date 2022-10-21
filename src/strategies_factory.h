#pragma once

#include <string>
#include <memory>
#include <map>
#include "strategy.h"

struct StrategyInfo{
    std::string description;
    std::unique_ptr<Strategy> (*create)();
};

class StrategiesFactory{
private:
    mutable std::map<const std::string, StrategyInfo> _info;
public:
    StrategiesFactory();

    std::unique_ptr<Strategy> create_strategy(const std::string& title) const;

    std::map<std::string, std::string> get_strategies_description() const;
};
