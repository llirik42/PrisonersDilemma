#include "strategies_factory.h"
#include "args_parser.h"
#include "game.h"
#include "storage.h"

int main(int arc, char** argv){
    srand(time(nullptr));

    StrategiesFactory factory = StrategiesFactory();

    StrategiesDescription strategies_description = factory.get_strategies_description();

    ArgsParser args_parser(arc, const_cast<const char**>(argv), strategies_description);

    ParsingStatus status = args_parser.get_parsing_status();

    if (status != SUCCESS){
        GameViewer::view_parsing_error(status);
        return 1;
    }

    if (args_parser.is_help_mode()){
        GameViewer::view_help_command(strategies_description);
        return 0;
    }

    Matrix matrix = args_parser.is_matrix_default() ? Matrix() : Matrix(args_parser.get_matrix_file_path());
    if (matrix.has_error()){
        GameViewer::view_incorrect_matrix();
        return 1;
    }

    Storage storage = Storage(args_parser.get_configs_path());

    History previous_games_history = storage.get_previous_games_history();

    StrategiesVector strategies_list;
    for (const auto& title : args_parser.get_strategies_names()){
        Strategy new_strategy = factory.create_strategy(title);

        storage.register_strategy(new_strategy);

        if (new_strategy->is_super_smart()){
            storage.register_strateg(new_strategy);
        }

        new_strategy->apply_previous_games_experience(previous_games_history);

        strategies_list.push_back(new_strategy);
    }

    Game game(strategies_list, matrix,args_parser.get_steps_count(),
            args_parser.get_game_mode(),storage);

    game.start();

    return 0;
}
