#include "strategies_factory.h"
#include <vector>
#include <iostream>
#include "strategy.h"
#include "matrix.h"

enum GameMode{
    FAST,
    DETAILED,
    TOURNAMENT
};

using StrategiesList = std::vector<std::unique_ptr<Strategy>>;

struct GameData{
    unsigned int steps_count;
    const StrategiesList& strategies_list;
    const Matrix& matrix;
};




void competition(bool detailed, const GameData& game_data){
    if (detailed){
        return;
    }

    unsigned int sum_1 = 0;
    unsigned int sum_2 = 0;
    unsigned int sum_3 = 0;

    for (unsigned int i = 0; i < game_data.steps_count; i++){
        char t1 = game_data.strategies_list[0]->act();
        char t2 = game_data.strategies_list[1]->act();
        char t3 = game_data.strategies_list[2]->act();

    }



}

void tournament(const GameData& game_data){

}

void game(GameMode mode, const GameData& game_data){
    if (mode == TOURNAMENT){
        tournament(game_data);
    }

    competition(mode == DETAILED, game_data);
}

int main(){
    Matrix matrix("../matrices/matrix_2");

    StrategiesFactory factory = StrategiesFactory();

    StrategiesList strategies_list;

    strategies_list.push_back(factory.create_strategy(CONSTANT_STRATEGY));
    strategies_list.push_back(factory.create_strategy(RANDOM_STRATEGY));
    strategies_list.push_back(factory.create_strategy(PERIODIC_STRATEGY));

    GameMode mode = FAST;

    GameData game_data({true, strategies_list, matrix});

    game(mode, game_data);

    return 0;
}
