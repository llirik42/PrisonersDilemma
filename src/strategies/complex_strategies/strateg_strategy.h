#pragma once

#include "../abstract_strategy.h"

class RawStrategStrategy: public RawAbstractStrategy{
public:
    RawStrategStrategy();
    Step act(const Choices& enemies_choices) override;
    [[nodiscard]] bool is_super_smart() const override;
    void apply_previous_games_experience(const History& history) override;
private:
    unsigned int _cooperation_count;
    unsigned int _defection_count;

    void apply_choices(const Choices& choices);
};
