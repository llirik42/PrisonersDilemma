#pragma once

#include <memory>
#include "../utils.h"

class RawAbstractStrategy;

using Strategy = std::shared_ptr<RawAbstractStrategy>;

class RawAbstractStrategy{
public:
    virtual ~RawAbstractStrategy()=default;
    virtual Step act([[maybe_unused]] const Choices& enemies_choices) {return COOPERATION_STEP;}
    [[nodiscard]] virtual bool is_super_smart() const{ // means whether strategy can use experience of previous games or not
        return false;
    }
    virtual void apply_previous_games_experience([[maybe_unused]] const History& history) {}
protected:
    RawAbstractStrategy()=default;
};
