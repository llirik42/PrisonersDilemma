#include "strateg_strategy.h"
#include <random>

RawStrategStrategy::RawStrategStrategy(): _cooperation_count(0), _defection_count(0) {}

Step RawStrategStrategy::act(const Choices& enemies_choices){
    if (enemies_choices.empty()){
        return COOPERATION_STEP;
    }

    for (const auto& choice: enemies_choices){
        _cooperation_count += (choice == COOPERATION_STEP);
        _defection_count += (choice == DEFECTION_STEP);
    }

    if (_cooperation_count > _defection_count){
        return COOPERATION_STEP;
    }

    if (_defection_count > _cooperation_count){
        return DEFECTION_STEP;
    }

    return (rand() % 2) ? COOPERATION_STEP : DEFECTION_STEP;
}
