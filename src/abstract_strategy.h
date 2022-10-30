#pragma once

#include <memory>

using Step = char;

inline const Step COOPERATION_STEP = 'C';
inline const Step DEFECTION_STEP = 'D';

class RawAbstractStrategy;

using Strategy = std::shared_ptr<RawAbstractStrategy>;

class RawAbstractStrategy{
public:
    virtual ~RawAbstractStrategy();
    virtual Step act();
protected:
    RawAbstractStrategy();
};
