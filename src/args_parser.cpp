#include "args_parser.h"
#include <iostream>
#include <regex>

std::string extract_arg_name(char* arg){
    std::string result;

    const char* current_pointer = arg;
    while (current_pointer[0] != '\0' && current_pointer[0] != '='){
        result.append(1, current_pointer[0]);
        current_pointer++;
    }

    return result;
}

void extract_steps_count(char* argv, ArgsParser& parser){
    parser._steps_count = 0;

    const char* current_pointer = argv;
    while (current_pointer[0] != '='){
        current_pointer++;
    }

    current_pointer++;
    while (current_pointer[0] != '\0'){
        parser._steps_count = parser._steps_count * 10 + (current_pointer[0] - '0');
        current_pointer++;
    }
}

void extract_matrix_file_path(char* argv, ArgsParser& parser){
    parser._matrix_file_path = "";

    const char* current_pointer = argv;
    while (current_pointer[0] != '='){
        current_pointer++;
    }

    current_pointer++;

    while (current_pointer[0] != '\0'){
        parser._matrix_file_path += current_pointer[0];
        current_pointer++;
    }
}

void extract_game_mode(char* argv, ArgsParser& parser){
    const char* current_pointer = argv;
    while (current_pointer[0] != '='){
        current_pointer++;
    }

    current_pointer++;

    if (current_pointer[0] == 'd'){
        parser._game_mode = DETAILED;
    }
    if (current_pointer[0] == 'f'){
        parser._game_mode = FAST;
    }
    if (current_pointer[0] == 't'){
        parser._game_mode = TOURNAMENT;
    }
}

void extract_strategies_titles(char* argv, ArgsParser& parser){
    const char* current_pointer = argv;
    while (current_pointer[0] != '='){
        current_pointer++;
    }

    current_pointer += 2; // = + [

    while (current_pointer[0] != '\0'){
        std::string current_strategy;
        while (current_pointer[0] != ',' && current_pointer[0] != ']'){
            current_strategy += current_pointer[0];
            current_pointer++;
        }
        current_pointer++; // ,
        parser._strategies_titles.push_back(current_strategy);
    }
}

void ArgsParser::parse(int arc, char** argv, const StrategiesDescription& strategies_description){
    std::map<std::string, bool> met_arg({
        {"--help", false},
        {"--strategies", false},
        {"--mode", false},
        {"--steps", false},
        {"--matrix", false}
    });

    std::map<std::string, void(*)(char*, ArgsParser&)> tmp({
        {"--strategies", extract_strategies_titles},
        {"--mode", extract_game_mode},
        {"--steps", extract_steps_count},
        {"--matrix", extract_matrix_file_path}
    });

    for (unsigned int i = 1; i < arc; i++){
        std::string current_arg_name = extract_arg_name(argv[i]);

        if (met_arg[current_arg_name]){
            _parsing_status = REPEATED_ARGS;
            return;
        }

        met_arg[current_arg_name] = true;

        if (current_arg_name == "--help"){
            continue;
        }

        tmp[current_arg_name](argv[i], *this);
    }

    bool f = false;
    for (const auto& kv: met_arg){
        if (kv.second){
            f = true;
        }
    }

    if (!f){
        _parsing_status = TOO_FEW_ARGS;
        return;
    }


    if (met_arg["--help"]){
        for (const auto& kv: met_arg){
            if (kv.first != "--help" && kv.second){
                _parsing_status = HELP_IS_NOT_ONLY_ARG;
                return;
            }
        }

        _help = true;
        return;
    }

    if (!met_arg["--strategies"]){
        _parsing_status = NO_STRATEGIES;
        return;
    }

    for (const auto& title: _strategies_titles){

        bool f2 = false;

        for (const auto& kv : strategies_description){
            if (kv.first == title){
                f2 = true;
                break;
            }
        }

        if (!f2){
            _parsing_status = UNKNOWN_STRATEGIES;
            return;
        }
    }

    if (_strategies_titles.size() > 3 && !met_arg["--mode"]){
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

    std::regex arg_regex(R"(--((help)|(steps=([1-9])([0-9])*)|(matrix=.+)|(mode=((fast)|(detailed)|(tournament)))|(strategies=(\[).+,.+,.+(,.+)*(\]))))");

    for (unsigned int i = 1; i < arc; i++){
        if (!std::regex_match(argv[i], arg_regex)){
            _parsing_status = INCORRECT_ARGS;
            return;
        }
    }

    parse(arc, argv, strategies_description);
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

