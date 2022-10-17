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
    unsigned int sum_1 = 0;
    unsigned int sum_2 = 0;
    unsigned int sum_3 = 0;

    for (unsigned int i = 0; i < game_data.steps_count; i++){
        if (detailed){
            std::string current_command;
            std::getline(std::cin, current_command);

            if (current_command == "quit"){
                break;
            }
            if (!current_command.empty()){
                std::cout << "Incorrect command";
            }
        }


        char t1 = game_data.strategies_list[0]->act();
        char t2 = game_data.strategies_list[1]->act();
        char t3 = game_data.strategies_list[2]->act();

        const Row current_row = game_data.matrix.get_row(t1, t2, t3);
        sum_1 += current_row[0];
        sum_2 += current_row[1];
        sum_3 += current_row[2];

        if (detailed){
            std::cout << "Choices: P1 - " << t1 << ", P2 - " << t2 << ", P3 - " << t3 << "\n";
            std::cout << "Score: P1 - " << sum_1 << ", P2 - " << sum_2 << ", P3 - " << sum_3 << "\n";
        }
    }

    if (!detailed){
        std::cout << "Final score: P1 - " << sum_1 << ", P2 - " << sum_2 << ", P3 - " << sum_3 << "\n";
    }
}

void tournament(const GameData& game_data){
    GameData t = game_data;

}
void game(GameMode mode, const GameData& game_data){
    if (mode == TOURNAMENT){
        tournament(game_data);
    }

    competition(mode == DETAILED, game_data);
}

int main(){
    srand(time(nullptr));

    Matrix matrix("../matrices/matrix_2");

    StrategiesFactory factory = StrategiesFactory();

    StrategiesList strategies_list;

    strategies_list.push_back(factory.create_strategy(CONSTANT_STRATEGY));
    strategies_list.push_back(factory.create_strategy(RANDOM_STRATEGY));
    strategies_list.push_back(factory.create_strategy(PERIODIC_STRATEGY));

    GameMode mode = DETAILED;

    GameData game_data({3, strategies_list, matrix});

    game(mode, game_data);

    return 0;
}
