#pragma once

#include "../abstract_strategy.h"

class RawCooperatorStrategy: public RawAbstractStrategy{
public:
    Step act([[maybe_unused]] const Choices& enemies_choices) override;
};

class RawDefectorStrategy: public RawAbstractStrategy{
public:
    Step act([[maybe_unused]] const Choices& enemies_choices) override;
};
