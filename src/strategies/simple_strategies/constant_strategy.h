#pragma once

#include "../abstract_strategy.h"

class RawConstantStrategy: public RawAbstractStrategy{
public:
    RawConstantStrategy();
    Step act() override;
private:
    Step _step;
};
