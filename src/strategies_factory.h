#pragma once

#include <string>
#include <vector>
#include <memory>
#include "strategy.h"

struct StrategyDescription{
    std::string title;
    std::string description;
};

struct StrategyInfo{
    StrategyDescription description;
    std::unique_ptr<Strategy> (*create)(){};
};

class StrategiesFactory{
private:
    std::vector<StrategyDescription> _description;
    std::vector<StrategyInfo> _info;
public:
    StrategiesFactory();

    const std::vector<StrategyDescription>& get_strategies_description();

    std::unique_ptr<Strategy> create_strategy(const std::string& title);
};
