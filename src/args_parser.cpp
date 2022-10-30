#include <regex>
#include "args_parser.h"

inline bool points_to_end(const char* const pointer){
    return pointer[0] == '\0';
}

inline bool points_to_equal(const char* const pointer){
    return pointer[0] == '=';
}

void move_to_equal_and_step(char** pointer){
    while (!points_to_equal(*pointer)){
        (*pointer)++;
    }

    (*pointer)++;
}

ParsingStatus validate_args(int arc, char** argv){
    std::regex arg_regex(R"(--((help)|(steps=([1-9])([0-9])*)|(matrix=.+)|(mode=((fast)|(detailed)|(tournament)))|(strategies=(\[).+,.+,.+(,.+)*(\]))))");

    for (int i = 1; i < arc; i++){
        if (!std::regex_match(argv[i], arg_regex)){
            return INCORRECT_ARGS;
        }
    }

    return SUCCESS;
}

ParsingStatus validate_count_of_met_args(const ArgsParser::MetArgsMap& met_args){
    bool met_some_arg = false;
    for (const auto& kv: met_args){
        if (kv.second){
            met_some_arg = true;
        }
    }

    return met_some_arg ? SUCCESS : TOO_FEW_ARGS;
}

ParsingStatus validate_strategies(const ArgsParser& parser, const StrategiesDescription& description){
    for (const auto& name: parser._strategies_names){
        bool met_unknown_strategy = false;

        for (const auto& kv : description){
            if (kv.first == name){
                met_unknown_strategy = true;
                break;
            }
        }

        if (!met_unknown_strategy){
            return UNKNOWN_STRATEGIES;
        }
    }

    return SUCCESS;
}

bool is_help_only_arg(ArgsParser::MetArgsMap& met_args){
    if (met_args["--help"]){
        for (const auto& kv: met_args){
            if (kv.first != "--help" && kv.second){
                return false;
            }
        }
    }

    return true;
}

std::string extract_arg_name(const char* arg){
    std::string result;

    const char* current_pointer = arg;
    while (!points_to_end(current_pointer) && !points_to_equal(current_pointer)){
        result += current_pointer[0];
        current_pointer++;
    }

    return result;
}

void extract_steps_count(char* arg, ArgsParser& parser){
    parser._steps_count = 0;

    move_to_equal_and_step(&arg);

    while (!points_to_end(arg)){
        parser._steps_count = parser._steps_count * 10 + char_to_digit(*arg);
        arg++;
    }
}

void extract_matrix_file_path(char* arg, ArgsParser& parser){
    parser._matrix_file_path = "";

    move_to_equal_and_step(&arg);

    while (!points_to_end(arg)){
        parser._matrix_file_path += *arg;
        arg++;
    }
}

void extract_game_mode(char* arg, ArgsParser& parser){
    move_to_equal_and_step(&arg);

    // This arg was validated earlier, so it can be only "Detailed", "Fast" or "Tournament"
    switch (*arg){
        case 'd':
            parser._game_mode = DETAILED;
            return;
        case 'f':
            parser._game_mode = FAST;
            return;
        default:
            parser._game_mode = TOURNAMENT;
    }
}

void extract_strategies_names(char* arg, ArgsParser& parser){
    move_to_equal_and_step(&arg);

    arg++; // Because of '['

    while (!points_to_end(arg)){
        std::string current_strategy_name;

        while (*arg != ',' && *arg != ']'){
            current_strategy_name += *(arg++);
        }

        arg++; // Because of ','

        parser._strategies_names.push_back(current_strategy_name);
    }
}

void extract_args(int arc, char** argv, ArgsParser::MetArgsMap& met_args, ArgsParser& parser){
    std::map<std::string,void(*)(char*, ArgsParser&)> extracting_function({
        {"--strategies", extract_strategies_names},
        {"--mode",       extract_game_mode},
        {"--steps",      extract_steps_count},
        {"--matrix",     extract_matrix_file_path}
    });

    for (int i = 1; i < arc; i++){
        auto current_arg_name = extract_arg_name(argv[i]);

        if (met_args[current_arg_name]){
            parser._parsing_status = REPEATED_ARGS;
            return;
        }

        met_args[current_arg_name] = true;

        if (current_arg_name != "--help"){
            extracting_function[current_arg_name](argv[i], parser);
        }
    }
}

void ArgsParser::parse(int arc, char** argv, const StrategiesDescription& strategies_description){
    MetArgsMap met_args({
        {"--help", false},
        {"--strategies", false},
        {"--mode", false},
        {"--steps", false},
        {"--matrix", false}
    });

    extract_args(arc, argv, met_args, *this);

    ParsingStatus count_validation_status = validate_count_of_met_args(met_args);
    if (count_validation_status != SUCCESS){
        _parsing_status = count_validation_status;
        return;
    }

    if (!is_help_only_arg(met_args)){
        _parsing_status = HELP_IS_NOT_ONLY_ARG;
        return;
    }

    if (!met_args["--strategies"]){
        _parsing_status = NO_STRATEGIES;
        return;
    }

    ParsingStatus strategies_validation_status = validate_strategies(*this, strategies_description);
    if (strategies_validation_status != SUCCESS){
        _parsing_status = strategies_validation_status;
    }

    if (_strategies_names.size() > 3 && !met_args["--mode"]){
        _game_mode = TOURNAMENT;
    }
}

ArgsParser::ArgsParser(int arc, char** argv, const StrategiesDescription& strategies_description){
    // default values
    _steps_count = 1;
    _game_mode = DETAILED;
    _matrix_file_path = "../matrices/matrix_2";
    _help = false;
    _parsing_status = SUCCESS;

    const ParsingStatus validation_status = validate_args(arc, argv);

    if (validation_status != SUCCESS){
        _parsing_status = validation_status;
        return;
    }

    parse(arc, argv, strategies_description);
}

ParsingStatus ArgsParser::get_parsing_status() const{
    return _parsing_status;
}

const std::vector<std::string>& ArgsParser::get_strategies_names() const{
    return _strategies_names;
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
