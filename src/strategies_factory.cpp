#include "strategies_factory.h"
#include "strategies/all_strategies.h"

template<typename Type>
Strategy create(){
    return std::make_shared<Type>();
}

StrategiesFactory::StrategiesFactory(){
    _info["Cooperator"] = StrategyInfo({
        "Always cooperates",
        create<RawCooperatorStrategy>
    });

    _info["Defector"] = StrategyInfo({
        "Always defects",
        create<RawDefectorStrategy>
    });

    _info["Random"] = StrategyInfo({
        "Tries to make a random decision",
        create<RawRandomStrategy>
    });

    _info["Periodic"] = StrategyInfo({
        "Starts with cooperation and then alternates with period of 1",
        create<RawPeriodicStrategy>
    });

    _info["Kind"] = StrategyInfo({
        "Cooperates until somebody's betrayal",
        create<RawKindStrategy>
    });

    _info["Strateg"] = StrategyInfo({
        "Counts cooperation and betrayal in whole game. Cooperation > Betrayal - cooperates, else - betrays",
        create<RawStrategStrategy>
    });
    _info["TitForTat"] = StrategyInfo({
        "If Cooperation > Betrayal in previous round - cooperates, else - betrays. In first round cooperates",
        create<RawTitForTatStrategy>
    });
}

Strategy StrategiesFactory::create_strategy(const std::string& title) const{
    return _info.at(title).create();
}

std::map<std::string, std::string> StrategiesFactory::get_strategies_description() const{
    std::map<std::string, std::string> result;

    for (const auto& key: _info){
        result[key.first] = key.second.description;

    }
    return result;
}
