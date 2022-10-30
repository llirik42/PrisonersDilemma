#include "abstract_strategy.h"

RawAbstractStrategy::RawAbstractStrategy()=default;

RawAbstractStrategy::~RawAbstractStrategy()=default;

Step RawAbstractStrategy::act(){
    return 0;
}
