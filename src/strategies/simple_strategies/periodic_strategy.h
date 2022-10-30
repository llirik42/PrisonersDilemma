#pragma once

#include "../abstract_strategy.h"

class RawPeriodicStrategy: public RawAbstractStrategy{
public:
    RawPeriodicStrategy();
    Step act([[maybe_unused]] const Choices& enemies_choices) override;
private:
    unsigned int _steps_count;
    unsigned int _period;
    Step _current_step;
};
