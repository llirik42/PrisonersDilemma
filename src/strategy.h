#pragma once

class Strategy;

using Step = char;

class Strategy{
protected:
    Strategy();
public:
    virtual ~Strategy();
    virtual Step act();
};

class ConstantStrategy: public Strategy{
private:
    Step _step;
public:
    ConstantStrategy();
    Step act() override;
};

class RandomStrategy: public Strategy{
public:
    Step act() override;
};

class PeriodicStrategy:public Strategy{
private:
    unsigned int _steps_count;
    unsigned int _period;
    Step _current_step;
public:
    PeriodicStrategy();
    Step act() override;
};
