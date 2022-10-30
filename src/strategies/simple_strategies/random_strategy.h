#pragma once

#include "../abstract_strategy.h"

class RawRandomStrategy: public RawAbstractStrategy{
public:
    Step act([[maybe_unused]] const Choices& enemies_choices) override;
};
