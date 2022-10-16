#include <random>
#include "strategy.h"

inline const Step COOPERATION_STEP = 'C';
inline const Step DEFECTION_STEP = 'D';

Strategy::Strategy()=default;
Strategy::~Strategy()=default;
Step Strategy::act(){
    return 0;
}

ConstantStrategy::ConstantStrategy(): _step(COOPERATION_STEP) {}
Step ConstantStrategy::act(){
    return _step;
}

Step RandomStrategy::act(){
    return (rand() % 2) ? COOPERATION_STEP : DEFECTION_STEP;
}

PeriodicStrategy::PeriodicStrategy():_steps_count(0), _period(1), _current_step(COOPERATION_STEP) {}
Step PeriodicStrategy::act(){
    const Step result = _current_step;

    _steps_count++;

    if (_steps_count == _period){
        _current_step = _current_step == COOPERATION_STEP ? DEFECTION_STEP : COOPERATION_STEP;
        _steps_count = 0;
    }

    return result;
}

