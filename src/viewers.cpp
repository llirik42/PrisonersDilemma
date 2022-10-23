#include "viewers.h"
#include <iostream>

inline const unsigned int WIDTH = 20;

template<typename Container, typename Element>
void view_container(const std::string& title, Container container, bool unary_plus){
    if (unary_plus){
        std::cout.setf(std::ostream::showpos);
    }

    std::cout.setf(std::ostream::right);
    std::cout.fill(' ');

    if (!title.empty()){
        std::cout << title << ":\n";
    }

    for (Element i : container){
        std::cout.width(WIDTH);
        std::cout << i;
    }
    std::cout << "\n";

    std::cout.unsetf(std::ostream::right);
    std::cout.unsetf(std::ostream::showpos);
}

GameViewer::GameViewer():_players_count(0), _rounds_counter(0) {}

GameViewer::GameViewer(unsigned int players_count):_players_count(players_count), _rounds_counter(0){
    for (unsigned int i = 0; i < _players_count; i++){
        std::string out({'P'});
        out += std::to_string(i + 1);

        std::cout.width(WIDTH);

        std::cout << out;
    }

    std::cout << '\n';
}

void GameViewer::view_round(const Score& current_score, const Score& delta_score, StrategiesIndexes indexes){
    std::cout << "Round " << (1 + _rounds_counter++) << ":\n";

    std::cout.setf(std::ostream::showpos);
    std::cout.setf(std::ostream::right);
    std::cout.fill(' ');

    for (unsigned int i = 0; i < _players_count; i++){
        std::cout.width(WIDTH);

        int tmp_index = -1;
        for (unsigned int j = 0; j < indexes.size(); j++){
            if (indexes[j] == i){
                tmp_index = j;
            }
        }

        if (tmp_index != -1){
            std::cout << delta_score[tmp_index];
        }
        else{
            std::cout << " ";
        }
    }
    std::cout << "\n";

    std::cout.unsetf(std::ostream::right);
    std::cout.unsetf(std::ostream::showpos);

    view_container<const Score&, int>("", current_score, false);
    std::cout << '\n';
}

void GameViewer::view_incorrect_matrix(){
    std::cout << "Incorrect matrix\n";
}

void GameViewer::view_incorrect_command(){
    std::cout << "Incorrect command!\n\n";
}

void GameViewer::view_final_score(const Score& final_score){
    view_container<const Score&, int>("Final score", final_score, false);
}

void GameViewer::view_help_command(const StrategiesDescription& strategies_description){
    std::cout << "Help command)\n";
}

void GameViewer::view_round(const Score& current_score, const Triplet<Step>& choices, const Score& delta_score){
    view_container<const Triplet<Step>, Step>("", choices, false);
    view_container<const Score, int>("", delta_score, true);
    view_container<const Score, int>("", current_score, false);
}

void GameViewer::view_parsing_error(ParsingStatus status){
    static std::map<ParsingStatus, std::string> status_to_message({
        {TOO_FEW_ARGS, "Too few args"},
        {HELP_IS_NOT_ONLY_ARG, "--help is not the only arg"},
        {TOO_MANY_STRATEGIES_FOR_NON_TOURNAMENT, "Too many strategies for non-tournament mode"},
        {INCORRECT_ARGS, "Incorrect args"},
        {REPEATED_ARGS, "Some args are repeated"},
        {UNKNOWN_STRATEGIES, "Unknown strategies"},
        {NO_STRATEGIES, "At least 3 strategies must be chosen"}
        });

    std::cout << status_to_message[status] << "\n";
}
