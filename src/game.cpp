#include <iostream>
#include "game.h"
#include "utils.h"

using TripleScore = Triplet<int>;
using StrategiesTriplet = Triplet<std::unique_ptr<Strategy>>;

void add_score(const TripleScore& source, TripleScore& destination){
    destination[0] += source[0];
    destination[1] += source[1];
    destination[2] += source[2];
}

StrategiesTriplet strategies_vector_to_triplet(StrategiesVector& strategies, unsigned int i, unsigned int j, unsigned int k){
    return StrategiesTriplet({
       std::move(strategies[0]),
       std::move(strategies[1]),
       std::move(strategies[2])
    });
}

TripleScore competition(StrategiesTriplet& strategies_triplet, const Matrix& matrix, unsigned int steps_count, GameMode mode){
    TripleScore score({0});

    for (unsigned int i = 0; i < steps_count; i++){
        if (mode == DETAILED){
            std::string current_command;
            std::getline(std::cin, current_command);

            if (current_command == "quit"){
                break;
            }
            if (!current_command.empty()){
                std::cout << "Incorrect command";
            }
        }

        Triplet<Step> steps;
        for (unsigned int j = 0; j < 3; j++){
            steps[j] = strategies_triplet[j]->act();
        }

        add_score(matrix.get_row(steps), score);

        if (mode == DETAILED){
            std::cout << "Choices: P1 - " << t1 << ", P2 - " << t2 << ", P3 - " << t3 << "\n";
            std::cout << "Score: P1 - " << score_1 << ", P2 - " << score_2 << ", P3 - " << score_3 << "\n";
        }
    }

    if (mode == FAST){
        std::cout << "Final score: P1 - " << score_1 << ", P2 - " << score_2 << ", P3 - " << score_3 << "\n";
    }

    return score;

}

void tournament(const StrategiesVector& strategies, const Matrix& matrix, unsigned int steps_count){
    std::cout << "Tournament\n";
}

void game(StrategiesVector& strategies, const Matrix& matrix, unsigned int steps_count, GameMode mode){
    if (mode != TOURNAMENT){
        auto competitors = strategies_vector_to_triplet(strategies, 0, 1, 2);

        competition(competitors, matrix, steps_count, mode);

        return;
    }

    tournament(strategies, matrix, steps_count);
}
