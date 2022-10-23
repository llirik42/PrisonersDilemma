#include "args.h"

ArgsParser::ArgsParser(int arc, char** argv, const StrategiesDescription& strategies_description){
    if (arc > 5 || arc < 2){
        _parsing_status = 0;
        return;
    }

    _strategies_titles = {"Constant", "Random", "Constant"};
    _steps_count = 3;
    _matrix_file_path = "../matrices/matrix_2";
    _game_mode = TOURNAMENT;
    _help = false;
}

ParsingStatus ArgsParser::get_parsing_status() const{
    return _parsing_status;
}

const std::vector<std::string>& ArgsParser::get_strategies_titles() const{
    return _strategies_titles;
}

unsigned int ArgsParser::get_steps_count() const{
    return _steps_count;
}

const std::string& ArgsParser::get_matrix_file_path() const{
    return _matrix_file_path;
}

GameMode ArgsParser::get_game_mode() const{
    return _game_mode;
}

bool ArgsParser::is_help_mode() const{
    return _help;
}
