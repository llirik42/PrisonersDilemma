#include "viewer.h"
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

Viewer::Viewer(unsigned int players_count):_players_count(players_count), _rounds_counter(0){
    for (unsigned int i = 0; i < _players_count; i++){
        std::string out({'P'});
        out += std::to_string(i + 1);

        std::cout.width(WIDTH);

        std::cout << out;
    }

    std::cout << '\n';
}

void Viewer::view_incorrect_command(){
    std::cout << "Incorrect command!\n\n";
}

void Viewer::view_final_score(const Score& final_score){
    view_container<const Score&, int>("Final score", final_score, false);
}

void Viewer::view_help_command(const StrategiesDescription& strategies_description) const{

}

void Viewer::view_round(const Score& current_score, const Triplet<Step>& choices, const Score& delta_score){
    view_container<const Triplet<Step>, Step>("", choices, false);
    view_container<const Score, int>("", delta_score, true);
    view_container<const Score, int>("", current_score, false);
}

void Viewer::view_round(const Score& current_score, const Score& delta_score, StrategiesIndexes indexes){
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

void Viewer::view_parsing_error(ParsingStatus status){
    static std::map<ParsingStatus, std::string> status_to_message({
        {TOO_FEW_ARGS, "123"},
        {TOO_MANY_ARGS, "123"},
        {HELP_IS_NOT_ONLY_ARG, "123"},
        {INCORRECT_STRATEGIES, "123"},
        {INCORRECT_MODE, "123"},
        {INCORRECT_STEPS_COUNT, "123"},
        {INCORRECT_MATRIX_PATH, "123"},
        });

    std::cout << status_to_message[status] << "\n";
}
