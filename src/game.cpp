#include <iostream>
#include "game.h"
#include "utils.h"
#include "viewer.h"

enum CommandReadingStatus{
    QUIT_COMMAND,
    INCORRECT_COMMAND,
    NO_COMMAND
};

CommandReadingStatus read_command(){
    std::string current_command;
    std::getline(std::cin, current_command);

    if (current_command == "quit"){
        return QUIT_COMMAND;
    }

    if (!current_command.empty()){
        return INCORRECT_COMMAND;
    }

    return NO_COMMAND;
}

void add_score(const Score& source, Score& destination, StrategiesIndexes indexes){
    destination[indexes[0]] += source[0];
    destination[indexes[1]] += source[1];
    destination[indexes[2]] += source[2];
}
void add_score(const Row& source, Score& destination){
    destination[0] += source[0];
    destination[1] += source[1];
    destination[2] += source[2];
}

StrategiesTriplet Game::extract_strategies_triplet(StrategiesIndexes indexes){
    return StrategiesTriplet({_strategies[indexes[0]], _strategies[indexes[1]], _strategies[indexes[2]]});
}

Score Game::competition(StrategiesTriplet& strategies_triplet){
    Score score({0, 0, 0});

    for (unsigned int i = 0; i < _steps_count; i++){
        if (_mode == DETAILED){
            CommandReadingStatus status = read_command();

            if (status == QUIT_COMMAND){
                break;
            }
            if (status == INCORRECT_COMMAND){
                Viewer::view_incorrect_command();
            }
        }

        Triplet<Step> steps;
        for (unsigned int j = 0; j < steps.size(); j++){
            steps[j] = strategies_triplet[j]->act();
        }

        auto delta_score = _matrix.get_row(steps);
        add_score(delta_score, score);

        if (_mode == DETAILED){
            Viewer::view_round(score, steps, delta_score);
        }
    }

    return score;
}

Score Game::tournament(){
    Score score({0});
    score.resize(_strategies.size());

    for (unsigned int i = 0; i <= _strategies.size() - 3; i++){
        for (unsigned int j = i + 1; j <= _strategies.size() - 2; j++){
            for (unsigned int k = j + 1; k <= _strategies.size() - 1; k++){
                StrategiesTriplet competitors = extract_strategies_triplet({i, j, k});

                Score current_triple_score = competition(competitors);

                add_score(current_triple_score, score, {i, j, k});

                _viewer.view_round(score, current_triple_score, {i, j, k});
            }
        }
    }

    return score;
}

Game::Game(StrategiesVector& strategies, const Matrix& matrix, unsigned int steps_count, GameMode mode):
        _viewer(Viewer(strategies.size())), _strategies(strategies), _matrix(matrix), _steps_count(steps_count), _mode(mode) {}

void Game::start(){
    Score score;

    if (_mode != TOURNAMENT){
        StrategiesTriplet competitors = extract_strategies_triplet({0, 1, 2});

        score = competition(competitors);
    }
    else{
        score = tournament();
    }

    Viewer::view_final_score(score);
}
