#pragma once

#include "../abstract_strategy.h"

class RawTitForTatStrategy: public RawAbstractStrategy{
public:
    Step act(const Choices& enemies_choices) override;
};
