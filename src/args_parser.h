#pragma once

#include <vector>
#include <string>
#include "strategies_factory.h"
#include "utils.h"

enum ParsingStatus{
    SUCCESS,
    TOO_FEW_ARGS,
    REPEATED_ARGS,
    HELP_IS_NOT_ONLY_ARG,
    INCORRECT_ARGS,
    TOO_MANY_STRATEGIES_FOR_NON_TOURNAMENT,
    UNKNOWN_STRATEGIES,
    NO_STRATEGIES,
};

class ArgsParser{
    friend void extract_steps_count(char* argv, ArgsParser& parser);

    friend void extract_matrix_file_path(char* argv, ArgsParser& parser);

    friend void extract_game_mode(char* argv, ArgsParser& parser);

    friend void extract_strategies_titles(char* argv, ArgsParser& parser);

private:
    std::vector<std::string> _strategies_titles;
    unsigned int _steps_count;
    std::string _matrix_file_path;
    GameMode _game_mode;
    ParsingStatus _parsing_status;
    bool _help;

    void parse(int arc, char** argv, const StrategiesDescription& strategies_description);
public:
    ArgsParser(int arc, char** argv, const StrategiesDescription& strategies_description);

    [[nodiscard]] ParsingStatus get_parsing_status() const;
    [[nodiscard]] bool is_help_mode() const;

    [[nodiscard]] const std::vector<std::string>& get_strategies_titles() const;
    [[nodiscard]] unsigned int get_steps_count() const;
    [[nodiscard]] const std::string& get_matrix_file_path() const;
    [[nodiscard]] GameMode get_game_mode() const;
};
