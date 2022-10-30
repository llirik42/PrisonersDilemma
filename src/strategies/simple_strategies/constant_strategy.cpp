#include "constant_strategy.h"

RawConstantStrategy::RawConstantStrategy():_step(COOPERATION_STEP) {}

Step RawConstantStrategy::act(){
    return _step;
}
