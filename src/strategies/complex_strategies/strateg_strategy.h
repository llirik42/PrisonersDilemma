#pragma once

#include "../abstract_strategy.h"

class RawStrategStrategy: public RawAbstractStrategy{
public:
    RawStrategStrategy();
    Step act(const Choices& enemies_choices) override;
private:
    unsigned int _cooperation_count;
    unsigned int _defection_count;
};
