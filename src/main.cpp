#include "strategies_factory.h"
#include "game.h"

int main(){
    srand(time(nullptr));

    Matrix matrix("../matrices/matrix_2");

    StrategiesFactory factory = StrategiesFactory();

    StrategiesVector strategies_list;

    strategies_list.push_back(factory.create_strategy("Constant"));
    strategies_list.push_back(factory.create_strategy("Periodic"));
    strategies_list.push_back(factory.create_strategy("Random"));
    strategies_list.push_back(factory.create_strategy("Random"));
    strategies_list.push_back(factory.create_strategy("Random"));

    GameMode mode = TOURNAMENT;

    Game game(strategies_list, matrix, 100, mode);

    game.start();

    return 0;
}
