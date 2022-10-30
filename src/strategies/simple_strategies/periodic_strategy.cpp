#include "periodic_strategy.h"

RawPeriodicStrategy::RawPeriodicStrategy():_steps_count(0), _period(1), _current_step(COOPERATION_STEP) {}

Step RawPeriodicStrategy::act([[maybe_unused]] const Choices& enemies_choices){
    const Step result = _current_step;

    _steps_count++;

    if (_steps_count == _period){
        _current_step = _current_step == COOPERATION_STEP ? DEFECTION_STEP : COOPERATION_STEP;
        _steps_count = 0;
    }

    return result;
}
