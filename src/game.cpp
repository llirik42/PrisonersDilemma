#include <iostream>
#include "game.h"

void add_score(const Score& source, Score& destination, unsigned int i, unsigned int j, unsigned int k){
    destination[i] += source[0];
    destination[j] += source[1];
    destination[k] += source[2];
}
void add_score(const Row& source, Score& destination){
    destination[0] += source[0];
    destination[1] += source[1];
    destination[2] += source[2];
}

StrategiesTriplet Game::extract_strategies_triplet(unsigned int i, unsigned int j, unsigned int k){
    return StrategiesTriplet({_strategies[i], _strategies[j], _strategies[k]});
}

Score Game::competition(StrategiesTriplet& strategies_triplet, bool mode){
    Score score({0, 0, 0});

    for (unsigned int i = 0; i < _steps_count; i++){
        if (_mode == DETAILED){
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

        add_score(_matrix.get_row(steps), score);

        if (_mode == DETAILED){
            std::cout << "Choices: P1 - " << steps[0] << ", P2 - " << steps[1] << ", P3 - " << steps[2] << "\n";
            std::cout << "Score: P1 - " << score[0] << ", P2 - " << score[1] << ", P3 - " << score[1] << "\n";
        }
    }

    return score;
}

void Game::tournament(){
    Score score({0});
    score.resize(_strategies.size());

    for (unsigned int i = 0; i <= _strategies.size() - 3; i++){
        for (unsigned int j = i + 1;j <= _strategies.size() - 2; j++){
            for (unsigned int k = j + 1; k <= _strategies.size() - 1; k++){
                StrategiesTriplet competitors = extract_strategies_triplet(i, j, k);

                Score current_triple_score = competition(competitors, FAST);



                add_score(current_triple_score, score, i, j, k);
            }
        }
    }

    for (unsigned int i = 0; i < _strategies.size(); i++){
        std::cout << score[i] << " ";
    }
    std::cout << "\n";
}

Game::Game(StrategiesVector& strategies, const Matrix& matrix, unsigned int steps_count, GameMode mode):
    _strategies(strategies), _matrix(matrix), _steps_count(steps_count), _mode(mode) {}

void Game::start(){
    if (_mode != TOURNAMENT){
        auto competitors = extract_strategies_triplet(0, 1, 2);

        Score score = competition(competitors, _mode);

        std::cout << "Final score: P1 - " << score[0] << ", P2 - " << score[1] << ", P3 - " << score[2] << "\n";

        return;
    }

    tournament();
}
