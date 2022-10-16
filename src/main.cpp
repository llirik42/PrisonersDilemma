#include "strategies_factory.h"
#include <vector>
#include <iostream>

void


void fast_mode(){

}
void tournament(){

}
void detailed_mode(){

}

int main(){
    //srand(time(nullptr));

    StrategiesFactory factory = StrategiesFactory();

    std::vector<std::unique_ptr<Strategy>> strategies;

    strategies.push_back(factory.create_strategy(CONSTANT_STRATEGY));
    strategies.push_back(factory.create_strategy(RANDOM_STRATEGY));
    strategies.push_back(factory.create_strategy(PERIODIC_STRATEGY));

    for (unsigned int i = 0; i < 10; i++){
        for (auto & strategy : strategies){
            std::cout << strategy->act() << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
