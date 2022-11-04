#include "tit_for_tat_strategy.h"

Step RawTitForTatStrategy::act(const Choices& enemies_choices){
    if (enemies_choices.empty()){
        return COOPERATION_STEP;
    }

    unsigned int cooperation_count = 0;
    unsigned int defection_count = 0;

    for (const auto& choice: enemies_choices){
        cooperation_count += (choice == COOPERATION_STEP);
        defection_count += (choice == DEFECTION_STEP);
    }

    return cooperation_count > defection_count ? COOPERATION_STEP : DEFECTION_STEP;
}
