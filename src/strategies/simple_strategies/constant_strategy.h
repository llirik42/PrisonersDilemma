#pragma once

#include "../abstract_strategy.h"

class RawConstantStrategy: public RawAbstractStrategy{
public:
    RawConstantStrategy();
    Step act([[maybe_unused]] const Choices& enemies_choices) override;
private:
    Step _step;
};
