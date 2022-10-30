#pragma once

#include "../abstract_strategy.h"

class RawKindStrategy: public RawAbstractStrategy{
public:
    RawKindStrategy();
    Step act(const Choices& enemies_choices) override;
private:
    bool _was_betrayed;
};
