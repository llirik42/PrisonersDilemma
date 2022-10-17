#include "strategies_factory.h"





template<typename Type>
std::unique_ptr<Strategy> create(){
    return std::make_unique<Type>();
}

StrategiesFactory::StrategiesFactory(){
    _info.push_back(StrategyInfo({
        StrategyDescription({"Constant", "Description 1"}),
        create<ConstantStrategy>
    }));

    _info.push_back(StrategyInfo({
        StrategyDescription({"Random", "Description 2"}),
        create<RandomStrategy>
    }));

    _info.push_back(StrategyInfo({
        StrategyDescription({"Periodic", "Description 3"}),
        create<PeriodicStrategy>
                                 }));

    for (const auto& i : _info){
        _description.push_back(i.description);
    }
}

std::unique_ptr<Strategy> StrategiesFactory::create_strategy(const std::string& title){
    for (const auto& i : _info){
        if (i.description.title == title){
            return i.create();
        }
    }

    return nullptr;

    /*
    if (title == "Constant"){
        return std::make_unique<ConstantStrategy>();
    }

    if (title == "Random"){
        return std::make_unique<RandomStrategy>();
    }

    if (title == "Periodic"){
        return std::make_unique<PeriodicStrategy>();
    }

    return nullptr;*/
}

const std::vector<StrategyDescription>& StrategiesFactory::get_strategies_description(){
    return _description;
}
