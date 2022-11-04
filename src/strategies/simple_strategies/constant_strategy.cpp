#include "constant_strategies.h"

Step RawCooperatorStrategy::act([[maybe_unused]] const Choices& enemies_choices){
    return COOPERATION_STEP;
}

Step RawDefectorStrategy::act([[maybe_unused]] const Choices& enemies_choices){
    return DEFECTION_STEP;
}
