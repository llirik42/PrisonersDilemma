#include <random>
#include "strateg_strategy.h"

void RawStrategStrategy::apply_choices(const Choices& choices){
    for (const auto& choice: choices){
        _cooperation_count += (choice == COOPERATION_STEP);
        _defection_count += (choice == DEFECTION_STEP);
    }
}

RawStrategStrategy::RawStrategStrategy(): _cooperation_count(0), _defection_count(0) {}

Step RawStrategStrategy::act(const Choices& enemies_choices){
    apply_choices(enemies_choices);

    if (_cooperation_count >= _defection_count){
        return COOPERATION_STEP;
    }

    if (_defection_count > _cooperation_count){
        return DEFECTION_STEP;
    }

    return (rand() % 2) ? COOPERATION_STEP : DEFECTION_STEP;
}

bool RawStrategStrategy::is_super_smart() const{
    return true;
}

void RawStrategStrategy::apply_previous_games_experience(const History& history){
    for (const auto& choices: history){
        apply_choices(choices);
    }
}
