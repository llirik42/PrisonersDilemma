#include "constant_strategy.h"

RawConstantStrategy::RawConstantStrategy():_step(DEFECTION_STEP) {}

Step RawConstantStrategy::act([[maybe_unused]] const Choices& enemies_choices){
    return _step;
}
