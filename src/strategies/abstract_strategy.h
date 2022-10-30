#pragma once

#include <memory>
#include "../utils.h"

class RawAbstractStrategy;

using Strategy = std::shared_ptr<RawAbstractStrategy>;

class RawAbstractStrategy{
public:
    virtual ~RawAbstractStrategy()=default;
    virtual Step act([[maybe_unused]] const Choices& enemies_choices){return COOPERATION_STEP;}
protected:
    RawAbstractStrategy()=default;
};
