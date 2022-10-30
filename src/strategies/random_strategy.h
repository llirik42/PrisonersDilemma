#pragma once

#include "../abstract_strategy.h"

class RawRandomStrategy: public RawAbstractStrategy{
public:
    Step act() override;
};
