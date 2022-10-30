#pragma once

#include <memory>
#include "../utils.h"

class RawAbstractStrategy;

using Strategy = std::shared_ptr<RawAbstractStrategy>;

class RawAbstractStrategy{
public:
    virtual ~RawAbstractStrategy();
    virtual Step act();
protected:
    RawAbstractStrategy();
};
