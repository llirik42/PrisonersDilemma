#include <random>
#include "strategy.h"

inline const Step COOPERATION_STEP = 'C';
inline const Step DEFECTION_STEP = 'D';

RawStrategy::RawStrategy()=default;
RawStrategy::~RawStrategy()=default;
Step RawStrategy::act(){
    return 0;
}

RawConstantStrategy::RawConstantStrategy():_step(COOPERATION_STEP) {}
Step RawConstantStrategy::act(){
    return _step;
}

Step RawRandomStrategy::act(){
    return (rand() % 2) ? COOPERATION_STEP : DEFECTION_STEP;
}

RawPeriodicStrategy::RawPeriodicStrategy():_steps_count(0), _period(1), _current_step(COOPERATION_STEP) {}
Step RawPeriodicStrategy::act(){
    const Step result = _current_step;

    _steps_count++;

    if (_steps_count == _period){
        _current_step = _current_step == COOPERATION_STEP ? DEFECTION_STEP : COOPERATION_STEP;
        _steps_count = 0;
    }

    return result;
}
