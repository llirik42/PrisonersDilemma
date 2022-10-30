#include "strategies_factory.h"
#include "strategies/simple_strategies/constant_strategy.h"
#include "strategies/simple_strategies/random_strategy.h"
#include "strategies/simple_strategies/periodic_strategy.h"

template<typename Type>
Strategy create(){
    return std::make_shared<Type>();
}

StrategiesFactory::StrategiesFactory(){
    _info["Constant"] = StrategyInfo({
        "Always cooperates",
        create<RawConstantStrategy>
    });

    _info["Random"] = StrategyInfo({
        "Tries to make a random decision",
        create<RawRandomStrategy>
    });

    _info["Periodic"] = StrategyInfo({
        "Starts with cooperation and then alternates with period of 1",
        create<RawPeriodicStrategy>
    });
}

Strategy StrategiesFactory::create_strategy(const std::string& title) const{
    return _info[title].create();
}

std::map<std::string, std::string> StrategiesFactory::get_strategies_description() const{
    std::map<std::string, std::string> result;

    for (const auto& key: _info){
        result[key.first] = key.second.description;

    }
    return result;
}
