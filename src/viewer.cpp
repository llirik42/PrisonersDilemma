#include "viewer.h"
#include <iostream>

inline const unsigned int WIDTH2 = 20;
inline const unsigned int WIDTH_FOR_LIST = 40;
inline const unsigned int LIST_INDENT = 10;

using ListWithDescription = std::map<std::string, std::string>;

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
        std::cout.width(WIDTH2);
        std::cout << i;
    }
    std::cout << "\n";

    std::cout.unsetf(std::ostream::right);
    std::cout.unsetf(std::ostream::showpos);
}

void view_list(const std::string& list_title, const ListWithDescription& list, bool args){
    std::cout << list_title << ":\n";
    for (const auto& element : list){
        for (unsigned int i = 0; i < LIST_INDENT; i++){
            std::cout << ' ';
        }
        if (args){
            std::cout << "--";
        }

        std::cout.width(WIDTH_FOR_LIST + 2 * (1 - args));
        std::cout.setf(std::ostream::left);
        std::cout << element.first << element.second << '\n';
        std::cout.unsetf(std::ostream::left);
    }
}

GameViewer::GameViewer():_players_count(0), _rounds_counter(0) {}

GameViewer::GameViewer(unsigned int players_count):_players_count(players_count), _rounds_counter(0){
    for (unsigned int i = 0; i < _players_count; i++){
        std::string out({'P'});
        out += std::to_string(i + 1);

        std::cout.width(WIDTH2);

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
        std::cout.width(WIDTH2);

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

void GameViewer::view_help_command([[maybe_unused]] StrategiesDescription& strategies_description){
    std::cout << "The program is the simulator of Prisoner's dilemma for 3 players. It arranges classical rounds "
                 "with 3 players and tournament, where all kinds of threes are being competed.\n\n";

    std::cout << "Usage PrisonersDilemma [--help]  [--matrix=MATRIX_PATH] [--steps=STEPS] "
                 "[--mode=detailed|fast|tournament] --strategies=[S1,S2,S3,...]\n\n";

    std::map<std::string, std::string> tmp({
        {"help", "Help"},
        {"matrix=MATRIX_PATH", "Path to file of matrix"},
        {"steps=STEPS", "Number of steps in game (in a round if mode=tournament)"},
        {"mode=detailed|fast|tournament", R"(Game of mode. "detailed" can be interrupted by the "quit")"},
        {"strategies=[S1,S2,S3,...]", "List of strategies in the game (at least 3). Strategies must go with no spaces"},
        });

    std::map<std::string, std::string> modes({
        {"fast", "The program calculates the specified number of moves and outputs the result"},
        {"detailed", "At each step, the program waits for a keystroke and after it prints data for this round and takes one step"},
        {"tournament", "The program iterates through all possible triples and identifies the winner by the sum of points"}
    });

    view_list("Options", tmp, true);
    view_list("Strategies", strategies_description, false);
    view_list("Modes", modes, false);
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

    std::cout << status_to_message[status] << ". See --help";
}
