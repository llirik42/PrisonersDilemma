#pragma once

#include <memory>

using Step = char;

class RawStrategy;

using Strategy = std::shared_ptr<RawStrategy>;

class RawStrategy{
protected:
    RawStrategy();
public:
    virtual ~RawStrategy();
    virtual Step act();
};

class RawConstantStrategy:public RawStrategy{
private:
    Step _step;
public:
    RawConstantStrategy();
    Step act() override;
};

class RawRandomStrategy:public RawStrategy{
public:
    Step act() override;
};

class RawPeriodicStrategy:public RawStrategy{
private:
    unsigned int _steps_count;
    unsigned int _period;
    Step _current_step;
public:
    RawPeriodicStrategy();
    Step act() override;
};
