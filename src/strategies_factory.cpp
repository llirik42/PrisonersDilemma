#include "strategies_factory.h"

template<typename Type>
std::unique_ptr<Strategy> create(){
    return std::make_unique<Type>();
}

StrategiesFactory::StrategiesFactory(){
    _info.push_back(StrategyInfo({"Constant", "Description 1"}));
    _info.push_back(StrategyInfo({"Random", "Description 2"}));
    _info.push_back(StrategyInfo({"Periodic", "Description 3"}));
}






std::unique_ptr<Strategy> StrategiesFactory::create_strategy(const std::string& title){
    if (title == "Constant"){
        return std::make_unique<ConstantStrategy>();
    }

    if (title == "Random"){
        return std::make_unique<RandomStrategy>();
    }

    if (title == "Periodic"){
        return std::make_unique<PeriodicStrategy>();
    }

    return nullptr;
}

const std::vector<StrategyInfo>& StrategiesFactory::get_info_about_strategies(){
    return _info;
}
