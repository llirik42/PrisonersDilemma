#pragma once

#include <string>
#include <vector>
#include <memory>
#include "strategy.h"

class StrategiesFactory;

class StrategyInfo{
    friend StrategiesFactory;
private:
    std::unique_ptr<Strategy> (*create)();
public:
    std::string title;
    std::string description;
};

class StrategiesFactory{
private:
    std::vector<StrategyInfo> _info;
public:
    StrategiesFactory();

    const std::vector<StrategyInfo>& get_info_about_strategies();

    std::unique_ptr<Strategy> create_strategy(const std::string& title);
};
