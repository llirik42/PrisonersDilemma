#include <random>
#include "random_strategy.h"

Step RawRandomStrategy::act([[maybe_unused]] const Choices& enemies_choices){
    return (rand() % 2) ? COOPERATION_STEP : DEFECTION_STEP;
}
