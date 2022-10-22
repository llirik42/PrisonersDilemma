#include "strategies_factory.h"

template<typename Type>
Strategy create(){
    return std::make_shared<Type>();
}

StrategiesFactory::StrategiesFactory(){
    _info["Constant"] = StrategyInfo({
        "Description 1",
        create<RawConstantStrategy>
    });

    _info["Random"] = StrategyInfo({
        "Description 2",
        create<RawRandomStrategy>
    });

    _info["Periodic"] = StrategyInfo({
        "Description 3",
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
