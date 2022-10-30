#include "kind_strategy.h"

RawKindStrategy::RawKindStrategy(): _was_betrayed(false) {}

Step RawKindStrategy::act(const Choices& enemies_choices){
    if (enemies_choices.empty()){
        return COOPERATION_STEP;
    }

    if (!_was_betrayed){
        for (const auto& choice: enemies_choices){
            if (choice == DEFECTION_STEP){
                _was_betrayed = true;
                break;
            }
        }
    }

    return _was_betrayed ? DEFECTION_STEP : COOPERATION_STEP;
}
