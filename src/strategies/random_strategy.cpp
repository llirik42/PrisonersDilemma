#include <random>
#include "random_strategy.h"

Step RawRandomStrategy::act(){
    return (rand() % 2) ? COOPERATION_STEP : DEFECTION_STEP;
}
