#pragma once

#include <memory>
#include "../utils.h"
#include "../storage.h"

class RawAbstractStrategy;

using Strategy = std::shared_ptr<RawAbstractStrategy>;

class RawAbstractStrategy{
public:
    virtual ~RawAbstractStrategy()=default;
    virtual Step act(){return COOPERATION_STEP;}

    unsigned int get_id(){
        return _id;
    }
    void set_id(unsigned int id){
        _id = id;
    }
protected:
    RawAbstractStrategy()=default;
private:
    unsigned int _id=0;
};
